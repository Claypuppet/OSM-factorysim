//
// Created by don on 9-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MOCKOBSERVER_H
#define PRODUCTION_LINE_CONTROL_MOCKOBSERVER_H

#include <patterns/notifyobserver/Observer.hpp>
#include <functional>

namespace testUtils {

typedef std::function<void(const Patterns::NotifyObserver::NotifyEvent&)> NotificationHandlerFn;

/**
 * The mockObserver class can be used to mock an observer
 */
class MockObserver : public Patterns::NotifyObserver::Observer {
 public:
  void handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) override;
  void setHandleNotificationFn(NotificationHandlerFn &aHandleNotificationFn);
 private:
  NotificationHandlerFn handleNotificationFn;
};

}

#endif //PRODUCTION_LINE_CONTROL_MOCKOBSERVER_H
