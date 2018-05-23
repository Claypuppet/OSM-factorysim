/*
 * NetworkClient.h
 *
 *  Created on: 15 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef NETWORKCLIENT_H_
#define NETWORKCLIENT_H_

#include "Connection.h"

#include <memory>
#include <string>
#include <atomic>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

#include <boost/asio.hpp>

#pragma GCC diagnostic pop

namespace network {

using boost::system::error_code;
using boost::asio::io_service;

class Connection;
class Manager;

class Client : public IConnectionService, public IConnectionHandler, public std::enable_shared_from_this<Client> {
  friend Manager;

 public:

  typedef boost::asio::ip::tcp::socket SocketType;
  typedef boost::asio::ip::tcp::resolver ResolverType;
  typedef boost::asio::ip::tcp::endpoint EndpointType;

  typedef std::shared_ptr<SocketType> SocketPtr;

 public:

  /**
   * The destructor
   */
  virtual ~Client();

  /**
   * Starts the client
   */
  void start();

  /**
   * Stops the client
   */
  virtual void stop() override;

  /**
   * A function to check if the client is running
   * @return !mFStopped
   */
  virtual bool isRunning() const override;

  /**
   * Getter for the serviceEventListener
   * @return mServiceEventLister
   */
  virtual ServiceEventListenerPtr getServiceEventListener() const override;

  /**
   * Sets the serviceEventListener
   * @param listener : The new listener
   */
  virtual void setServiceEventListener(ServiceEventListenerPtr listener) override;

  /**
   * Returns the connection
   * @return mConnection
   */
  virtual ConnectionPtr getConnection() const override;

  /**
   * Returns the connection handler
   * @return mConnectionHandler
   */
  virtual ConnectionHandlerPtr getConnectionHandler() const override;

  /**
   * Sets the connection handler
   * @param connectionHandler : The new connection handler
   */
  virtual void setConnectionHandler(ConnectionHandlerPtr connectionHandler) override;

 protected:

  /**
   * The constructor
   * @param manager : The manager
   * @param handler : The connection handler
   * @param host : The ip-address of the host the client connects to
   * @param port : The port of the the host the client connects to
   */
  Client(Manager &manager, ConnectionHandlerPtr handler, const std::string &host, uint16_t port);

  void asynResolve();
  virtual void handleResolve(ResolverType::iterator &iter, const error_code &error);

  void asyncConnect(EndpointType endpoint);
  virtual void handleConnect(const EndpointType &endpoint, const error_code &error);

  /**
   * Handler for when a connection is established
   * @param connection : The established connection
   */
  virtual void onConnectionEstablished(ConnectionPtr connection);

  /**
   * Handler for when a connection disconnects
   * @param connection : The disconnected connection
   * @param error : The error that disconnected the connection
   */
  virtual void onConnectionDisconnected(ConnectionPtr connection, const error_code &error);

  /**
   * Handler for when a message is received
   * @param connection : The connection that send the message
   * @param message : The message that was received
   */
  virtual void onConnectionMessageReceived(ConnectionPtr connection, Message &message);

  /**
   * Handler for when a message is send
   * @param connection : The connection the message is sent to
   * @param message : The message that was sent
   */
  virtual void onConnectionMessageSent(ConnectionPtr connection, Message &message);

 protected:
  Manager &mManager;
  std::string mHost;
  uint16_t mPort;
  ResolverType mResolver;
  SocketType mSocket;
  ServiceEventListenerPtr mServiceEventLister;
  ConnectionPtr mConnection;
  ConnectionHandlerPtr mConnectionHandler;
  // flags
  std::atomic_flag mFStarted;
  std::atomic_flag mFStopping;
  bool mFStopped;

};

} // namespace Network

#endif /* NETWORKCLIENT_H_ */
