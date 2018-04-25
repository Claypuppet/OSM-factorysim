#ifndef EVENT_H_
#define EVENT_H_

#include <cstdint>
#include <memory>
#include <boost/any.hpp>

namespace Patterns {
    namespace Statemachine {

        class Event;

        typedef std::shared_ptr<Event> EventPtr;

        class Event : public std::enable_shared_from_this<Event> {
        public:
			/**
			 * Create new event
			 * @param id
			 */
            explicit Event(uint32_t aId) : id(aId){}

            Event(const Event& event) : id(event.id){}
            virtual ~Event() = default;

            uint32_t getId() const { return id; };

            Event& operator=(const Event &e){
				if(this != &e){
					id = e.id;
				}
				return *this;
			}

			/**
			 * Get argument, will be casted to T
			 * @tparam T : type to cast the argument to
			 * @return T : argument of type T, or nullptr if cast failed
			 */
			template<typename T>
			T getArgumentAsType() const
			{
				return boost::any_cast<T>(argument);
			}

			/**
			 * Add argument
			 * @tparam T : type of the argument
			 * @param value : Argument value to add
			 */
			template <typename T>
			void setArgument(const T& value)
			{
				argument = value;
			}

        private:
            uint32_t id;
			boost::any argument;
        };
    }
}

#endif
