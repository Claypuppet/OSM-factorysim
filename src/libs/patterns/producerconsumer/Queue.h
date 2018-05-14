//
// Created by klei on 5/14/18.
//

#ifndef PRODUCTION_LINE_CONTROL_QUEUE_H
#define PRODUCTION_LINE_CONTROL_QUEUE_H

#include <cstddef>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace patterns {
namespace producerconsumer{

/**
 * Safe queue / producer consumer pattern
 * @tparam T : type of items in the queue
 */
template< typename T >
class Queue
{
 public:

  /**
   * get size of the queue
   * @return : number of items
   */
  size_t size() const
  {
	return queue.size();
  }

  /**
   * Add object to the queue
   * @param item : item to add
   */
  void enqueue(const T& item)
  {
	std::unique_lock< std::mutex > lock( queueBusy);
	queue.push(item);
	queueFull.notify_one();
  }

  /**
   * Get the next item from the queue. If queue is empty, it waits.
   * @return : first items from the queue
   */
  T dequeue()
  {
	std::unique_lock< std::mutex > lock( queueBusy);
	while (queue.empty())
	  queueFull.wait( lock);

	T front = queue.front();
	queue.pop();
	return front;
  }

  /**
   * Try to get the first item from the queue, this is different from the dequeue because it won't wait, and instead
   * return the value through a reference paramter.
   * @param out : variable to put the first item in
   * @return : true if success else false
   */
  bool tryDequeue(T& out)
  {
	std::unique_lock< std::mutex > lock( queueBusy);
	if(queue.empty())
	  return false;
	out = queue.front();
	queue.pop();
	return true;
  }

 private:
  std::queue< T > queue;
  std::mutex queueBusy;
  std::condition_variable queueFull;
};

}
}

#endif //PRODUCTION_LINE_CONTROL_QUEUE_H
