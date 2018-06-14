//
// Created by klei on 4/19/18.
//

#ifndef PRODUCTION_LINE_CONTROL_NetworkCOMPONENT_H
#define PRODUCTION_LINE_CONTROL_NetworkCOMPONENT_H

#include <patterns/notifyobserver/Notifier.hpp>
#include <models/Machine.h>
#include "network/Connection.h"

namespace Communication {

/**
 * Network component that handles messages for application
 */
class NetworkComponent : public network::IConnectionHandler, public patterns::notifyobserver::Notifier {
 public:
  NetworkComponent();
  ~NetworkComponent() = default;
  NetworkComponent(const NetworkComponent&) = delete;

  /**
   * A function that sends a message to production control to register this machine
   * @param machineId : The id of the machine
   */
  void sendRegisterMachineMessage(uint16_t machineId);

  /**
   * Send status update
   */
  void sendStatusUpdate(models::Machine::MachineStatus status);

  /**
   * Send response: NOK
   * @param errorCode : error code
   */
  void sendResponseNOK(models::Machine::MachineErrorCode errorCode);

  /**
   * Sends a message to production control to tell this machine took products from its input buffer
   */
  void sendProductTakenFromBufferMessage();

  /**
   * Sends a message to production control to tell this machine added products to its output buffer
   */
  void sendProductAddedToBufferMessage();
 private:
  void onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionEstablished(network::ConnectionPtr connection) override;
  void onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) override;
  /**
   * checks for connection with PC
   * @return
   */
  bool isConnected();

  /**
   * checks for connection and sends message
   * @param message
   */
  void sendMessage(network::Message &message);

  network::ConnectionPtr mConnection;

  void handleProcessProductMessage();
  void handleReconfigureMessage(network::Message &message);

};

typedef std::shared_ptr<NetworkComponent> NetworkComponentPtr;
}

#endif //PRODUCTION_LINE_CONTROL_NetworkCOMPONENT_H
