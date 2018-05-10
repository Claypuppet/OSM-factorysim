/*
 * NetworkServer.h
 *
 *  Created on: 12 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef NETWORKSERVER_H_
#define NETWORKSERVER_H_


#include "Connection.h"

#include <cstdint>
#include <memory>
#include <set>
#include <atomic>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

#include <boost/asio.hpp>

#pragma GCC diagnostic pop

namespace Network
{

	using boost::system::error_code;
	using boost::asio::io_service;
	using boost::asio::ip::tcp;

	class Connection;
	class Manager;

	class Server : public IConnectionService, public IConnectionHandler, public std::enable_shared_from_this<Server>
	{
	public:
		typedef std::shared_ptr<Connection> ConnectionPtr;
		typedef std::set<ConnectionPtr> ClientConnections;
		typedef tcp::acceptor Acceptor;
		typedef tcp::socket Socket;

		constexpr static const uint16_t kDefaultMaxClients = 16;

		/**
		 * Destructor
		 */
		virtual ~Server();

		/**
		 * Starts the server
		 */
		void start();

		/**
		 * Stops the server
		 */
		virtual void stop() override;

		/**
		 * A function to check if the server is running
		 * @return True when the server is running
		 */
		virtual bool isRunning() const override;

		/**
		 * Returns the service event listener of the server
		 * @return mServiceEventLister
		 */
		virtual ServiceEventListenerPtr getServiceEventListener() const override;

		/**
		 * Sets new service event listener
		 * @param listener : The new service event listener
		 */
		virtual void setServiceEventListener(ServiceEventListenerPtr listener) override;

		/**
		 * Returns the connections with clients
		 * @return mConnections
		 */
		virtual ConnectionPtr getConnection() const override;

		/**
		 * Returns the connection handler
		 * @return mConnectionHandler
		 */
		virtual ConnectionHandlerPtr getConnectionHandler() const override;

		/**
		 * Sets a new connection handler
		 * @param connectionHandler : The new connection handler
		 */
		virtual void setConnectionHandler(ConnectionHandlerPtr connectionHandler) override;

		/**
		 * Returns the maximum amount of clients that can connect to this server
		 * @return mMaxClients
		 */
		uint16_t getMaxClients() const { return mMaxClients; };

		/**
		 * Sets a new maximum amount of clients that can connect to this server
		 * @param maxClients : New maximum amount of clients
		 */
		void setMaxClients(uint16_t maxClients) {  mMaxClients = maxClients; }


	protected:

		friend class Manager;

		/**
		 * Constructor
		 * @param manager : The manager the server is stored in
		 * @param handler : The connection handler
		 * @param port : The port the server is running on
		 * @param maxClients : The maximum amount of clients that can connect to the server
		 */
		Server(Manager& manager, ConnectionHandlerPtr handler, uint16_t port, uint16_t maxClients = kDefaultMaxClients);

		void asyncAccept();

		virtual void handleAccept(const error_code& error);

		/**
		 * A function that is called when a new connection is established
		 * @param connection : The new connection that is established
		 */
		virtual void onConnectionEstablished(ConnectionPtr connection);

		/**
		 * A function that is called when a connection disconnected
		 * @param connection : The connection that disconnected
		 * @param error : The error that caused the disconnection
		 */
		virtual void onConnectionDisconnected(ConnectionPtr connection, const error_code& error);

		/**
		 * A function that is called when a message is received
		 * @param connection : The connection that send the message
		 * @param message : The received message
		 */
		virtual void onConnectionMessageReceived(ConnectionPtr connection, Message& message);

		/**
		 * A function that is called when a message is sent
		 * @param connection : The connection the message is sent to
		 * @param message : The message that is sent
		 */
		virtual void onConnectionMessageSent(ConnectionPtr connection, Message& message);


	private:
		Manager& mManager;
		Acceptor mAcceptor;
		Socket mSocket;
		uint16_t mPort;
		uint16_t mMaxClients;
		ClientConnections mConnections;
		ConnectionHandlerPtr mConnectionHandler;
		ServiceEventListenerPtr mServiceEventLister;
		std::atomic_flag mFStarted;
		std::atomic_flag mFStopping;
		bool mFStopped;
	};

} // namespace Network



#endif /* NETWORKSERVER_H_ */
