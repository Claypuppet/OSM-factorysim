/*
 * NetworkSession.h
 *
 *  Created on: 12 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef NETWORKCONNECTION_H_
#define NETWORKCONNECTION_H_


#include "Message.h"
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

#include <boost/asio.hpp>
#include <mutex>
#include <list>

#pragma GCC diagnostic pop

namespace Network
{
	using boost::asio::io_service;
	using boost::system::error_code;
	using boost::asio::ip::tcp;
	//using boost::asio::placeholders;


	struct IConnectionHandler;


	class Connection : public std::enable_shared_from_this<Connection>
	{

		typedef tcp::socket SocketType;

	public:
		/**
		 * The constuctor
		 * @param handler : The connection handler
		 * @param socket : The socket
		 */
		Connection(IConnectionHandler* handler, SocketType socket);

		/**
		 * The destructor
		 */
		virtual ~Connection();

		/**
		 * A function to check if the connection is connected to its endpoint
		 * @return true when connected to its endpoint
		 */
		virtual bool isConnected() const;

		/**
		 * This function is called when the connection is established
		 */
		void established();

		/**
		 * This function is called when the connction failed to connect
		 * @param error : The error why the connection failed to connect
		 */
		void failed(const error_code& error);

		/**
		 * Closes the connection
		 */
		void close();

		/**
		 * Getter for the session id
		 * @return mSessionId
		 */
		int getSessionId();

		/**
		 * Getter for the socket
		 * @return mSocket
		 */
		const SocketType& getSocket() const;

		/**
		 * writeMessage will write the message in 2 a-sync writes, 1 for the header and 1 for the body.
		 * After each write a callback will be called that should handle the stuff just read.
		 * After writing the full message handleMessageWritten will be called.
		 *
		 * @see handle_header_written
		 * @see handle_body_written
		 * @see handleMessageWritten
		 */
		void writeMessage(Message& aMessage);


	private:

	    /**
	     * Writes the next message in the mOutMessageQueue
	     */
		void writeNextQueuedMessage();

		// The following functions should be protected or private
		// but the friend template syntax is not very friendly....

		/**
		 * readMessage will read the message in 2 a-sync reads, 1 for the header and 1 for the body.
		 * After each read a callback will be called that should handle the stuff just read.
		 * After reading the full message handleMessageRead will be called
		 * whose responsibilty it is to handle the message as a whole.
		 *
		 * @see handle_header_read
		 * @see handle_body_read
		 * @see handleMessageRead
		 */
		void readMessage();

		/**
		 * This function is called after the header bytes are read.
		 */
		void handleHeaderRead(const error_code& error, size_t  bytes_transferred);

		/**
		 * This function as called after the body bytes are read.
		 * Any error handling (throwing an exception ;-)) is done in this function and
		 * than the function with the same name but without the error is called.
		 */
		void handleBodyRead(const error_code& error,size_t bytes_transferred);

		/**
		 * This function is called after both the header and body bytes are read.
		 */
		void handleMessageRead();



		/**
		 * This function is called after the header bytes are written.
		 */
		void handleHeaderWritten(MessagePtr msg, const error_code& error, size_t bytes_transferred);

		/**
		 * This function is called after the body bytes are written.
		 */
		void handleBodyWritten(MessagePtr msg, const error_code& error, size_t bytes_transferred);

		/**
		 * This function is called after both the header and body bytes are written.
		 * Any error handling (throwing an exception ;-)) is done in this function and
		 * than the function with the same name but without the error is called.
		 */

		void handleMessageWritten(MessagePtr message);

        /**
         * This function is called when the connection disconnected
         * @param error : The errot why the connection was disconnected
         */
		void disconnected(const error_code& error);


	protected:
		static int sSessionCounter;
		IConnectionHandler* mHandler;
		SocketType mSocket;
		int mSessionId;
		union {
			struct {
				uint32_t mFFailed : 1;
				uint32_t mFEstablished : 1;
				uint32_t mFDisconnect : 1;
				uint32_t mFClose : 1;
			};
			uint32_t mFlags;
		};

		Message mRecvMsg;
		std::recursive_mutex mMutex;
		std::list<MessagePtr> mOutMessageQue;
		volatile bool mFWriting;

	};

	typedef std::shared_ptr<Connection> ConnectionPtr;


	struct IServiceEventListener;

	typedef std::shared_ptr<IServiceEventListener> ServiceEventListenerPtr;

	struct IService
	{
		virtual ~IService() = default;

		virtual void stop() = 0;
		virtual bool isRunning() const = 0;

		virtual ServiceEventListenerPtr getServiceEventListener() const = 0;
		virtual void setServiceEventListener(ServiceEventListenerPtr listener) = 0;
	};

	typedef std::shared_ptr<IService> ServicePtr;

	struct IServiceEventListener {
			virtual ~IServiceEventListener() = default;
			virtual void onServiceError(ServicePtr service, const std::string& message) { (void)service; (void)message;};
			virtual void onServiceStopping(ServicePtr service) { (void)service; };
			virtual void onServiceStopped(ServicePtr service) { (void)service; };
			virtual void onServiceStarted(ServicePtr service) { (void)service; };
	};


	struct IConnectionMessageReceivedHandler {
		virtual ~IConnectionMessageReceivedHandler() = default;
		virtual void onConnectionMessageReceived(ConnectionPtr connection, Message& message) = 0;
	};

	struct IConnectionMessageSendHandler {
		virtual ~IConnectionMessageSendHandler() = default;
		virtual void onConnectionMessageSent(ConnectionPtr connection, Message& message) = 0;
	};

	struct IConnectionMessageHandler : public IConnectionMessageReceivedHandler, public IConnectionMessageSendHandler  {
	};

	struct IConnectionHandler : public IConnectionMessageHandler
	{
			virtual ~IConnectionHandler() = default;
			virtual void onConnectionFailed(ConnectionPtr connection, const error_code& error) {(void)connection; (void)error; };
			virtual void onConnectionEstablished(ConnectionPtr connection) = 0;
			virtual void onConnectionDisconnected(ConnectionPtr connection, const error_code& error) = 0;
			virtual void onConnectionMessageReceived(ConnectionPtr connection, Message& message) = 0;
			virtual void onConnectionMessageSent(ConnectionPtr connection, Message& message) { (void)connection; (void)message; }
	};

	typedef std::shared_ptr<IConnectionHandler> ConnectionHandlerPtr;

	struct IConnectionService : public IService {
			virtual ConnectionPtr getConnection() const = 0;
			virtual ConnectionHandlerPtr getConnectionHandler() const = 0;
			virtual void setConnectionHandler(ConnectionHandlerPtr connectionHandler) = 0;
	};


} // namespace Network



#endif /* NETWORKCONNECTION_H_ */
