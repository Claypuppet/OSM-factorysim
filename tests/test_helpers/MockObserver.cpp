//
// Created by don on 9-5-18.
//

#include "MockObserver.h"
#include "patterns/notifyobserver/Notifier.hpp"
#include "../../src/production_control/NotificationTypes.h"
#include "HelperFunctions.h"

namespace testutils {

MockObserver::MockObserver() : notificationStatus(kNotificationWaiting) {}

void MockObserver::handleNotification(const patterns::NotifyObserver::NotifyEvent &notification) {
  if (handleNotificationFn) {
    handleNotificationFn(notification);
  }
  notificationStatus = kNotificationReceived;
}

void testutils::MockObserver::setHandleNotificationFn(NotificationHandlerFn &aHandleNotificationFn) {
  handleNotificationFn = aHandleNotificationFn;
}

void MockObserver::awaitNotificationReceived(uint32_t timeout) {
  Predicate predicate = [this]() { return notificationStatus != kNotificationWaiting;};
  HelperFunctions::waitForPredicate(predicate, timeout);
  notificationStatus = kNotificationWaiting;
}

}
