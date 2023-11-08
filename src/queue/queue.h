#ifndef CPP2_S21_CONSTAINERS_1_QUEUE_QUEUE_H_
#define CPP2_S21_CONSTAINERS_1_QUEUE_QUEUE_H_

#include <cstddef>

#include "../iterators/random_access_iterator.h"
#include "../list/list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
 private:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 public:
  queue() : queue_(){};
  queue(std::initializer_list<value_type> const &items) : queue_(items) {}
  queue(const queue &other) : queue_(other.queue_) {}
  queue(queue &&other) noexcept : queue_(std::move(other.queue_)) {}

  const_reference front() const noexcept { return queue_.front(); }
  const_reference back() const noexcept { return queue_.back(); }

  queue operator=(const queue &other) {
    queue_ = other.queue_;
    return *this;
  }
  queue operator=(queue &&other) {
    queue_ = std::move(other.queue_);
    return *this;
  }

  bool empty() const noexcept(noexcept(queue_.empty())) {
    return queue_.empty();
  }

  size_type size() const noexcept(noexcept(queue_.size())) {
    return queue_.size();
  }

  void push(const_reference value) { queue_.push_back(value); }

  void pop() { queue_.pop_front(); }

  void swap(queue &other) { return queue_.swap(other.queue_); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (auto &it : {args...}) {
      push(it);
    }
  }

 private:
  container_type queue_;
};

}  // namespace s21

#endif  // CPP2_S21_CONSTAINERS_1_QUEUE_QUEUE_H_