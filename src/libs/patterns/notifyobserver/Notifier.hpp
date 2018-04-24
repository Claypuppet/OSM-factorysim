#ifndef NOTIFIER_HPP_
#define NOTIFIER_HPP_

#include <boost/any.hpp>
#include <string>
#include <vector>
#include <stdexcept>
#include <type_traits>
#include <memory>
#include <ostream>
#include <sstream>

#include <patterns/statemachine/Event.h>

#include "Observer.hpp"

#define DEFINE_HASHED_ENUM_VALUE(type, name) static const constexpr type name = (type)static_cast<int32_t>(cx::fnv1(#name))

namespace Patterns {
	namespace NotifyObserver {

		class Observer;
		class Notifier;


		enum NotifyTriggerId
		{
			kNotifyTriggerId_Unspecified = 0,
			kNotifyTriggerId_DoNotNotify,
			kNotifyTriggerId_Network,
			kNotifyTriggerId_Model,
			kNotifyTriggerId_Other
		};


		class NotifyTrigger {
		public:
			static const NotifyTrigger DoNotNotify;

			NotifyTrigger(NotifyTriggerId triggerId, void *triggerObject)
					: mTriggerId(triggerId), mTriggerObject(triggerObject) {}

			NotifyTrigger(NotifyTriggerId triggerId) : NotifyTrigger(triggerId, nullptr) {};

			NotifyTrigger() : NotifyTrigger(kNotifyTriggerId_Unspecified, nullptr) {}


			NotifyTriggerId getId() const {
				return mTriggerId;
			}

			NotifyTrigger &setId(NotifyTriggerId id) {
				return mTriggerId = id, *this;
			}

			void *getTriggerObject() const {
				return mTriggerObject;
			}

			NotifyTrigger &setObject(void *object) {
				return mTriggerObject = object, *this;
			}

			std::string asString() const {
				std::stringstream ss;
				ss << "NotifyTrigger{id=" << mTriggerId << ',' << "object=" << mTriggerObject << '}';
				return ss.str();

			}

		protected:

			NotifyTriggerId mTriggerId;
			void *mTriggerObject;

		};


		class NotifyEvent {
		public:
			NotifyEvent(const NotifyTrigger &trigger, Notifier *notifier);

			NotifyEvent(const NotifyTrigger &trigger);

			NotifyEvent();

			Notifier *getNotifier() const;

			const NotifyTrigger &getTrigger() const;

			NotifyEvent &setTrigger(NotifyTrigger &trigger);

			const Statemachine::EventPtr &getStateEvent() const;
			void setStateEvent(const Statemachine::EventPtr &stateEvent);

		protected:

			friend class Notifier;

			NotifyEvent &setNotifier(Notifier *notifier);


		protected:
			Notifier *mNotifier;
			NotifyTrigger mTrigger;
			Statemachine::EventPtr stateEvent;
		};


		/**
		 * The Notifier class is part of a straight forward implementation of the Observer/Notifier pattern
		 *
		 * @see Observer
		 */
		class Notifier {
		public:

			/**
			 * @name Constructors and destructor
			 */
			//@{
			/**
			 * Default constructor, enables notification by default.
			 *
			 * @param enable If true, notification is enabled.
			 */
			Notifier(bool enable = true);

			/**
			 *
			 */
			virtual ~Notifier();
			//@}

			/**
			 * @name Notifier functions
			 */
			//@{
			/**
			 * En- or disables the notification by this Notifier
			 *
			 * @param enable If true (default) enables the notification for this Notifier
			 */
			virtual void enableNotification(bool enable = true);

			/**
			 * Disables the notification by this Notifier
			 */
			virtual void disableNotification();

			/**
			 *
			 * @return True if notification is enabled for this Notifier, false otherwise
			 */
			virtual bool isEnabledForNotification() const;

			/**
			 * Adds the Observer to the list of Observers if not in the list yet
			 *
			 * @param anObserver The observer to add
			 */
			virtual void addObserver(Observer &anObserver);

			/**
			 *  Check if the specified observer is added
			 *
			 *  @param anObserver The observer to check for
			 */
			virtual bool isObservedBy(Observer &anObserver);

			/**
			 * Removes the Observer from the list of Observers if in the list
			 *
			 * @param anObserver The Observer to remove
			 */
			virtual void removeObserver(Observer &anObserver);

			/**
			 * Removes all observer from the list of Observers
			 */
			virtual void removeAllObservers();

			/**
			 * Notifies all observers
			 */
			virtual void notifyObservers(const NotifyEvent &notification);


			static NotifyEvent
			makeNotificationForNotifier(Notifier *notifier, const NotifyTrigger &trigger);

			static NotifyEvent
			makeNotificationForNotifier(Notifier *notifier, const NotifyTrigger &trigger, const Statemachine::EventPtr stateEvent) {
				auto notification = makeNotificationForNotifier(notifier, trigger);
				notification.setStateEvent(stateEvent);
				return notification;
			}


		private:
			bool notify;
			std::vector<Observer *> observers;

		};
		// class Notifier



	} // namespace NotifyObserver

} // namespace Patterns
#endif // DANU_NOTIFIER_HPP_
