//
// Created by klei on 5/8/18.
//

#ifndef PRODUCTION_LINE_CONTROL_MOCKNETWORK_H
#define PRODUCTION_LINE_CONTROL_MOCKNETWORK_H

#include <network/Manager.h>
#include <network/Connection.h>
#include <network/Message.h>
#include <cstdint>

namespace testutils{

typedef std::function<void(const Network::Message&)> OnMessageFn;
typedef std::function<void(const Network::ConnectionPtr&)> OnConnectionFn;


/**
 * The MockNetwork class can be used to create a dummy network component. Can be used to make connection for both
 * machine control and production control. Has access to an onMessage and onConnection callback
 */
class MockNetwork : public Network::IConnectionHandler, public std::enable_shared_from_this<MockNetwork> {
 public:
  MockNetwork();
  virtual ~MockNetwork();

  /**
   * Start client to connect to production control over simulation port
   * @param waitForConnected : wait for connection to establish, default true
   */
  void startMockMCClientController(bool waitForConnected = true);

  /**
   * Start client to connect to production control over production port
   * @param waitForConnected : wait for connection to establish, default true
   */
  void startMockMCClientApplication(bool waitForConnected = true);

  /**
   * Start server to listen to machine control over simulation port
   */
  void startMockPCServerController();

  /**
   * Start server to listen to machine control over production port
   */
  void startMockPCServerApplication();

  /**
   * Wait for the connection to establish or disconnect. Timeout is 100 milliseconds by default.
   * @param timeout : max time to wait in milliseconds
   */
  void awaitConnection(uint32_t timeout = 1000);

  /**
   * Call this when you send a message to the mock network. It will wait till the message is received. Timeout is
   * 100 milliseconds by default.
   * @param timeout : max time to wait in milliseconds
   */
  void awaitMessageReceived(uint32_t timeout = 1000);

  /**
   * Stop network
   */
  void stop();

  /**
   * Send message to the other side (the one you're testing)
   * @param msg : Message to send
   */
  void sendMessage(Network::Message& msg);

  /**
   * set on receive callback
   * example argument: [](Network::Message& message){std::cout << message.mBody << std::endl;}
   * @param aHandleMessageFn : lambda to be called when message is received
   */
  void setOnMessageFn(OnMessageFn& aOnMessageFn);

  /**
   * set on connection established callback
   * example argument: [](Network::ConnectionPtr& connection){write some message to connection}
   * @param aHandleMessageFn : lambda to be called when message is received
   */
  void setOnConnectionFn(OnConnectionFn& aOnConnectionFn);

  /**
   * get connection
   * @return : connection
   */
  const Network::ConnectionPtr &getConnection() const;

  // IConnectionHandler callbacks
  void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionEstablished(Network::ConnectionPtr connection) override;
  void onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;

 private:

  friend Network::Server;
  friend Network::Client;

  enum ConnectionStatus {
    kConnectionDisconnected,
    kConnectionConnected,
    kConnectionConnecting
  };
  enum MessageStatus {
	kMessageIdle,
    kMessageWaiting,
  };

  ConnectionStatus connectionStatus;
  MessageStatus messageStatus;
  ThreadPtr networkThread;
  Network::Manager networkManager;
  Network::ConnectionPtr connection;
  OnMessageFn onMessageFn;
  OnConnectionFn onConnectionFn;

  Network::ServerPtr server;
  Network::ClientPtr client;

};

}

#endif //PRODUCTION_LINE_CONTROL_MOCKNETWORK_H
