//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H

#include "patterns/statemachine/Context.h"
#include "patterns/notifyobserver/Observer.hpp"
#include "network/Manager.h"
#include "NetworkComponent.h"
#include "Machine.h"
#include "models/MachineConfiguration.h"
#include <network/Client.h>




//TODO: Implement Observer
namespace machinecore {

enum NotifyEventType {
  kNotifyEventTypeMachineInfoReceived,
  kNotifyEventTypeServiceStarted,
  kNotifyEventTypeServiceError,
  kNotifyEventTypeStartProcess
};

class Application
    : public patterns::statemachine::Context,
      public patterns::NotifyObserver::Observer {
 public:
  void handleNotification(const patterns::NotifyObserver::NotifyEvent &notification) override;

  /**
   * Constructor
   * @param aMachineInfo : The value for machineInfo
   */
  explicit Application(uint16_t aMachineId);

  /**
   * The destructor
   */
  ~Application() override;

  const Machine &getMachine() const {
    return machine;
  }

  void setMachine(const Machine &machine) {
    Application::machine = machine;
  }

  uint16_t getId() const {
    return id;
  }

  void setId(uint16_t id) {
    Application::id = id;
  }

  const std::vector<models::MachineConfiguration> &getConfigurations() const {
    return configurations;
  }

  void setConfigurations(const std::vector<models::MachineConfiguration> &configurations) {
    Application::configurations = configurations;
  }

  /**
   * Sets the starting state for the application's statemachine context
   */
  void setStartState();

  /**
   * Stops the network manager and joins the client thread
   */
  void stop();

  void setupNetwork();

  /**
   * Execute the self test and create a new event based on the result
   */
  virtual void executeSelfTest() {}

  /**
   * Take a product from the machine buffer into the machine
   */
  virtual void takeProductIn() {}

  /**
   * Process the product that is currently in the machine
   */
   virtual void processProduct() {}

   /**
    * Take product out of the machine into the output buffer
    */
    virtual void takeProductOut() {}

 private:
  Network::Manager manager;
  Network::ClientPtr client;
  ThreadPtr clientThread;
  Communication::NetworkComponent connectionHandler;

  Machine machine;

  // Id of the machine
  uint16_t id;

  // Vector of possible configurations
  std::vector<models::MachineConfiguration> configurations;

  /**
 * This class is used to handle possible errors, it also fires events on the Applicationhandler, because this implementation is only used here it is defined inline
 */
  class NetworkEventDispatcher : public Network::IServiceEventListener, public patterns::NotifyObserver::Notifier {
   public:
    NetworkEventDispatcher() = default;
    ~NetworkEventDispatcher() override = default;
   private:

    void onServiceError(Network::ServicePtr service, const std::string &message) override {
      //TODO: Add eventId
      //Set up the Connection Failed state event to send to the observers.
      auto event = makeNotificationForNotifier(this,
                                               patterns::NotifyObserver::NotifyTrigger(),
                                               NotifyEventType::kNotifyEventTypeServiceError);

      //Notify observers of the error
      notifyObservers(event);
    }

    void onServiceStopped(Network::ServicePtr service) override {
      // TODO: check if this is needed
    }

    void onServiceStarted(Network::ServicePtr service) override {
      //Set up an event to let the observers know that connection was successful
      auto event = makeNotificationForNotifier(this,
                                               patterns::NotifyObserver::NotifyTrigger(),
                                               NotifyEventType::kNotifyEventTypeServiceStarted);

      //Notify observers of connection success
      notifyObservers(event);
    }
  };
};
}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
