#ifndef CPP2_S21_CONTAINERS_1_ITERATORS_ITERATORS_TRAITS_H_
#define CPP2_S21_CONTAINERS_1_ITERATORS_ITERATORS_TRAITS_H_

#include <cstddef>

namespace s21 {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template <typename Iterator>
struct iterator_traits {
  using value_type = typename Iterator::value_type;
  using difference_type = typename Iterator::difference_type;
  using pointer = typename Iterator::pointer;
  using reference = typename Iterator::reference;
  using iterator_category = typename Iterator::iterator_category;
};

template <typename T>
struct iterator_traits<T *> {
  using value_type = T;
  using difference_type = ptrdiff_t;
  using pointer = T *;
  using reference = T &;
  using iterator_category = random_access_iterator_tag;
};

template <typename T>
struct iterator_traits<const T *> {
  using value_type = T;
  using difference_type = ptrdiff_t;
  using pointer = const T *;
  using reference = const T &;
  using iterator_category = random_access_iterator_tag;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_ITERATORS_ITERATORS_TRAITS_H_
