#ifndef CPP2_S21_CONTAINERS_1_STACK_STACK_H_
#define CPP2_S21_CONTAINERS_1_STACK_STACK_H_

#include <cstdio>
#include <initializer_list>

#include "../list/list.h"

namespace s21 {

template <typename T, typename Allocator = Allocator<T>>
class stack : protected s21::list<T, Allocator> {
 private:
  using cur = s21::list<T, Allocator>;

  using value_type = typename cur::value_type;
  using reference = typename cur::reference;
  using const_reference = typename cur::const_reference;
  using size_type = typename cur::size_type;

 public:
  using cur::cur;
  const_reference top() const noexcept { return cur::front(); }
  using cur::empty;
  using cur::size;
  void push(const_reference value) { cur::push_front(value); }
  void pop() noexcept { cur::pop_front(); };
  void swap(stack& s) noexcept { cur::swap(static_cast<cur&>(s)); }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_STACK_STACK_H_
