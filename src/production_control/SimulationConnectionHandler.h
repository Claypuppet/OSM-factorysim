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

namespace simulation {

class SimulationConnectionHandler;

typedef std::shared_ptr<SimulationConnectionHandler> SimulationConnectionHandlerPtr;

class SimulationConnectionHandler :
    public Network::IConnectionHandler,
    public patterns::NotifyObserver::Notifier,
    public core::NetworkMapper {
 public:
  SimulationConnectionHandler() = default;

  virtual ~SimulationConnectionHandler() = default;

 private:
  void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

  void onConnectionEstablished(Network::ConnectionPtr connection) override;

  void
  onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

  /**
 * If message is received check for type and tries to fire an event with messageBody and connectionPointer
   * Possible Events:
   * MCsim -> PCsim kSimMessageTypeRegister: Register external simulationmachine to receive future data for simulations
 * @param connection : connection to listen to
 * @param message : incomming message
 */
  void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;

  /**
   * Function that handles message for machine ready for simulation
   * creates a notify even with id eControllerMachineReady and notifies observers
   * @param notification : NotifyEvent
   */
  void handleMachineReady(Network::ConnectionPtr);

  /**
   * handle register machine message, creates a eControllerRegisterMachine notify event to notify the controller
   * @param messageBody : content of the message
   * @param connection : connection to the machine
   */
  void onHandleRegisterMachine(const std::string &messageBody, Network::ConnectionPtr connection);

};
}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H
