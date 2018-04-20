/*
 * NetworkServer.h
 *
 *  Created on: 12 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef NETWORKSERVER_H_
#define NETWORKSERVER_H_


#include "Connection.h"

#include <stdint.h>
#include <memory>
#include <set>
#include <atomic>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

#include <boost/asio.hpp>

#pragma GCC diagnostic pop

namespace network
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

		virtual ~Server();

		void start();

		virtual void stop() override;
		virtual bool isRunning() const override;

		virtual ServiceEventListenerPtr getServiceEventListener() const override;
		virtual void setServiceEventListener(ServiceEventListenerPtr listener) override;

		virtual ConnectionPtr getConnection() const override;
		virtual ConnectionHandlerPtr getConnectionHandler() const override;
		virtual void setConnectionHandler(ConnectionHandlerPtr connectionHandler) override;

		uint16_t getMaxClients() const { return mMaxClients; };
		void setMaxClients(uint16_t maxClients) {  mMaxClients = maxClients; }


	protected:

		friend class Manager;

		Server(Manager& manager, ConnectionHandlerPtr handler, uint16_t port, uint16_t maxClients = kDefaultMaxClients);

		void asyncAccept();

		virtual void handleAccept(const error_code& error);

		virtual void onConnectionEstablished(ConnectionPtr connection);
		virtual void onConnectionDisconnected(ConnectionPtr connection, const error_code& error);
		virtual void onConnectionMessageReceived(ConnectionPtr connection, Message& message);
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

} // namespace network



#endif /* NETWORKSERVER_H_ */
