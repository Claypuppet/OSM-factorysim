#include "Notifier.hpp"
#include <boost/foreach.hpp>
#include <sstream>
#include <typeinfo>
#include "Observer.hpp"
#include "../../../machine_control/states_simulation/Event.h"
#include <algorithm>
#include <patterns/statemachine/Event.h>

namespace Patterns {
	namespace NotifyObserver {

		const NotifyTrigger NotifyTrigger::DoNotNotify(kNotifyTriggerId_DoNotNotify);

		NotifyEvent::NotifyEvent(const NotifyTrigger &trigger, Notifier *notifier)
				: mNotifier(notifier), mTrigger(trigger) {
		}


		NotifyEvent::NotifyEvent(const NotifyTrigger &trigger)
				: NotifyEvent(trigger, nullptr) {
		}

		NotifyEvent::NotifyEvent()
				: NotifyEvent(NotifyTrigger(kNotifyTriggerId_Unspecified), nullptr) {
		}

		Notifier *NotifyEvent::getNotifier() const {
			return mNotifier;
		}

		const NotifyTrigger &NotifyEvent::getTrigger() const {
			return mTrigger;
		}

		NotifyEvent &NotifyEvent::setTrigger(NotifyTrigger &trigger) {
			return mTrigger = trigger, *this;
		}

		NotifyEvent &NotifyEvent::setNotifier(Notifier *notifier) {
			return mNotifier = notifier, *this;
		}

		const Patterns::Statemachine::EventPtr &NotifyEvent::getStateEvent() const {
			return stateEvent;
		}

		void NotifyEvent::setStateEvent(const Patterns::Statemachine::EventPtr &stateEvent) {
			NotifyEvent::stateEvent = stateEvent;
		}

		/**
		 *
		 */
		Notifier::Notifier(bool enable /*= true*/) :
				notify(enable) {
		}

		/**
		 *
		 */
		Notifier::~Notifier() {
		}

		/**
		 *
		 */
		void Notifier::enableNotification(bool enable /* = true */) {
			notify = enable;
		}

		/**
		 *
		 */
		void Notifier::disableNotification() {
			notify = false;
		}

		/**
		 *
		 */
		bool Notifier::isEnabledForNotification() const {
			return notify;
		}

		/**
		 *	The implementation of operator== uses pointer comparison!
		 */
		void Notifier::addObserver(Observer &aObserver) {
			for (Observer *observer : observers) {
				if (*observer == aObserver) {
					return;
				}
			}
			observers.push_back(&aObserver);
		}

		/**
		 *	The implementation of operator== uses pointer comparison!
		 */
		bool Notifier::isObservedBy(Observer &anObserver) {
			return std::find(observers.begin(), observers.end(), &anObserver) != observers.end();
		}


		/**
		 *	The implementation of operator== uses pointer comparison!
		 */
		void Notifier::removeObserver(Observer &aObserver) {
			for (std::vector<Observer *>::iterator i = observers.begin(); i != observers.end(); ++i) {
				if (*(*i) == aObserver) {
					observers.erase(i);
					break;
				}
			}
		}

		/**
		 *
		 */
		void Notifier::removeAllObservers() {
			observers.erase(observers.begin(), observers.end());
		}

		/**
		 *
		 */
		void Notifier::notifyObservers(const NotifyEvent &notification) {
			if (notify && notification.getTrigger().getId() != kNotifyTriggerId_DoNotNotify) {
				for (Observer *observer : observers) {
					observer->handleNotification(notification);
				}
			}
		}

		NotifyEvent Notifier::makeNotificationForNotifier(Notifier *notifier, const NotifyTrigger &trigger) {
			return NotifyEvent(trigger, notifier);
		}


	} // namespace NotifyObserver

} // namespace Patterns

