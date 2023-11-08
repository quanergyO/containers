#ifndef CPP2_S21_CONTAINERS_1_STACK_STACK2_H_
#define CPP2_S21_CONTAINERS_1_STACK_STACK2_H_

#include "../list/list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class stack {
 private:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 public:
  stack() : stack_() {}
  stack(std::initializer_list<value_type> const &items) : stack_(items) {}
  stack(const stack &other) : stack_(other.stack_) {}
  stack(stack &&other) noexcept : stack_(std::move(other.stack_)) {}

  stack operator=(const stack &other) {
    stack_ = other.stack_;
    return *this;
  }

  stack operator=(stack &&other) {
    stack_ = std::move(other.stack_);
    return *this;
  }

  void swap(stack &other) { return stack_.swap(other.stack_); }

  size_type size() { return stack_.size(); }

  bool empty() { return stack_.empty(); }

  const_reference top() { return stack_.back(); }

  void push(const_reference value) { stack_.push_back(value); }

  void pop() { stack_.pop_back(); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    for (auto &it : {args...}) {
      push(it);
    }
  }

 private:
  container_type stack_;
};
}  // namespace s21

#endif  // namespace CPP2_S21_CONTAINERS_1_STACK_STACK2_H_