//
// Created by don on 19-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_COMMNET_H
#define PRODUCTION_LINE_CONTROL_COMMNET_H

#include <patterns/notifyobserver/Notifier.hpp>
#include "network/Connection.h"
#include "Application.h"
#include "NetworkMapper.h"

namespace communication {

/**
 * Network component for an application that handles messages and connections
 */
class ConnectionHandler :
	public network::IConnectionHandler,
	public patterns::notifyobserver::Notifier,
	public NetworkMapper {
 public:
  ConnectionHandler() = default;
  virtual ~ConnectionHandler() = default;

 private:

  void onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) override;

  void onConnectionEstablished(network::ConnectionPtr connection) override;

  void onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) override;

  /**
   * Handles incoming messages
   * @param connection : The connection that send the message
   * @param message The : incoming message
   */
  void onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) override;

  void onConnectionMessageSent(network::ConnectionPtr connection, network::Message &message) override;

  /**
   * Make notification for registering a machine
   * @param connection : The connection of the machine
   * @param message : The incoming message
   */
  void handleRegisterMachine(network::ConnectionPtr connection, network::Message &message);

  /**
   * Makes a notification to indicate a machine send an OK message
   * @param connection : The connection that send the message
   * @param message : incoming message, contains the status update
   */
  void handleOK(network::ConnectionPtr connection, network::Message &message);

  /**
   * Makes a notification to indicate a machine send a NOK message
   * @param connection : The connection that send the message
   * @param message : The incoming message, contains the error code
   */
  void handleNOK(network::ConnectionPtr connection, network::Message &message);

  /**
   * Makes a notification to indicate a machine send a product added message
   * @param connection : The connection that send the message
   */
   void handleProductAddedToBuffer(network::ConnectionPtr connection, network::Message &message);

   /**
    * Makes a notification to indicate a machine send a product taken message
    * @param connection : The connection that send the message
    */
   void handleProductTakenFromBuffer(network::ConnectionPtr connection, network::Message &message);
};
}

#endif //PRODUCTION_LINE_CONTROL_COMMNET_H
