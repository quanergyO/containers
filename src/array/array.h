#ifndef CPP2_S21_CONSTAINERS_1_ARRAY_ARRAY_H_
#define CPP2_S21_CONSTAINERS_1_ARRAY_ARRAY_H_

#include <cstddef>
#include <exception>

#include "../iterators/random_access_iterator.h"

namespace s21 {
template <typename T, size_t N>
struct array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = RandomAccessIterator<T, iterator_traits<T *>>;
  using const_iterator = RandomAccessIterator<T, iterator_traits<const T *>>;
  using size_type = size_t;

  array() : size_(N) {}
  array(std::initializer_list<value_type> const &items) : size_(N) {
    std::copy(items.begin(), items.end(), data_);  // construct?
  }
  array(const array &rhs) : size_(N) {
    std::copy(rhs.begin(), rhs.end(), data_);  // construct?
  }

  array(array &&rhs) noexcept : array(rhs) {}

  array &operator=(const array &rhs) noexcept {
    if (this != &rhs) {
      for (size_type i = 0; i < size_; ++i) {
        data_[i] = rhs.data_[i];
      }
    }
    return *this;
  }

  ~array() = default;

  reference at(size_t pos) {
    if (pos >= size_ || size_ == 0) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  const_reference front() const noexcept { return data_[0]; }

  const_reference back() const noexcept { return data_[size_ - 1]; }

  reference operator[](size_type index) { return data_[index]; }

  iterator data() { return data_; }

  iterator begin() noexcept { return iterator(data_); }

  iterator end() noexcept { return iterator(data_ + N); }

  const_iterator begin() const { return const_iterator(data_); }

  const_iterator end() const { return const_iterator(data_ + N); }

  const_iterator cbegin() const { return const_iterator(data_); }

  const_iterator cend() const { return const_iterator(data_ + N); }

  bool empty() const noexcept { return !size_; }

  size_type size() const noexcept { return N; }

  size_type max_size() const noexcept { return N; }

  void swap(array &rhs) {
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < size_; ++i) {
      data_[i] = value;
    }
  }

 public:
  size_t size_;
  T data_[N];
};

}  // namespace s21

#endif  // CPP2_S21_CONSTAINERS_1_ARRAY_ARRAY_H_
