#ifndef EVENT_H_
#define EVENT_H_
namespace Patterns {
    namespace Statemachine {
        class Event {
        public:
            Event(unsigned long long id);

            Event(const Event &event);

            virtual ~Event();

            unsigned long long getId() const;

            const Event& operator=(const Event& rhs);

        private:
            unsigned long long id;
        };
    }
}

#endif
