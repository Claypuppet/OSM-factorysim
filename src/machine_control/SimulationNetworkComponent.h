#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONSimulationNetworkComponent_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONSimulationNetworkComponent_H

// standard library includes
// -

// libary includes
#include <patterns/notifyobserver/Notifier.hpp>
#include <network/Connection.h>
#include <models/Machine.h>

// other includes
// -

namespace SimulationCommunication {

class SimulationNetworkComponent;
typedef std::shared_ptr<SimulationNetworkComponent> SimulationNetworkComponentPtr;

class SimulationNetworkComponent :
    public Network::IConnectionHandler,
    public patterns::NotifyObserver::Notifier {
 public:
  SimulationNetworkComponent() = default;
  virtual ~SimulationNetworkComponent() = default;
  /**
   * A function that sends a message to production control to register this machine
   * @param machineId : The id of the machine
   */
  void sendRegisterMessage(const uint16_t machineId);

  bool isConnected();

 private:
  void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionEstablished(Network::ConnectionPtr connection) override;
  void onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;

  /**
   * Send a message over the connection
   * @param message : message to send
   */
  void sendMessage(const Network::Message &message);

  /**
   * Handles new machine info receive
   * @param machine
   */
  void onSimulationMachineInfoReceived(models::MachinePtr machinePtr);

  /**
   * Handles machine turn on command
   */
  void onTurnOnReceived();

  /**
   * Handles machine turn off command
   */
  void onTurnOffReceived();

  Network::ConnectionPtr mConnection;
};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONSimulationNetworkComponent_H
