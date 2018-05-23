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
	public network::IConnectionHandler,
	public patterns::notifyobserver::Notifier {
 public:
  SimulationNetworkComponent() = default;
  virtual ~SimulationNetworkComponent() = default;

  /**
   * A function that sends a message to production control to register this machine
   * @param machineId : The id of the machine
   */
  void sendRegisterMessage(const uint16_t machineId);

  /**
   * A function that sends a message to production control that the machine is ready for simulation
   */
  void sendMachineReadyMessage();

  bool isConnected();

 private:
  void onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionEstablished(network::ConnectionPtr connection) override;
  void onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) override;
  void onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) override;

  /**
   * Send a message over the connection
   * @param message : message to send
   */
  void sendMessage(const network::Message &message);

  /**
   * Handles new machine info receive
   * @param machine
   */
  void onSimulationMachineInfoReceived(models::MachinePtr machine);

  /**
   * Handles machine turn on command
   */
  void onTurnOnReceived();

  /**
   * Handles machine turn off command
   */
  void onTurnOffReceived();

  network::ConnectionPtr mConnection;
};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONSimulationNetworkComponent_H
