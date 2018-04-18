/*
 * NetworkClient.cpp
 *
 *  Created on: 15 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Client.h"

#include "Connection.h"
#include "Manager.h"


#include <stdexcept>
#include <iostream>
#include <sstream>



namespace network {

	Client::Client(Manager& manager, ConnectionHandlerPtr handler, const std::string& host, uint16_t port)
		: mManager(manager)
		, mHost(host)
		, mPort(port)
		, mResolver(manager.getIOService())
		, mSocket(manager.getIOService())
		, mConnectionHandler(handler)
		, mFStarted(ATOMIC_FLAG_INIT)
		, mFStopping(ATOMIC_FLAG_INIT)
	    , mFStopped(true)
	{
	}

	Client::~Client()
	{
	}

	void Client::stop()
	{
		if(mFStopping.test_and_set())
			return;
		io_service& ios = mManager.getIOService();
		auto self = shared_from_this();
		if(auto l = mServiceEventLister)
			ios.post([l, self](){l->onServiceStopping(self);});
		if(auto c = mConnection)
			c->close();
		mConnection.reset();
		mResolver.cancel();
		mSocket.close();
		mFStopped = true;
		if(auto l = mServiceEventLister)
			ios.post([l, self](){l->onServiceStopped(self);});
	}


	bool Client::isRunning() const
	{
		return !mFStopped;
	}

	void Client::start()
	{
		if(mFStarted.test_and_set()) {
			std::cerr << "Client: start called more then once. ignored!" << std::endl;
			return;
		}
		mFStopped = false;
		asynResolve();
	}

	void Client::handleResolve(ResolverType::iterator& iter, const error_code& error)
	{
		auto self = shared_from_this();
		if(error || iter == ResolverType::iterator()) {
			std::string errormsg =  std::string("Client: failed to resolve host: '") + mHost + "' with error: " + error.message();
			std::cerr << errormsg << std::endl;
			if(auto l = mServiceEventLister)
				mManager.getIOService().post([l, self, errormsg](){ l->onServiceError(self, errormsg); });
			stop();
			return;
		}

		auto entry = *iter;
		EndpointType endpoint(entry.endpoint());

		std::cout << "Client: resolved host: '" << entry.host_name() << "' to: '" << endpoint << '\'' << std::endl;

		asyncConnect(endpoint);

	}

	void Client::asynResolve()
	{
		auto self = shared_from_this();
		mResolver.async_resolve(
				ResolverType::query(boost::asio::ip::tcp::v4(), mHost, std::to_string(mPort)),
				[self](const error_code& error, ResolverType::iterator iter){
					self->handleResolve(iter, error);
				}
		);
	}



	void Client::handleConnect(const EndpointType& endpoint, const error_code& error)
	{
		auto self = shared_from_this();
		mConnection = std::make_shared<Connection>(this, std::move(mSocket));
		if(error) {
			auto cp = mConnection;
			std::stringstream ss;
			ss << "Client: connection to: " << endpoint << "' failed with error: " + error.message();
			std::string errorMsg = ss.str();
			std::cerr << errorMsg << std::endl;
			if(auto l = mServiceEventLister)
				mManager.getIOService().post([l, self, errorMsg](){l->onServiceError(self, errorMsg); });
			mConnection->failed(error);
			stop();
			return;
		}
		else
			mConnection->established();
	}


	void Client::asyncConnect(EndpointType endpoint)
	{
		auto self = shared_from_this();
		mSocket.async_connect(endpoint, [self, endpoint](const error_code& error){
			return self->handleConnect(endpoint, error);
		});
	}

	void Client::onConnectionEstablished(ConnectionPtr connection)
	{
		auto self = shared_from_this();
		std::cout << "Client: connection established with: " << connection->getSocket().remote_endpoint() << std::endl;
		if(auto h = mConnectionHandler)
			mConnectionHandler->onConnectionEstablished(connection);
		if(auto l = mServiceEventLister)
			l->onServiceStarted(self);
	}

	void Client:: onConnectionDisconnected(ConnectionPtr connection, const error_code& error)
	{
		auto self = shared_from_this();
		std::cout << "Client: connection with: " << connection->getSocket().remote_endpoint() <<
				" disconnected (" << error.message() << ")" << std::endl;
		if(auto h = mConnectionHandler)
			h->onConnectionDisconnected(connection, error);
		stop();

	}

	void Client::onConnectionMessageReceived(ConnectionPtr connection, Message& message)
	{
		if(auto h = mConnectionHandler)
			h->onConnectionMessageReceived(connection, message);
	}

	void Client::onConnectionMessageSent(ConnectionPtr connection, Message& message)
	{
		if(auto h = mConnectionHandler)
			h->onConnectionMessageSent(connection, message);
	}


	ServiceEventListenerPtr Client::getServiceEventListener() const
	{
		return mServiceEventLister;
	}

	void Client::setServiceEventListener(ServiceEventListenerPtr listener)
	{
		auto old = mServiceEventLister;
		mServiceEventLister = listener;
	}

	ConnectionPtr Client::getConnection() const
	{
		return mConnection;
	}

	ConnectionHandlerPtr Client::getConnectionHandler() const
	{
		return mConnectionHandler;
	}


	void Client::setConnectionHandler(ConnectionHandlerPtr connectionHandler)
	{
		auto old = mConnectionHandler;
		mConnectionHandler = connectionHandler;
	}

} // namespace network


