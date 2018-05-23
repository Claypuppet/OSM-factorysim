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

#include "Observer.hpp"

#define DEFINE_HASHED_ENUM_VALUE(type, name) static const constexpr type name = (type)static_cast<int32_t>(cx::fnv1(#name))

namespace patterns {
namespace notifyobserver {

class Observer;
class Notifier;

typedef uint32_t NotifyEventId;

enum NotifyTriggerId {
  kNotifyTriggerId_Unspecified = 0,
  kNotifyTriggerId_DoNotNotify,
  kNotifyTriggerId_Network,
  kNotifyTriggerId_Model,
  kNotifyTriggerId_Other
};

/**
 * NotifyTrigger can be used to let the observer know what triggered this event
 * triggerId: where did the trigger come from? (network, model, etc)
 * triggerObject: What object initiated the trigger?
 */
class NotifyTrigger {
 public:
  static const NotifyTrigger DoNotNotify;

  /**
   * Create trigger with both trigger id and trigger object
   * @param triggerId
   * @param triggerObject
   */
  NotifyTrigger(NotifyTriggerId triggerId, void *triggerObject)
	  : mTriggerId(triggerId), mTriggerObject(triggerObject) {}

  /**
   * Create trigger with just triggerId
   * @param triggerId
   */
  explicit NotifyTrigger(NotifyTriggerId triggerId) : NotifyTrigger(triggerId, nullptr) {};

  /**
   * Default constructor
   */
  NotifyTrigger() : NotifyTrigger(kNotifyTriggerId_Unspecified, nullptr) {}

  /**
   * Returns the id of the trigger
   * @return mTriggerId
   */
  NotifyTriggerId getId() const {
	return mTriggerId;
  }

  /**
   * Sets a new trigger id
   * @param id : The new trigger id
   * @return Instance of itself
   */
  NotifyTrigger &setId(NotifyTriggerId id) {
	return mTriggerId = id, *this;
  }

  /**
   * Returns the trigger object
   * @return mTriggerObject
   */
  void *getTriggerObject() const {
	return mTriggerObject;
  }

  /**
   * Sets a new trigger object
   * @param object : The new trigger object
   * @return Instance of itseld
   */
  NotifyTrigger &setObject(void *object) {
	return mTriggerObject = object, *this;
  }

  /**
   * Returns the object as string
   * @return NotifyTrigger{id=<mTriggerId>,object=<mTriggerObject>}
   */
  std::string asString() const {
	std::stringstream ss;
	ss << "NotifyTrigger{id=" << mTriggerId << ',' << "object=" << mTriggerObject << '}';
	return ss.str();

  }

 protected:

  NotifyTriggerId mTriggerId;
  void *mTriggerObject;

};

/**
 * NotifyEvent holds the information of the notification.
 * trigger: NotifyTrigger object (see above)
 * notifier: the notifier who notified the observer
 * eventId: unique id of the event to let the observer know what kind of event it is.
 */
class NotifyEvent {
 public:
  /**
   * Create full notify event
   * @param trigger : trigger object, triggered the event
   * @param notifier : the object that notified the event
   * @param eventId : Unique identifier for the event type
   */
  NotifyEvent(const NotifyTrigger &trigger, Notifier *notifier, NotifyEventId eventId);

  /**
   * Create notify event (without trigger)
   * @param notifier : the object that notified the event
   * @param eventId : Unique identifier for the event type
   */
  NotifyEvent(Notifier *notifier, NotifyEventId eventId);

  /**
   * Create notify event with just an id
   * @param eventId : Unique identifier for the event type
   */
  explicit NotifyEvent(NotifyEventId eventId);

  /**
   * The destructor
   */
  virtual ~NotifyEvent() = default;

  // Getters and setters
  /**
   * Returns the notifier of the event
   * @return mNotifier
   */
  Notifier *getNotifier() const;

  /**
   * Returns the id of the event
   * @return mEventId
   */
  NotifyEventId getEventId() const;

  /**
   * Returns the notify trigger
   * @return mTrigger
   */
  const NotifyTrigger &getTrigger() const;

