//
// Created by klei on 5/8/18.
//

#include "MockNetwork.h"
#include <network/Protocol.h>
#include <network/Client.h>
#include <network/Server.h>

namespace testUtils {

MockNetwork::MockNetwork() : status(kDisconnected), onMessageFn([](Network::Message& m){}), onConnectionFn([](Network::ConnectionPtr& c){}){
  networkThread = networkManager.runServiceThread();
}

void MockNetwork::startMockMCClientController(bool waitForConnected) {
  networkManager.setRemotePort(Network::Protocol::kPortSimulationCommunication);
  client = networkManager.createClient(shared_from_this());
  client->start();
  status = kConnecting;
  if(waitForConnected){
    awaitConnection();
  }
}

void MockNetwork::startMockMCClientApplication(bool waitForConnected) {
  networkManager.setRemotePort(Network::Protocol::kPortProductionCommunication);
  client = networkManager.createClient(shared_from_this());
  client->start();
  status = kConnecting;
  if(waitForConnected){
    awaitConnection();
  }
}

void MockNetwork::startMockPCServerController() {
  networkManager.setLocalPort(Network::Protocol::kPortSimulationCommunication);
  server = networkManager.createServer(shared_from_this(),32);
  server->start();
  status = kConnected;
}

void MockNetwork::startMockPCServerApplication() {
  networkManager.setLocalPort(Network::Protocol::kPortProductionCommunication);
  server = networkManager.createServer(shared_from_this(),32);
  server->start();
  status = kConnected;
}

void MockNetwork::onConnectionEstablished(Network::ConnectionPtr aConnection) {
  connection = aConnection;
  status = kConnected;
}

void MockNetwork::onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) {
  status = kDisconnected;
}

void MockNetwork::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
  if(onMessageFn){
    onMessageFn(message);
  }
}

void MockNetwork::sendMessage(Network::Message &msg) {
  if(connection && connection->isConnected()){
	connection->writeMessage(msg);
  }
}

void MockNetwork::setOnMessageFn(std::function<void(Network::Message &)>& aOnMessageFn) {
  onMessageFn = aOnMessageFn;
}

void MockNetwork::setOnConnectionFn(std::function<void(Network::ConnectionPtr &)> &aOnConnectionFn) {
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
  status = kDisconnected;
}
void MockNetwork::awaitConnection() {
  while(status == kConnecting){}
}

}