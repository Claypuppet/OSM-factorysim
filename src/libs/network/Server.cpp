/*
 * NetworkServer.cpp
 *
 *  Created on: 12 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Server.h"
#include "Manager.h"

#include <utils/Logger.h>

namespace network {

Server::Server(Manager &manager, ConnectionHandlerPtr handler, uint16_t port, uint16_t maxClients)
	: mManager(manager),
	  mAcceptor(manager.getIOService()),
	  mSocket(manager.getIOService()),
	  mPort(port),
	  mMaxClients(maxClients),
	  mConnectionHandler(std::move(handler)),
	  mFStarted(ATOMIC_FLAG_INIT),
	  mFStopping(ATOMIC_FLAG_INIT),
	  mFStopped(true) {
}

Server::~Server() {
}

void Server::start() {
  if (mFStarted.test_and_set()) {
	return;
  }

  auto self = shared_from_this();
  tcp::endpoint endpoint(tcp::v4(), mPort);
  try {
	mAcceptor.open(endpoint.protocol());
	//if (reuse_addr)
	//std::cout << "Server binding to port: " << mPort << std::endl;
	mAcceptor.set_option(boost::asio::socket_base::reuse_address(true));
	mAcceptor.bind(endpoint);
	mAcceptor.listen();

	mFStopped = false;

	std::stringstream message;
	message << "----Server: accepting clients on port: " << mAcceptor.local_endpoint().port();

	utils::Logger::log(message.str());

	if (auto l = mServiceEventLister) {
	  // call this from a Network i/o thread (to keep it consistent with other callbacks)
	  mManager.getIOService().post([self, l]() {
		l->onServiceStarted(self);
	  });
	}

	asyncAccept();
  }
  catch (boost::system::system_error &error) {
	std::stringstream ss;
	ss << "Server: failed to start server on port: " << mPort << +" with error: " + error.code().message();
	std::string errorMsg = ss.str();
	std::cerr << errorMsg << std::endl;
	if (auto l = self->getServiceEventListener()) {
	  // call this from a Network i/o thread (to keep it consistent with other callbacks)
	  mManager.getIOService().post([self, errorMsg, l]() {
		l->onServiceError(self, errorMsg);
	  });
	}
	stop();
  }

}

void Server::stop() {
  if (mFStopping.test_and_set()) {
	return;
  }
  auto self = shared_from_this();
  if (!mFStopped) {
	if (auto l = mServiceEventLister) {
	  mManager.getIOService().post([self, l]() { l->onServiceStopping(self); });
	}
  }
  mAcceptor.close();
  if (!mFStopped) {
  	auto connections = mConnections;
	for (auto connection : connections) {
	  connection->close();
	}
	if (auto l = mServiceEventLister) {
	  mManager.getIOService().post([self, l]() { l->onServiceStopped(self); });
	}
  }
  mFStopped = true;
}

void Server::handleAccept(const error_code &error) {
  auto self = shared_from_this();
  if (!error) {
	error_code epError;
	Socket::endpoint_type endpoint(mSocket.remote_endpoint(epError));
	if (!epError) {
	  ConnectionPtr connectionPtr(std::make_shared<Connection>(this, std::move(mSocket)));
	  if (mConnections.size() < mMaxClients) {
		mConnections.insert(connectionPtr);
		connectionPtr->established();
	  } else {
		std::stringstream message;
		message << "----Server: dropping client server full";
		utils::Logger::log(message.str());
		connectionPtr->failed(error_code(boost::system::errc::connection_refused, boost::system::generic_category()));
	  }
	}
  }

  if (error) {
	// TODO: handle "fatal" errors which might cause an infinite loop asyncAccept -> error -> asyncAccept ... etc
	std::stringstream message;
	message << "----Server: failed to accept client. error: " << error.message();
	utils::Logger::log(message.str());
	if (mFStopped || !mSocket.is_open() || !mAcceptor.is_open()) {
	  return;
	}
  }

  asyncAccept();
}

bool Server::isRunning() const {
  return !mFStopped;
}

void Server::asyncAccept() {
  if (mConnections.size() >= mMaxClients) {
	return;
  }
  auto self = shared_from_this();
  mAcceptor.async_accept(mSocket, [self](const error_code &error) { self->handleAccept(error); });
}

void Server::onConnectionEstablished(ConnectionPtr connection) {
  auto self = shared_from_this();
  std::stringstream message;
  message << "----Server: connection established with: " << connection->getSocket().remote_endpoint();
  utils::Logger::log(message.str());
  if (auto h = mConnectionHandler) {
	mManager.getIOService().post([self, h, connection]() { h->onConnectionEstablished(connection); });
  }
}

void Server::onConnectionDisconnected(ConnectionPtr connection, const error_code &error) {
  auto self = shared_from_this();

  std::stringstream message;
  message << "----Server: lost connection with: " << connection->getSocket().remote_endpoint() <<
		  " (" << error.message() << ")";
  utils::Logger::log(message.str());
  if (auto h = mConnectionHandler) {
	mManager.getIOService().post([self, h, connection, error]() { h->onConnectionDisconnected(connection, error); });
  }
  bool doAccept = mConnections.size() >= mMaxClients;
  mConnections.erase(connection);
  if (doAccept && mConnections.size() < mMaxClients) {
	asyncAccept();
  }
}

void Server::onConnectionMessageReceived(ConnectionPtr connection, Message &message) {
  auto self = shared_from_this();
  if (auto h = mConnectionHandler) {
	h->onConnectionMessageReceived(connection, message);
  }
}

void Server::onConnectionMessageSent(ConnectionPtr connection, Message &message) {
  auto self = shared_from_this();
  if (auto h = mConnectionHandler) {
	h->onConnectionMessageSent(connection, message);
  }
}

ServiceEventListenerPtr Server::getServiceEventListener() const {
  return mServiceEventLister;
}

void Server::setServiceEventListener(ServiceEventListenerPtr listener) {
  auto old = mServiceEventLister;
  mServiceEventLister = listener;
}

ConnectionPtr Server::getConnection() const {
  if (!mConnections.empty()) {
	return *mConnections.begin();
  }
  return ConnectionPtr();
}

ConnectionHandlerPtr Server::getConnectionHandler() const {
  return mConnectionHandler;
}

void Server::setConnectionHandler(ConnectionHandlerPtr connectionHandler) {
  auto old = mConnectionHandler;
  mConnectionHandler = connectionHandler;
}

}


