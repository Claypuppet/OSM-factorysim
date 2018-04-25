#include "Notifier.hpp"
#include <boost/foreach.hpp>

namespace Patterns {
	namespace NotifyObserver {

		const NotifyTrigger NotifyTrigger::DoNotNotify(kNotifyTriggerId_DoNotNotify);

		NotifyEvent::NotifyEvent(const NotifyTrigger& trigger, Notifier* notifier, NotifyEventId event)
				: mNotifier(notifier)
				, mEventId(event)
				, mTrigger(trigger)
		{
		}


		NotifyEvent::NotifyEvent(const NotifyTrigger& trigger)
				: NotifyEvent(trigger, nullptr, 0)
		{
		}

		NotifyEvent::NotifyEvent()
				: NotifyEvent(NotifyTrigger(kNotifyTriggerId_Unspecified), nullptr, 0)
		{
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

		NotifyEventId NotifyEvent::getEventId() const {
			return mEventId;
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


		NotifyEvent Notifier::makeNotificationForNotifier(Notifier* notifier, const NotifyTrigger& trigger, NotifyEventId eventId) {
			return NotifyEvent(trigger, notifier, eventId);
		}

		NotifyEvent Notifier::makeNotifcation(const NotifyTrigger& trigger, NotifyEventId event)
		{
			return NotifyEvent(trigger, this, event);
		}


	} // namespace NotifyObserver

} // namespace Patterns

