//
// Created by don on 28-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_LIVENETWORK_H
#define PRODUCTION_LINE_CONTROL_LIVENETWORK_H

#include <network/Connection.h>
#include <patterns/notifyobserver/Notifier.hpp>
namespace live {

/**
 * Connection handler for live feed
 */
class LiveNetwork : public network::IConnectionHandler, patterns::notifyobserver::Notifier{
 public:
  LiveNetwork() = default;
 private:
  void onConnectionEstablished(network::ConnectionPtr connection) override;
  void onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) override;
};

}

#endif //PRODUCTION_LINE_CONTROL_LIVENETWORK_H