  /**
   * Sets new notify trigger
   * @param trigger : the new trigger
   */
  void setTrigger(NotifyTrigger &trigger);

  /**
   * get argument on given index
   * @param index :
   * @return : boost::any so you can cast it yourself
   */
  boost::any getArgument(uint32_t index) const {
	return mArguments[index];
  }

  /**
   * get an argument as given type
   * @tparam T : Type to cast to
   * @param index :
   * @return : object on given index as given type
   */
  template<typename T>
  T getArgumentAsType(uint32_t index) const {
	return boost::any_cast<T>(mArguments[index]);
  }

  /**
   * get first argument as type
   * @tparam T : Type to cast to
   * @return : object on index 0 as given type
   */
  template<typename T>
  T getFirstArgumentAsType() const {
	return boost::any_cast<T>(mArguments.front());
  }

  /**
   * get number of arguments
   * @return : number of arguments
   */
  uint32_t getNumberOfArguments() {
	return static_cast<uint32_t>(mArguments.size());
  }

  /**
   * add argument
   * @tparam T : type of value
   * @param value : value to add
   */
  template<typename T>
  void addArgument(const T &value) {
	mArguments.push_back(value);
  }

  /**
   * set argument
   * @tparam T : type of value
   * @param index : index to set on
   * @param value : value to set
   */
  template<typename T>
  void setArgument(uint32_t index, const T &value) {
	if (index > mArguments.size()) {
	  throw new std::out_of_range("index > size()");
	}
	if (index == mArguments.size()) {
	  mArguments.push_back(value);
	} else {
	  mArguments[index] = value;
	}
  }

 protected:

  friend class Notifier;

  void setNotifier(Notifier *notifier);

 protected:
  using Arguments = std::vector<boost::any>;

  Notifier *mNotifier;
  uint32_t mEventId;
  NotifyTrigger mTrigger;
  Arguments mArguments;
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

  /**
   * Creates a notification for a notifier
   * @param notifier : A pointer to the notifier
   * @param trigger : A trigger
   * @param eventId : Id for the notify event
   * @return The created NotifyEvent
   */
  static NotifyEvent makeNotificationForNotifier(Notifier *notifier,
												 const NotifyTrigger &trigger,
												 NotifyEventId eventId);

  /**
   * Creates a notification for a notifier
   * @tparam Args
   * @param notifier : Pointer to the notifier
   * @param trigger : Trigger of the event
   * @param eventId : Id of the event
   * @param args : Arguments for the event
   * @return The created NotifyEvent
   */
  template<typename ...Args>
  static NotifyEvent makeNotificationForNotifier(Notifier *notifier,
												 const NotifyTrigger &trigger,
												 NotifyEventId eventId,
												 Args &&... args) {
	auto event = makeNotificationForNotifier(notifier, trigger, eventId);
	event.addArgument(args...);
	return event;
  }

  /**
   * Creates a notification
   * @param trigger : Trigger of the notification
   * @param event : The id of the notification
   * @return The created NotifyEvent
   */
  NotifyEvent makeNotifcation(const NotifyTrigger &trigger, NotifyEventId event);

  /**
   * Creates a even simpler notification
   * @param event : The id of the notification
   * @return The created NotifyEvent
   */
  NotifyEvent makeNotifcation(NotifyEventId event);

  /**
   * Creates a notification
   * @tparam Args
   * @param trigger : The trigger of the notification
   * @param eventId : The id of the notification
   * @param args : The arguments to add to the notification
   * @return The created NotifyEvent
   */
  template<typename ...Args>
  NotifyEvent makeNotificationWithArgs(const NotifyTrigger &trigger, NotifyEventId eventId, Args &&... args) {
	auto event = makeNotificationForNotifier(this, trigger, eventId);
	event.addArgument(args...);
	return event;
  }

 private:
  bool notify;
  std::vector<Observer *> observers;

};
// class Notifier



} // namespace NotifyObserver

} // namespace Patterns
#endif // DANU_NOTIFIER_HPP_
