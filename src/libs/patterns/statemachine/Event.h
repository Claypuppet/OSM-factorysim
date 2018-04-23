#ifndef EVENT_H_
#define EVENT_H_

#include <cstdint>

namespace Patterns {
    namespace Statemachine {

        template <typename T = uint32_t>
        class Event {
        public:

            Event(T id) : id(id){}
            Event(const Event& event) : id(event.id){}
            virtual ~Event() = default;

            T getId() const { return id; };

            Event& operator=(const Event &e) {
                if(this != &e){
                    id = e.id;
                }
                return *this;
            }

        private:
            T id;
        };
    }
}

#endif
