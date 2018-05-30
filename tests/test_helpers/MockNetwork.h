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

typedef std::function<void(network::Message&)> OnMessageFn;
typedef std::function<void(const network::ConnectionPtr&)> OnConnectionFn;


/**
 * The MockNetwork class can be used to create a dummy network component. Can be used to make connection for both
 * machine control and production control. Has access to an onMessage and onConnection callback
 */
class MockNetwork : public network::IConnectionHandler, public std::enable_shared_from_this<MockNetwork> {
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
   * @param timeout : max time to wait in milliseconds, default 100
   */
  void awaitConnection(uint32_t timeout = 100);

  /**
   * Call this when you send a message to the mock network. It will wait till the message is received. Timeout is
   * 100 milliseconds by default.
   * @param timeout : max time to wait in milliseconds, default 100
   */
  void awaitMessageReceived(uint32_t timeout = 100);

  /**
   * Waits for the server to start
   * @param timeout Time before timeout in milliseconds, default 100
   */
  void awaitClientConnecting(uint32_t timeout = 100);

  /**
   * Stop network
   */
  void stop();

  /**
   * Stop client instance
   */
  void stopClient();

  /**
   * Stop server instance
   */
  void stopServer();

  /**
   * Send message to the other side (the one you're testing)
   * @param msg : Message to send
   */
  void sendMessage(network::Message& msg);

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
   * Set a new handler for the client / server
   * @param handler
   */
  void setConnectionHandler(network::ConnectionHandlerPtr handler);

  /**
   * get connection
   * @return : connection
   */
  const network::ConnectionPtr &getConnection() const;

  // IConnectionHandler callbacks
  void onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionEstablished(network::ConnectionPtr connection) override;
  void onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) override;

 private:

  friend network::Server;
  friend network::Client;

  enum ConnectionStatus {
    kConnectionDisconnected,
    kConnectionConnected,
    kConnectionConnecting
  };
  enum MessageStatus {
	kMessageIdle,
    kMessageWaiting,
  };

  network::ConnectionPtr connection;

  ConnectionStatus connectionStatus;
  MessageStatus messageStatus;

  // Custom
  network::ConnectionHandlerPtr customConnectionHandler;
  OnMessageFn onMessageFn;
  OnConnectionFn onConnectionFn;

  // Server manager
  static network::Manager serverManager;
  static ThreadPtr serverThread;
  network::ClientPtr client;

  // Client manager
  static network::Manager clientManager;
  static ThreadPtr clientThread;
  network::ServerPtr server;

};

}

#endif //PRODUCTION_LINE_CONTROL_MOCKNETWORK_H
