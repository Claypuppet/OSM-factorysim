#ifndef EVENT_H_
#define EVENT_H_

#include <cstdint>
#include <memory>
#include <boost/any.hpp>
#include <vector>

namespace patterns {
    namespace statemachine {

        class Event;

        typedef std::shared_ptr<Event> EventPtr;

        class Event : public std::enable_shared_from_this<Event> {
        public:
			/**
			 * Create new event
			 * @param id
			 */
            explicit Event(uint32_t aId) : id(aId){}

            /**
             * Copy constructor
             * @param event : The event to copy
             */
            Event(const Event& event) : id(event.id){}
            virtual ~Event() = default;

            /**
             * Returns the id of the event
             * @return id
             */
            uint32_t getId() const { return id; };

            /**
             * Assignment operator
             * @param e : The assigned Event
             * @return The new Event
             */
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
			T getArgumentAsType(uint32_t index) const
			{
				return boost::any_cast<T>(mArguments[index]);
			}

			/**
			 * Get first argument, will be casted to T
			 * @tparam T : type to cast the argument to
			 * @return T : argument of type T, or nullptr if cast failed
			 */
			template<typename T>
			T getArgumentAsType() const
			{
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
			 * Append argument
			 * @tparam T : type of the argument
			 * @param value : Argument value to add to argument list
			 */
			template <typename T>
			void addArgument(const T& value)
			{
				mArguments.push_back(value);
			}

			/**
			 * Set argument on index 0
			 * @tparam T : type of the argument
			 * @param value : Argument value to set
			 */
			template<typename T>
			void setArgument(const T& value)
			{
				// set on first
				uint32_t index = 0;
				if(index > mArguments.size())
					throw new std::out_of_range("index > size()");
				if(index == mArguments.size())
					mArguments.push_back(value);
				else
					mArguments[index] = value;
			}

			/**
			 *
			 * Set argument on given index
			 * @tparam T : type of the argument
			 * @param index : Argument index
			 * @param value : Argument value to set
			 */
			template<typename T>
			void setArgument(uint32_t index, const T& value)
			{
				if(index > mArguments.size())
					throw new std::out_of_range("index > size()");
				if(index == mArguments.size())
					mArguments.push_back(value);
				else
					mArguments[index] = value;
			}



		protected:
			using Arguments = std::vector<boost::any>;

			uint32_t		id;
			Arguments		mArguments;
        };
    }
}

#endif
