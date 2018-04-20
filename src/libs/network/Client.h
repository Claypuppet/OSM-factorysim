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

namespace network
{

	using boost::system::error_code;
	using boost::asio::io_service;

	class Connection;
	class Manager;



	class Client : public IConnectionService, public IConnectionHandler, public std::enable_shared_from_this<Client>
	{
		friend Manager;

	public:

		typedef boost::asio::ip::tcp::socket SocketType;
		typedef boost::asio::ip::tcp::resolver ResolverType;
		typedef boost::asio::ip::tcp::endpoint EndpointType;

		typedef std::shared_ptr<SocketType> SocketPtr;


	public:

		virtual ~Client();

		void start();
		virtual void stop() override;
		virtual bool isRunning() const override;

		virtual ServiceEventListenerPtr getServiceEventListener() const override;
		virtual void setServiceEventListener(ServiceEventListenerPtr listener) override;

		virtual ConnectionPtr getConnection() const override;
		virtual ConnectionHandlerPtr getConnectionHandler() const override;
		virtual void setConnectionHandler(ConnectionHandlerPtr connectionHandler) override;


	protected:

		Client(Manager& manager, ConnectionHandlerPtr handler, const std::string& host, uint16_t port);


		void asynResolve();
		virtual void handleResolve(ResolverType::iterator& iter, const error_code& error);


		void asyncConnect(EndpointType endpoint);
		virtual void handleConnect(const EndpointType& endpoint, const error_code& error);

		virtual void onConnectionEstablished(ConnectionPtr connection);
		virtual void onConnectionDisconnected(ConnectionPtr connection, const error_code& error);
		virtual void onConnectionMessageReceived(ConnectionPtr connection, Message& message);
		virtual void onConnectionMessageSent(ConnectionPtr connection, Message& message);




	protected:
		Manager&		mManager;
		std::string 	mHost;
		uint16_t		mPort;
		ResolverType	mResolver;
		SocketType		mSocket;
		ServiceEventListenerPtr mServiceEventLister;
		ConnectionPtr	mConnection;
		ConnectionHandlerPtr mConnectionHandler;
		// flags
		std::atomic_flag mFStarted;
		std::atomic_flag mFStopping;
		bool 			 mFStopped;

	};

} // namespace network

#endif /* NETWORKCLIENT_H_ */
