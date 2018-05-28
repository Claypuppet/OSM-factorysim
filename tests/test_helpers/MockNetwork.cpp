//
// Created by klei on 5/8/18.
//

#include <ctime>

#include "MockNetwork.h"
#include "HelperFunctions.h"
#include <network/Client.h>
#include <network/Server.h>

// Server static init
network::Manager testutils::MockNetwork::serverManager;
ThreadPtr testutils::MockNetwork::serverThread;

// Client static init
network::Manager testutils::MockNetwork::clientManager;
ThreadPtr testutils::MockNetwork::clientThread;

namespace testutils {

MockNetwork::MockNetwork() : connectionStatus(kConnectionDisconnected), messageStatus(kMessageIdle),
                             onMessageFn([](const network::Message& m){}), onConnectionFn([](const network::ConnectionPtr& c){}){
  if(!serverThread && !clientThread){
    // Start service threads and detach them.
    serverThread = serverManager.runServiceThread();
    clientThread = clientManager.runServiceThread();
    serverThread->detach();
    clientThread->detach();
  }
}

MockNetwork::~MockNetwork(){
  stop();
}

void MockNetwork::startMockMCClientController(bool waitForConnected) {
  if (client && client->isRunning()){
    client->stop();
  }
  clientManager.setRemotePort(network::Protocol::PORT_SIMULATION_COMMUNICATION);
  network::ConnectionHandlerPtr handler = customConnectionHandler ? customConnectionHandler : shared_from_this();
  client = clientManager.createClient(handler);
  client->start();
  connectionStatus = kConnectionConnecting;
  if(waitForConnected){
    awaitConnection();
  }
}

void MockNetwork::startMockMCClientApplication(bool waitForConnected) {
  if (client && client->isRunning()){
    client->stop();
  }
  clientManager.setRemotePort(network::Protocol::PORT_PRODUCTION_COMMUNICATION);
  network::ConnectionHandlerPtr handler = customConnectionHandler ? customConnectionHandler : shared_from_this();
  client = clientManager.createClient(handler);
  client->start();
  connectionStatus = kConnectionConnecting;
  if(waitForConnected){
    awaitConnection();
  }
}

void MockNetwork::startMockPCServerController() {
  if (server && server->isRunning()){
    server->stop();
  }
  serverManager.setLocalPort(network::Protocol::PORT_SIMULATION_COMMUNICATION);
  network::ConnectionHandlerPtr handler = customConnectionHandler ? customConnectionHandler : shared_from_this();
  server = serverManager.createServer(handler, 2);
  server->start();
  connectionStatus = kConnectionConnecting;
  HelperFunctions::wait(20);
}

void MockNetwork::startMockPCServerApplication() {
  if (server && server->isRunning()){
    server->stop();
  }
  serverManager.setLocalPort(network::Protocol::PORT_PRODUCTION_COMMUNICATION);
  network::ConnectionHandlerPtr handler = customConnectionHandler ? customConnectionHandler : shared_from_this();
  server = serverManager.createServer(handler, 2);
  server->start();
  connectionStatus = kConnectionConnecting;
  HelperFunctions::wait(20);
}

void MockNetwork::onConnectionEstablished(network::ConnectionPtr aConnection) {
  connection = aConnection;
  connectionStatus = kConnectionConnected;
}

void MockNetwork::onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) {
  connectionStatus = kConnectionDisconnected;
}

void MockNetwork::onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) {
  if(onMessageFn){
    onMessageFn(message);
  }
  // Message has been handled, set status to idle
  messageStatus = kMessageIdle;
}

void MockNetwork::sendMessage(network::Message &message) {
  if(connection && connection->isConnected()){
	connection->writeMessage(message);
  }
}

void MockNetwork::setOnMessageFn(OnMessageFn &aOnMessageFn) {
  onMessageFn = aOnMessageFn;
}

void MockNetwork::setOnConnectionFn(OnConnectionFn &aOnConnectionFn) {
  onConnectionFn = aOnConnectionFn;
}

const network::ConnectionPtr &MockNetwork::getConnection() const {
  return connection;
}

void MockNetwork::stop() {
  if (client && client->isRunning()){
    client->stop();
  }
  if (server && server->isRunning()){
    server->stop();
  }
  if(connectionStatus != kConnectionDisconnected){
    Predicate disconnected = [this](){return connectionStatus == kConnectionDisconnected;};
    HelperFunctions::waitForPredicate(disconnected, 200);
  }
}
void MockNetwork::onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) {
  connectionStatus = kConnectionDisconnected;
}
void MockNetwork::awaitConnection(uint32_t timeout) {
  Predicate predicate = [this](){return connectionStatus != kConnectionConnecting;};
  HelperFunctions::waitForPredicate(predicate, timeout);

}
void MockNetwork::awaitMessageReceived(uint32_t timeout) {
  Predicate predicate = [this](){return messageStatus != kMessageWaiting;};
  HelperFunctions::waitForPredicate(predicate, timeout);
  HelperFunctions::wait(10);
  // Message has been received or it timed out.
  messageStatus = kMessageIdle;
}
void MockNetwork::awaitClientConnecting(uint32_t timeout) {
  Predicate predicate = [this](){return connectionStatus == kConnectionConnected;};
  HelperFunctions::waitForPredicate(predicate, timeout);
}
void MockNetwork::setConnectionHandler(network::ConnectionHandlerPtr handler) {
  customConnectionHandler = handler;
}

}