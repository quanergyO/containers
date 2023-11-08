#ifndef CPP2_S21_CONTAINERS_1_ITERATORS_BIDIRECTIONAL_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_ITERATORS_BIDIRECTIONAL_ITERATOR_H_

#include "../list/list.h"
#include "iterators_traits.h"

namespace s21 {
template <typename T>
class ListNode {
 public:
  T data_;
  ListNode *next_;
  ListNode *prev_;
  ListNode() : next_(nullptr), prev_(nullptr) {}
  explicit ListNode(const T &value)
      : data_(value), next_(nullptr), prev_(nullptr) {}
};

template <typename T, typename IteratorTraits, typename Container>
class BidirectionalIterator {
  friend Container;

 public:
  using value_type = typename IteratorTraits::value_type;
  using difference_type = typename IteratorTraits::difference_type;
  using pointer = typename IteratorTraits::pointer;
  using reference = typename IteratorTraits::reference;
  using iterator_category = typename IteratorTraits::iterator_category;

  BidirectionalIterator() = delete;
  BidirectionalIterator(ListNode<T> *ptr) : ptr_(ptr) {}
  BidirectionalIterator(const BidirectionalIterator &rhs) : ptr_(rhs.ptr_) {}
  BidirectionalIterator &operator=(const BidirectionalIterator &rhs) {
    if (this == &rhs) {
      return *this;
    }
    ptr_ = rhs.ptr_;
    return *this;
  }
  ~BidirectionalIterator() = default;

  BidirectionalIterator &operator++() {
    ptr_ = ptr_->next_;
    return *this;
  }

  BidirectionalIterator &operator--() {
    ptr_ = ptr_->prev_;
    return *this;
  }

  BidirectionalIterator operator++(int) {
    BidirectionalIterator copy(*this);
    ptr_ = ptr_->next_;
    return copy;
  }

  BidirectionalIterator operator--(int) {
    BidirectionalIterator copy(*this);
    ptr_ = ptr_->prev_;
    return copy;
  }

  reference operator*() { return ptr_->data_; }

  pointer operator->() { return &(ptr_->data_); }

  bool operator==(const BidirectionalIterator &rhs) { return ptr_ == rhs.ptr_; }

  bool operator!=(const BidirectionalIterator &rhs) { return ptr_ != rhs.ptr_; }

 private:
  ListNode<T> *ptr_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_ITERATORS_BIDIRECTIONAL_ITERATOR_H_