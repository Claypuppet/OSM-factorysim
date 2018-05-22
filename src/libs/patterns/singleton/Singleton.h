//
// Created by Jelle on 4/18/18.
//

#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace patterns {
namespace Singleton {
template<typename T>
class Singleton {
 public:
  Singleton(const Singleton &) = delete;
  virtual Singleton &operator=(const Singleton &) = delete;

  /**
   * Get singleton object instance
   * @return T type
   */
  static T &getInstance() {
	static T instance;
	return instance;
  }

  /**
   * Short function for getInstance
   * @return T type
   */
  static T &i() { return getInstance(); }
 protected:
  Singleton() = default;
};
}
}

#endif /* SINGLETON_H_ */
