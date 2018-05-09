//
// Created by hqnders on 20/04/18.
//

#ifndef PRODUCTION_LINE_CONTROL_APPLICATION_H
#define PRODUCTION_LINE_CONTROL_APPLICATION_H

#include <models/Machine.h>
#include "patterns/statemachine/Context.h"
#include "patterns/notifyobserver/Observer.hpp"
#include "network/Manager.h"
#include "NetworkComponent.h"
#include <network/Client.h>





namespace MachineCore {
enum NotifyEventType {
  kNotifyEventTypeMachineInfoReceived,

  kNotifyEventTypeServiceStarted,
  kNotifyEventTypeServiceError
};

class Application
    : public Patterns::Statemachine::Context,
      public Patterns::NotifyObserver::Observer {
 public:
  void handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) override;

  /**
   * Constructor
   * @param aMachineInfo : The value for machineInfo
   */
  explicit Application(const Models::Machine &aMachineInfo);

  /**
   * The destructor
   */
  ~Application() override = default;

  /**
   * Getter for machineInfo
   * @return machineInfo
   */
  const Models::Machine &getMachineInfo() const;

  /**
   * Setter for machineInfo
   * @param machineInfo : New value for machineInfo
   */
  void setMachineInfo(const Models::Machine &machineInfo);
  /**
   * This function tries to make a connection, it fires an event.
   */
  void setupNetwork();

  /**
   * Sets start state, this function is called Onstate entry of simulation
   */
  void setStartState();

 private:
  Network::Manager manager;
  Network::ClientPtr client;
  ThreadPtr clientThread;
  Models::Machine machineInfo;

/**
 * This class is used to handle possible errors, it also fires events on the Applicationhandler, because this implementation is only used here it is defined inline
 */
  class NetworkEventDispatcher : public Network::IServiceEventListener, public Patterns::NotifyObserver::Notifier {
   public:
    NetworkEventDispatcher() = default;
    ~NetworkEventDispatcher() override = default;
   private:

    void onServiceError(Network::ServicePtr service, const std::string &message) override {
      //TODO: Add eventId
      //Set up the Connection Failed state event to send to the observers.
      auto event = makeNotificationForNotifier(this,
                                               Patterns::NotifyObserver::NotifyTrigger(),
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
                                               Patterns::NotifyObserver::NotifyTrigger(),
                                               NotifyEventType::kNotifyEventTypeServiceStarted);

      //Notify observers of connection success
      notifyObservers(event);
    }
  };
};
}

#endif //PRODUCTION_LINE_CONTROL_APPLICATION_H
