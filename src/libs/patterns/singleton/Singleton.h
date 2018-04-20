//
// Created by Jelle on 4/18/18.
//

#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace Patterns {
    namespace Singleton {
        template<typename T>
        class Singleton {
        public:
            Singleton() = default;

            Singleton(const Singleton &) = delete;

            static T &getInstance() {
                static T instance;
                return instance;
            }

            static T &i() { return getInstance(); }
        };
    }
}


#endif /* SINGLETON_H_ */
