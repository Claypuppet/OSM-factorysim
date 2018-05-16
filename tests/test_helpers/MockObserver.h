//
// Created by don on 9-5-18.
//

#ifndef PRODUCTION_LINE_CONTROL_MOCKOBSERVER_H
#define PRODUCTION_LINE_CONTROL_MOCKOBSERVER_H

#include <patterns/notifyobserver/Observer.hpp>
#include <functional>

namespace testutils {

typedef std::function<void(const patterns::NotifyObserver::NotifyEvent&)> NotificationHandlerFn;

/**
 * The mockObserver class can be used to mock an observer
 */
class MockObserver : public patterns::NotifyObserver::Observer {
 public:
  MockObserver();
  void handleNotification(const patterns::NotifyObserver::NotifyEvent &notification) override;
  void setHandleNotificationFn(NotificationHandlerFn &aHandleNotificationFn);

  /**
   * A function waits until the mock receives a notification
   * @param timeout : Maximum time to wait in milliseconds default = 100
   */
  void awaitNotificationReceived(uint32_t timeout = 100);
 private:
  NotificationHandlerFn handleNotificationFn;

  enum NotificationStatus{
    kNotificationWaiting,
    kNotificationReceived
  };

  NotificationStatus notificationStatus;
};

}

#endif //PRODUCTION_LINE_CONTROL_MOCKOBSERVER_H
