//
// Created by sven on 25-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H

#include <network/Connection.h>
#include <patterns/notifyobserver/Notifier.hpp>
#include <models/Configuration.h>
#include <models/Machine.h>

#include "NetworkMapper.h"

namespace simulationcommunication {

class SimulationConnectionHandler;

typedef std::shared_ptr<SimulationConnectionHandler> SimulationConnectionHandlerPtr;

/**
 * Network component for a simulation control that handles messages and connections
 */
class SimulationConnectionHandler :
	public network::IConnectionHandler,
	public patterns::notifyobserver::Notifier,
	public communication::NetworkMapper {
 public:
  SimulationConnectionHandler() = default;
  SimulationConnectionHandler(const SimulationConnectionHandler &) = delete;

  virtual ~SimulationConnectionHandler() = default;

 private:
  void onConnectionFailed(network::ConnectionPtr connection, const boost::system::error_code &error) override;

  void onConnectionEstablished(network::ConnectionPtr connection) override;

  void
  onConnectionDisconnected(network::ConnectionPtr connection, const boost::system::error_code &error) override;

  /**
 * If message is received check for type and tries to fire an event with messageBody and connectionPointer
   * Possible Events:
   * MCsim -> PCsim kSimMessageTypeRegister: Register external simulationmachine to receive future data for simulations
 * @param connection : connection to listen to
 * @param message : incomming message
 */
  void onConnectionMessageReceived(network::ConnectionPtr connection, network::Message &message) override;

  /**
   * Function that handles message for machine ready for simulation
   * creates a notify even with id eControllerMachineReady and notifies observers
   * @param notification : NotifyEvent
   */
  void handleMachineReady(network::ConnectionPtr);

  /**
   * handle register machine message, creates a eControllerRegisterMachine notify event to notify the controller
   * @param messageBody : content of the message
   * @param connection : connection to the machine
   */
  void onHandleRegisterMachine(network::Message &message, network::ConnectionPtr connection);

};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H
