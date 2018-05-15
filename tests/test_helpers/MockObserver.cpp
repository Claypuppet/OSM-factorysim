//
// Created by don on 9-5-18.
//

#include "MockObserver.h"
#include "patterns/notifyobserver/Notifier.hpp"
#include "../../src/production_control/NotificationTypes.h"

void testUtils::MockObserver::handleNotification(const Patterns::NotifyObserver::NotifyEvent &notification) {
  if(handleNotificationFn)
  {
    handleNotificationFn(notification);
  }
}

void testUtils::MockObserver::setHandleNotificationFn(testUtils::NotificationHandlerFn &aHandleNotificationFn) {
  handleNotificationFn = aHandleNotificationFn;
}
