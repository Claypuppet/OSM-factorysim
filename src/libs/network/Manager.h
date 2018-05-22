/*
 * Network.h
 *
 *  Created on: 12 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include <cstdint>
#include <string.h>
#include <string>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

#ifdef __GNUC__
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wconversion"
#endif

#include <boost/asio.hpp>

#ifdef __GNUC__
#	pragma GCC diagnostic pop
#endif

typedef std::shared_ptr<std::thread> ThreadPtr;

namespace network {
using boost::asio::io_service;
using boost::system::error_code;

class Server;

class Client;

typedef std::shared_ptr<Server> ServerPtr;
typedef std::shared_ptr<Client> ClientPtr;

struct IConnectionHandler;
typedef std::shared_ptr<IConnectionHandler> ConnectionHandlerPtr;

class Manager {
 public:

  /**
   * The constructor
   */
  Manager();

  /**
   * The destructor
   */
  virtual ~Manager();

  /**
   * Returns the io_service
   * @return *mServicePtr.get()
   */
  io_service &getIOService() { return *mServicePtr.get(); }

  /**
   * Creates a new client
   * @param handler : The connection handler for the client
   * @return The created client
   */
  ClientPtr createClient(ConnectionHandlerPtr handler);

  /**
   * Creates a new server
   * @param handler : The connection handler for the server
   * @param maxClients : The maximum amount of clients that can connect to the server
   * @return The created server
   */
  ServerPtr createServer(ConnectionHandlerPtr handler, uint16_t maxClients);

  /**
   * Getter for the client stored in the Manager
   * @return mClient
   */
  ClientPtr getClient() { return mClient; }

  /**
   * Getter for the server stored in the Manager
   * @return mServer
   */
  ServerPtr getServer() { return mServer; }

  /**
   * Starts running the service
   */
  void runService();

  /**
   * Starts the service thread
   * @return Pointer to the thread the server is running on
   */
  ThreadPtr runServiceThread();

  /**
   * Stops the manager
   */
  void stop();

  /**
   * Sets the remoteHost, remotePort and localPort
   * @param remoteIpAddress : New ip address of host
   * @param remotePort : New port of host
   * @param localPort : New port of manager
   */
  void setSettings(std::string remoteIpAddress, std::string remotePort, std::string localPort);

  /**
   * Function to get the remoteHost
   * @return The ip-address of the host
   */
  const std::string &getRemoteHost() const;

  /**
   * Sets new ip-address of host
   * @param host : New ip-address of host
   * @return instance of itself
   */
  Manager &setRemoteHost(const std::string &host);

  /**
   * Getter to get the port of the host
   * @return mRemotePort
   */
  uint16_t getRemotePort() const;

  /**
   * Sets new port of host
   * @param port : New port of the host
   * @return instance of itself
   */
  Manager &setRemotePort(uint16_t port);

  /**
   * Getter to get the port the manager is running on
   * @return mLocalPort
   */
  uint16_t getLocalPort() const;

  /**
   * Sets a new port for the manager
   * @param port : The new port
   * @return instance of itself
   */
  Manager &setLocalPort(uint16_t port);

 protected:

  /**
   * Function to handle a signal
   * @param error : The error code
   * @param signal : The signal to handle
   */
  virtual void handleSingnal(error_code &error, int signal);

 protected:
  std::mutex mMutex;
  std::shared_ptr<io_service> mServicePtr;
  std::unique_ptr<io_service::work> mServicerWorkPtr;
  ThreadPtr mServiceThread;
  ServerPtr mServer;
  ClientPtr mClient;
  bool mFStopping;
  bool mFStopped;

  std::string mRemoteHost;
  uint16_t mRemotePort;
  uint16_t mLocalPort;
};

} // namespace Network



#endif /* NETWORK_MANAGER_H_ */
