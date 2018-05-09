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
				    /**
				    * Default constructor
				    */
					MessageHeader() :
						mType(0), mLength(0)
					{
					}

					/**
					 * Constructor
					 * @param aMessageType : Type of message
					 * @param aMessageLength : Length of message
					 */
					MessageHeader(MessageType aMessageType,MessageLength aMessageLength)
					:	mType( aMessageType)
					, 	mLength( aMessageLength)
					{
					}

					/**
					 * Returns the length of the header
					 * @return 24
					 */
					MessageLength getHeaderLength() const
					{
						return 24;
					}

					/**
					 * Returns the type of the message
					 * @return mType
					 */
					MessageType getMessageType() const
					{
						return mType;
					}

					/**
					 * Returns the length of the message
					 * @return mLength
					 */
					MessageLength getMessageLength() const
					{
						return mLength;
					}

					/**
					 * Returns message as string
					 * @return ""
					 */
					std::string asString() const
					{
						return "";
					}

					MessageType mType;
					MessageLength mLength;
			};

			/**
			 * Default constructor
			 */
			Message()
			{
			}

			/**
			 * Constructor
			 * @param aMessageType : Type of message
			 */
			Message(MessageType aMessageType)
			:	mHeader(aMessageType, 0)
			{
			}

			/**
			 * Constructor
			 * @param aMessageType : Type of message
			 * @param aMessage : Body of message
			 */
			Message(MessageType aMessageType, const std::string& aMessage)
			: mHeader(aMessageType, static_cast<MessageLength>(aMessage.size()))
			, mBody(aMessage)
			{

			}

			/**
			 * Copy constructor
			 * @param aMessage : Message to copy
			 */
			Message( const Message& aMessage)
			:	mHeader(aMessage.getHeader())
			, 	mBody(aMessage.mBody)
			{
			}

			/**
			 * Destructor
			 */
			virtual ~Message()
			{
			}

			/**
			 * Returns header of message
			 * @return mHeader
			 */
			MessageHeader getHeader() const
			{
				return mHeader;
			}

			/**
			 * Returns type of message
			 * @return mHeader.mType
			 */
			MessageType getMessageType() const
			{
				return mHeader.mType;
			}

			/**
			 * Sets new type of message
			 * @param aMessageType : New type of the message
			 */
			void setMessageType(MessageType aMessageType)
			{
				mHeader.mType = aMessageType;
			}

			/**
			 * Returns the body of the message
			 * @return mBody
			 */
			const MessageBody& getBody() const
			{
				return mBody;
			}

			/**
			 * Sets a new body of the message
			 * @param aBody : New body
			 */
			void setBody( const std::string& aBody)
			{
				mBody = aBody;
			}

			/**
			 * A function to resize the body length
			 * @param length : The length to resize too
			 */
			void resizeBody(uint16_t length)
			{
				mBody.resize(length);
			}

			/**
			 * Returns the length of the message is bytes
			 * @return length of message
			 */
			MessageLength length() const
			{
				return static_cast<MessageLength>(mBody.length());
			}

			/**
			 * A function to clear the message type and message body
			 */
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
