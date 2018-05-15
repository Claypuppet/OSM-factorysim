/*
 * NetworkSession.cpp
 *
 *  Created on: 12 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Connection.h"

#include <utils/Logger.h>

namespace Network
{

	using boost::asio::io_service;
	using boost::system::error_code;

	int Connection::sSessionCounter = 0;


	Connection::Connection(IConnectionHandler* handler, Connection::SocketType aSocket)
	:	mHandler(handler)
	,	mSocket(std::move(aSocket))
	,	mSessionId(++sSessionCounter)
	, 	mFlags(0)
	, 	mFWriting(false)
	{
	}

	Connection::~Connection()
	{
		try {
			disconnected(error_code());
		}
		catch(std::bad_weak_ptr& e){} // nothing we can do...
	}

	void Connection::readMessage()
	{
		mRecvMsg.clear();
		auto self = shared_from_this();
		boost::asio::async_read(mSocket, boost::asio::buffer((void*)&mRecvMsg.mHeader, sizeof(Message::MessageHeader)),
				[this, self](const error_code& error, size_t bytes_transferred) {
					this->handleHeaderRead(error, bytes_transferred);
		});
	}

	void Connection::handleHeaderRead(const error_code& error, size_t bytes_transferred)
	{
		auto self = shared_from_this();

		if (error) {
			disconnected(error);
			return;
		}

		if(bytes_transferred != sizeof(Message::MessageHeader)) {
			readMessage();
			return;
		}

		mRecvMsg.resizeBody(mRecvMsg.mHeader.mLength);
		if(!mRecvMsg.length()) {
			handleMessageRead();
			return;
		}

		boost::asio::async_read(mSocket, boost::asio::buffer((void*)&mRecvMsg.mBody[0], mRecvMsg.mBody.size()),
				[this, self](const error_code& error, size_t bytes_transferred) {
					this->handleBodyRead(error, bytes_transferred);
		});
	}

	void Connection::handleBodyRead(const error_code& error, size_t bytes_transferred)
	{
		auto self = shared_from_this();

		if (error) {

			disconnected(error);
			return;
		}

		/// hmm lost some bytes?? what can we do here?
		if(bytes_transferred < mRecvMsg.length())
			mRecvMsg.resizeBody(static_cast<uint16_t>(bytes_transferred));

		handleMessageRead();
	}

	void Connection::handleMessageRead()
	{
		auto self = shared_from_this();
		try {
			mHandler->onConnectionMessageReceived(self, mRecvMsg);
		}
		catch(std::exception& e) {
			readMessage();
			throw;
		}

		readMessage();
	}

	void Connection::writeNextQueuedMessage()
	{
		auto self = shared_from_this();
		std::lock_guard<std::recursive_mutex> lg(mMutex);
		if(mFWriting)
			return;
		if(!mOutMessageQue.empty()) {
			auto msg = mOutMessageQue.front();
			mOutMessageQue.pop_front();

			mFWriting = 1;

			boost::asio::async_write(mSocket,
					boost::asio::buffer((void*)&msg->mHeader, sizeof(Message::MessageHeader)),
					[msg, this, self](const error_code& error, size_t size){
					this->handleHeaderWritten(msg, error, size);
			});
		}
	}

	void Connection::writeMessage(const Message& aMessage)
	{
		auto messagePtr = std::make_shared<Message>(aMessage);
		std::lock_guard<std::recursive_mutex> lg(mMutex);
		mOutMessageQue.push_back(messagePtr);
		writeNextQueuedMessage();
	}

	void Connection::handleHeaderWritten(MessagePtr message, const error_code& error, size_t bytes_transferred)
	{
		auto self = shared_from_this();
		// TODO: verify size
		(void)bytes_transferred;

		if (error) {
			disconnected(error);
			return;
		}

		if(message->length()) {
			boost::asio::async_write(mSocket, boost::asio::buffer((void*)&message->mBody[0], message->length()),
													[message, this, self](const error_code& error, size_t size){
				this->handleBodyWritten(message, error, size);
			});
		}
		else
			handleMessageWritten(message);

	}

	void Connection::handleBodyWritten(MessagePtr message, const error_code& error, size_t bytes_transferred)
	{
		auto self = shared_from_this();

		// TODO: verify size
		(void)bytes_transferred;

		if (error) {
			disconnected(error);
			return;
		}

		handleMessageWritten(message);
	}

	void Connection::handleMessageWritten(MessagePtr message)
	{
		auto self = shared_from_this();

		mFWriting = false;
		mHandler->onConnectionMessageSent(self, *message);

		writeNextQueuedMessage();
	}

	void Connection::established()
	{
		if(mFEstablished || mFFailed || mFClose || mFDisconnect)
			return;
		auto self = shared_from_this();
		mFEstablished = 1;
		mHandler->onConnectionEstablished(self);
		readMessage();
	}

	void Connection::failed(const error_code& error)
	{
		if(mFFailed || mFEstablished)
			return;
		auto self = shared_from_this();
		mFFailed = 1;
		mHandler->onConnectionFailed(self, error);
	}

	const Connection::SocketType& Connection::getSocket() const
	{
		return mSocket;
	}

	int Connection::getSessionId()
	{
		return mSessionId;
	}

	void Connection::disconnected(const error_code& error)
	{
		auto self = shared_from_this();
		if(!mFDisconnect) {
			mFDisconnect = 1;
			if(mFEstablished)
				mHandler->onConnectionDisconnected(self, error);
		}

		close();
	}

	void Connection::close()
	{
		if(mFClose && mFDisconnect)
			return;
		auto self = shared_from_this();
		mFClose = 1;
		if(mFEstablished) {
			disconnected(error_code());
			mSocket.shutdown(SocketType::shutdown_both);
		}
		mSocket.close();
	}

	bool Connection::isConnected() const
	{
		return mFEstablished && !mFDisconnect;
	}

} // namespace Network


