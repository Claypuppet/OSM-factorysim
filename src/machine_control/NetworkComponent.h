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

  Network::ConnectionPtr getConnection();
  /**
   * sends a message to PC to find the right
   * @param machineId
   */
  void sendRegisterMachineMessage(uint16_t machineId);

 private:
  void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionEstablished(Network::ConnectionPtr connection) override;
  void onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;
  bool isConnected();
  void sendMessage(Network::Message &msg);

  Network::ConnectionPtr mConnection;

  void handleReconfigureMessage();
  void handleProcessProductMessage();

};
}

#endif //PRODUCTION_LINE_CONTROL_NetworkCOMPONENT_H
