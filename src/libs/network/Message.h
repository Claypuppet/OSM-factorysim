/*
 * Message.h
 *
 *  Created on: 29 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef NETWORK_MESSAGE_H_
#define NETWORK_MESSAGE_H_

#include <string>
#include <memory>

namespace Network
{
	typedef std::size_t size_t;
	typedef uint8_t MessageType;
	typedef uint16_t MessageLength;

	struct Message
	{
			typedef std::string MessageBody;


			struct MessageHeader
			{
					MessageHeader() :
						mType(0), mLength(0)
					{
					}

					MessageHeader(MessageType aMessageType,MessageLength aMessageLength)
					:	mType( aMessageType)
					, 	mLength( aMessageLength)
					{
					}


					MessageLength getHeaderLength() const
					{
						return 24;
					}

					MessageType getMessageType() const
					{
						return mType;
					}

					MessageLength getMessageLength() const
					{
						return mLength;
					}

					std::string asString() const
					{
						return "";
					}

					MessageType mType;
					MessageLength mLength;
			};

			Message()
			{
			}

			Message(MessageType aMessageType)
			:	mHeader(aMessageType, 0)
			{
			}

			Message(MessageType aMessageType, const std::string& aMessage)
			: mHeader(aMessageType, static_cast<MessageLength>(aMessage.size()))
			, mBody(aMessage)
			{

			}

			Message( const Message& aMessage)
			:	mHeader(aMessage.getHeader())
			, 	mBody(aMessage.mBody)
			{
			}

			virtual ~Message()
			{
			}

			MessageHeader getHeader() const
			{
				return mHeader;
			}


			MessageType getMessageType() const
			{
				return mHeader.mType;
			}

			void setMessageType(MessageType aMessageType)
			{
				mHeader.mType = aMessageType;
			}

			const MessageBody& getBody() const
			{
				return mBody;
			}

			void setBody( const std::string& aBody)
			{
				mBody = aBody;
			}

			void resizeBody(uint16_t length)
			{
				mBody.resize(length);
			}

			MessageLength length() const
			{
				return static_cast<MessageLength>(mBody.length());
			}

			void clear()
			{
				mHeader = MessageHeader();
				mBody.clear();
			}


			MessageHeader mHeader;
			MessageBody mBody;
	};

	typedef std::shared_ptr<Message> MessagePtr;

} /* namespace Network */

#endif /* NETWORK_MESSAGE_H_ */
