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

void MockNetwork::startMockMCClientController(bool waitForConnected) {
  networkManager.setRemotePort(Network::Protocol::PORT_SIMULATION_COMMUNICATION);
  client = networkManager.createClient(shared_from_this());
  client->start();
  connectionStatus = kConnectionConnecting;
  if(waitForConnected){
    awaitConnection();
  }
}

void MockNetwork::startMockMCClientApplication(bool waitForConnected) {
  networkManager.setRemotePort(Network::Protocol::PORT_PRODUCTION_COMMUNICATION);
  client = networkManager.createClient(shared_from_this());
  client->start();
  connectionStatus = kConnectionConnecting;
  if(waitForConnected){
    awaitConnection();
  }
}

void MockNetwork::startMockPCServerController() {
  networkManager.setLocalPort(Network::Protocol::PORT_SIMULATION_COMMUNICATION);
  server = networkManager.createServer(shared_from_this(),32);
  server->start();
  connectionStatus = kConnectionConnected;
}

void MockNetwork::startMockPCServerApplication() {
  networkManager.setLocalPort(Network::Protocol::PORT_PRODUCTION_COMMUNICATION);
  server = networkManager.createServer(shared_from_this(),32);
  server->start();
  connectionStatus = kConnectionConnected;
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
  networkThread->join();
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
  // Message has been received or it timed out.
  messageStatus = kMessageIdle;
}

}