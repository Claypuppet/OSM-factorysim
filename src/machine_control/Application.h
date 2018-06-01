//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H

#include <patterns/statemachine/Context.h>
#include <patterns/notifyobserver/Observer.hpp>
#include <network/Manager.h>
#include <network/Client.h>
#include <models/MachineConfiguration.h>

#include "Machine.h"
#include "NetworkComponent.h"


//TODO: Implement Observer
namespace machinecore {

enum NotifyEventType {
  kNotifyEventTypeServiceStarted,
  kNotifyEventTypeServiceError,
  kNotifyEventTypeStartProcess,
  kNotifyEventTypeMachineConfigured,
  kNotifyEventTypeMachineFailedToConfigure,
  kNotifyEventTypeConfigure,
  kNotifyEventTypeMachineFinishedProcess,
  kNotifyEventTypeMachineBroke
};

class Application
    : public patterns::statemachine::Context,
      public patterns::notifyobserver::Observer {
 public:
  void handleNotification(const patterns::notifyobserver::NotifyEvent &notification) override;

  /**
   * Constructor
   * @param aMachineInfo : The value for machineInfo
   */
  explicit Application(uint16_t aMachineId);

  /**
   * The destructor
   */
  ~Application() override;

  const MachinePtr &getMachine() const {
    return machine;
  }

  void setMachine(const MachinePtr &aMachine) {
    machine = aMachine;
  }

  uint16_t getId() const {
    return id;
  }

  void setId(uint16_t aId) {
    id = aId;
  }

  void setConfigToSet(uint16_t aConfigToSet){
    configToSet = aConfigToSet;
  }

  uint16_t getConfigToSet() const {
    return configToSet;
  }

  /**
   * Sets the starting state for the application's statemachine context
   */
  virtual void setStartState();

  /**
   * Stops the network manager and joins the client thread
   */
  void stop();

  /**
 * Executes network
 */
  void setupNetwork();
/**
 * sends register machine message to PC
 */
  void registerMachine();

  /**
   * Send status update to production control
   * @param status : new status
   */
  void statusUpdate(models::Machine::MachineStatus status);

  /**
   * Send a kMachineErrorCodeBroke to Production Control
   */
  void machineBroke();

 protected:
  uint16_t id;
  MachinePtr machine;
  uint16_t configToSet;

 private:
  network::Manager manager;
  network::ClientPtr client;
  ThreadPtr clientThread;
  Communication::NetworkComponentPtr connectionHandler;

  /**
 * This class is used to handle possible errors, it also fires events on the Applicationhandler, because this implementation is only used here it is defined inline
 */
  class NetworkEventDispatcher : public network::IServiceEventListener, public patterns::notifyobserver::Notifier {
   public:
    NetworkEventDispatcher() = default;
    ~NetworkEventDispatcher() override = default;
   private:

    void onServiceError(network::ServicePtr service, const std::string &message) override {
      //TODO: Add eventId
      //Set up the Connection Failed state event to send to the observers.
      auto event = makeNotificationForNotifier(this,
                                               patterns::notifyobserver::NotifyTrigger(),
                                               NotifyEventType::kNotifyEventTypeServiceError);

      //Notify observers of the error
      notifyObservers(event);
    }

    void onServiceStopped(network::ServicePtr service) override {
      // TODO: check if this is needed
    }

    void onServiceStarted(network::ServicePtr service) override {
      //Set up an event to let the observers know that connection was successful
      auto event = makeNotificationForNotifier(this,
                                               patterns::notifyobserver::NotifyTrigger(),
                                               NotifyEventType::kNotifyEventTypeServiceStarted);

      //Notify observers of connection success
      notifyObservers(event);
    }
  };
};

typedef std::shared_ptr<Application> ApplicationPtr;

}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
