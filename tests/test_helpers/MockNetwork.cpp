//
// Created by klei on 5/8/18.
//

#include <ctime>

#include "MockNetwork.h"
#include "HelperFunctions.h"
#include <network/Protocol.h>
#include <network/Client.h>
#include <network/Server.h>

namespace testutils {

MockNetwork::MockNetwork() : connectionStatus(kConnectionDisconnected), messageStatus(kMessageIdle),
                             onMessageFn([](const Network::Message& m){}), onConnectionFn([](const Network::ConnectionPtr& c){}){
  networkThread = networkManager.runServiceThread();
}

MockNetwork::~MockNetwork(){
  stop();
}

void MockNetwork::startMockMCClientController(bool waitForConnected) {
  networkManager.setRemotePort(Network::Protocol::PORT_SIMULATION_COMMUNICATION);
  if(connectionHandler){
    client = networkManager.createClient(connectionHandler);
  }
  else{
    client = networkManager.createClient(shared_from_this());
  }
  client->start();
  connectionStatus = kConnectionConnecting;
  if(waitForConnected){
    awaitConnection();
  }
}

void MockNetwork::startMockMCClientApplication(bool waitForConnected) {
  networkManager.setRemotePort(Network::Protocol::PORT_PRODUCTION_COMMUNICATION);
  if(connectionHandler){
    client = networkManager.createClient(connectionHandler);
  }
  else{
    client = networkManager.createClient(shared_from_this());
  }
  client->start();
  connectionStatus = kConnectionConnecting;
  if(waitForConnected){
    awaitConnection();
  }
}

void MockNetwork::startMockPCServerController() {
  networkManager.setLocalPort(Network::Protocol::PORT_SIMULATION_COMMUNICATION);
  if(connectionHandler){
    server = networkManager.createServer(connectionHandler,32);
  }
  else{
    server = networkManager.createServer(shared_from_this(),32);
  }
  server->start();
  connectionStatus = kConnectionConnecting;
}

void MockNetwork::startMockPCServerApplication() {
  networkManager.setLocalPort(Network::Protocol::PORT_PRODUCTION_COMMUNICATION);
  if(connectionHandler){
    server = networkManager.createServer(connectionHandler,32);
  }
  else{
    server = networkManager.createServer(shared_from_this(),32);
  }
  server->start();
  connectionStatus = kConnectionConnecting;
}

void MockNetwork::onConnectionEstablished(Network::ConnectionPtr aConnection) {
  connection = aConnection;
  connectionStatus = kConnectionConnected;
}

void MockNetwork::onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) {
  connectionStatus = kConnectionDisconnected;
}

void MockNetwork::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
  if(onMessageFn){
    onMessageFn(message);
  }
  // Message has been handled, set status to idle
  messageStatus = kMessageIdle;
}

void MockNetwork::sendMessage(Network::Message &msg) {
  if(connection && connection->isConnected()){
	connection->writeMessage(msg);
  }
}

void MockNetwork::setOnMessageFn(OnMessageFn &aOnMessageFn) {
  onMessageFn = aOnMessageFn;
}

void MockNetwork::setOnConnectionFn(OnConnectionFn &aOnConnectionFn) {
  onConnectionFn = aOnConnectionFn;
}

const Network::ConnectionPtr &MockNetwork::getConnection() const {
  return connection;
}

void MockNetwork::stop() {
  networkManager.stop();
  Predicate disconnected = [this](){return connectionStatus == kConnectionDisconnected;};
  HelperFunctions::waitForPredicate(disconnected, 1000);
  if (networkThread && networkThread->joinable()){
    networkThread->join();
  }
}
void MockNetwork::onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) {
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
void MockNetwork::setConnectionHandler(Network::ConnectionHandlerPtr handler) {
  connectionHandler = handler;
}

}