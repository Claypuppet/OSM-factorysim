//
// Created by klei on 4/19/18.
//

#ifndef PRODUCTION_LINE_CONTROL_NetworkCOMPONENT_H
#define PRODUCTION_LINE_CONTROL_NetworkCOMPONENT_H

#include <patterns/notifyobserver/Notifier.hpp>
#include "network/Connection.h"

namespace Communication {
class NetworkComponent : public Network::IConnectionHandler, public patterns::NotifyObserver::Notifier {
 public:
  NetworkComponent();
  ~NetworkComponent() = default;

  /**
   * A function that sends a message to production control to register this machine
   * @param machineId : The id of the machine
   */
  void sendRegisterMachineMessage(uint16_t machineId);

  /**
       * Send status update: ready for instructions
       */
  void sendStatusUpdateReady();

  /**
   * Send status update: started procssing
   */
  void sendStatusUpdateStarted();

  /**
   * Send status update: done processing
   */
  void sendStatusUpdateDone();

  /**
   * Send response: OK
   */
  void sendResponseOK();

  /**
   * Send response: NOK
   * @param errorCode : error code
   */
  void sendResponseNOK(const uint16_t errorCode);
 private:
  void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionEstablished(Network::ConnectionPtr connection) override;
  void onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;
  /**
   * checks for connection with PC
   * @return
   */
  bool isConnected();

  /**
   * checks for connection and sends message
   * @param message
   */
  void sendMessage(Network::Message &message);

  Network::ConnectionPtr mConnection;

  void handleReconfigureMessage();
  void handleProcessProductMessage();
  void handleProcessReconfigureMessage(Network::Message &message);

};
}

#endif //PRODUCTION_LINE_CONTROL_NetworkCOMPONENT_H
