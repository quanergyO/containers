#ifndef CPP2_S21_CONSTAINERS_1_QUEUE_QUEUE_H_
#define CPP2_S21_CONSTAINERS_1_QUEUE_QUEUE_H_

#include <cstddef>

#include "../iterators/random_access_iterator.h"
#include "../list/list.h"

namespace s21 {

template <typename T, typename Allocator = Allocator<T>>
class queue : protected s21::list<T, Allocator> {
 private:
  using cur = s21::list<T, Allocator>;
  using value_type = typename cur::value_type;
  using reference = typename cur::reference;
  using const_reference = typename cur::const_reference;
  using size_type = typename cur::size_type;

 public:
  using cur::cur;
  const_reference front() const noexcept { return cur::front(); }
  const_reference back() const noexcept { return cur::back(); }

  using cur::empty;
  using cur::size;

  void push(const_reference value) { cur::push_back(value); }
  void pop() noexcept { cur::pop_front(); };
  void swap(queue& q) noexcept { cur::swap(static_cast<cur&>(q)); }
};
}  // namespace s21

#endif  // CPP2_S21_CONSTAINERS_1_QUEUE_QUEUE_H_