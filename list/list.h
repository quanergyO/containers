#ifndef CPP2_S21_CONTAINERS_1_LIST_LIST_H_
#define CPP2_S21_CONTAINERS_1_LIST_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <utility>
#include <algorithm>

#include "../iterators/bidirectional_iterator.h"
#include "../utils/allocator.h"

namespace s21 {

template <typename T, typename Allocator = Allocator<T>>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = BidirectionalIterator<T, iterator_traits<T *>, list>;
  using const_iterator =
      BidirectionalIterator<T, iterator_traits<const T *>, list>;
  using size_type = size_t;
  using allocator_type = Allocator;
  using node_allocator = typename std::allocator_traits<
      allocator_type>::template rebind_alloc<ListNode<T>>;

  list(const Allocator &alloc = Allocator())
      : allocator_(alloc),
        allocator_node_(node_allocator()),
        size_(0),
        phantom_node_(std::allocator_traits<node_allocator>::allocate(
            allocator_node_, 1)) {
    phantom_node_->next_ = nullptr;
    phantom_node_->prev_ = nullptr;
  }

  explicit list(size_type n, const Allocator &alloc = Allocator())
      : allocator_(alloc),
        allocator_node_(node_allocator()),
        size_(0),
        phantom_node_(std::allocator_traits<node_allocator>::allocate(
            allocator_node_, 1)) {
    for (size_t i = 0; i < n; ++i) {
      push_back(T());
    }
  }

  list(std::initializer_list<value_type> const &items,
       const Allocator &alloc = Allocator())
      : allocator_(alloc),
        allocator_node_(node_allocator()),
        size_(0),
        phantom_node_(std::allocator_traits<node_allocator>::allocate(
            allocator_node_, 1)) {
    for (auto &item : items) {
      push_back(item);
    }
  }

  list(const list &rhs)
      : allocator_(rhs.allocator_),
        allocator_node_(rhs.allocator_node_),
        size_(0),
        phantom_node_(std::allocator_traits<node_allocator>::allocate(
            allocator_node_, 1)) {
    for (const auto &item : rhs) {
      push_back(item);
    }
  }

list(list &&rhs) noexcept
    : allocator_(std::move(rhs.allocator_)),
      allocator_node_(std::move(rhs.allocator_node_)),
      size_(std::exchange(rhs.size_, 0)),
      phantom_node_(std::exchange(rhs.phantom_node_, nullptr)) {
}

  list &operator=(const list &rhs) {
    if (this == &rhs) {
      return *this;
    }
    list<value_type> copy = rhs;
    swap(copy);

    return *this;
  }

  list &operator=(list &&rhs) noexcept {
    if (this == &rhs) return *this;
    swap(rhs);
    rhs.clear();
    deallocate_node(rhs.phantom_node_);
    return *this;
  }

  ~list() {
    clear();
    deallocate_node(phantom_node_);
  }

  const_reference front() const {
    if (!size_) {
      throw std::out_of_range("list is empty");
    }
    return phantom_node_->next_->data_;
  }

  const_reference back() const {
    if (!size_) {
      throw std::out_of_range("list is empty");
    }
    return phantom_node_->prev_->data_;
  }

  iterator begin() { return iterator(phantom_node_->next_); }

  const_iterator begin() const { return const_iterator(phantom_node_->next_); }

  iterator end() { return iterator(phantom_node_); }

  const_iterator end() const { return const_iterator(phantom_node_); }

  const_iterator cbegin() const { return const_iterator(phantom_node_->next_); }

  const_iterator cend() const { return const_iterator(phantom_node_); }

  iterator rbegin() { return iterator(phantom_node_->prev_); }

  iterator rend() { return iterator(phantom_node_); }

  const_iterator rbegin() const { return const_iterator(phantom_node_->prev_); }

  const_iterator rend() const { return const_iterator(phantom_node_); }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
      return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void clear() {
    if (phantom_node_ == nullptr) {
      return;
    }
    while (phantom_node_->next_ != nullptr) {
      pop_back();
    }
  }

  iterator insert(iterator pos, const_reference value) {
    ListNode<T> *newNode = create_node(value);
    if (size_) {
      setup_connections(newNode, pos.ptr_, pos.ptr_->prev_);
      setup_next(pos.ptr_->prev_, newNode);
      setup_prev(pos.ptr_, newNode);
    } else {
      setup_connections(phantom_node_, newNode, newNode);
      setup_connections(newNode, phantom_node_, phantom_node_);
    }
    ++size_;

    return pos;
  }

  void erase(iterator pos) {
    if (size_ == 1) {
      delete_node(pos.ptr_);
      setup_connections(phantom_node_, nullptr, nullptr);
    } else {
      setup_next(pos.ptr_->prev_, pos.ptr_->next_);
      setup_prev(pos.ptr_->next_, pos.ptr_->prev_);
      delete_node(pos.ptr_);
    }
    --size_;
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() { erase(end().ptr_->prev_); }

  void push_front(const_reference value) { insert(begin(), value); }

  void pop_front() { erase(begin()); }

  void swap(list &rhs) {
    std::swap(allocator_, rhs.allocator_);
    std::swap(allocator_node_, rhs.allocator_node_);
    std::swap(phantom_node_, rhs.phantom_node_);
    std::swap(size_, rhs.size_);
  }

  void merge(list &rhs) {
    if (rhs.empty()) {
        return;
    }
    if (empty()) {
        swap(rhs);
        return;
    }

    ListNode<T> *current = phantom_node_->next_;
    ListNode<T> *rhs_current = rhs.phantom_node_->next_;

    while (current != phantom_node_ && rhs_current != rhs.phantom_node_) {
        if (rhs_current->data_ <= current->data_) {
            rhs_current->prev_->next_ = rhs_current->next_;
            rhs_current->next_->prev_ = rhs_current->prev_;
            ListNode<T> *next_rhs = rhs_current->next_;
            setup_connections(rhs_current, current, current->prev_);
            setup_next(current->prev_, rhs_current);
            setup_prev(current, rhs_current);
            rhs_current = next_rhs;
        } else {
            current = current->next_;
        }
    }

    while (rhs_current != rhs.phantom_node_) {
        rhs_current->prev_->next_ = rhs_current->next_;
        rhs_current->next_->prev_ = rhs_current->prev_;
        ListNode<T> *next_rhs = rhs_current->next_;
        setup_connections(rhs_current, phantom_node_, phantom_node_->prev_);
        setup_next(phantom_node_->prev_, rhs_current);
        setup_prev(phantom_node_, rhs_current);
        rhs_current = next_rhs;
    }
    size_ += rhs.size_;
    rhs.size_ = 0;
    setup_connections(rhs.phantom_node_, nullptr, nullptr);
  }

  void splice(const_iterator pos, list &rhs) {
    if (rhs.empty()) {
        return;
    }

    setup_next(pos.ptr_->prev_, rhs.phantom_node_->next_);
    setup_prev(rhs.phantom_node_->next_, pos.ptr_->prev_);
    setup_prev(pos.ptr_, rhs.phantom_node_->prev_);
    setup_next(rhs.phantom_node_->prev_, pos.ptr_);
    setup_connections(rhs.phantom_node_, nullptr, nullptr);

    size_ += rhs.size_;
    rhs.size_ = 0;
  }

  void unique() {
    if (size_ <= 1) {
      return;
    }

    ListNode<T> *current = phantom_node_->next_;
    ListNode<T> *next_node = current->next_;

    while (next_node != phantom_node_) {
      if (current->data_ == next_node->data_) {
          setup_next(current, next_node->next_);
          setup_prev(next_node->next_, current);
          delete_node(next_node);
          --size_;
      } else {
          current = next_node;
      }
      next_node = current->next_;
    }
  }

  void sort() {
    for (auto i = begin(); i != end(); ++i) {
      for (auto j = begin(); j != end(); ++j) {
        if (*i < *j) {
          std::swap(*i, *j);    
        }
      }
    }
  }

  void reverse() {
    auto first = begin();
    auto last = end();
    while (first != last) {
      --last;
      if (first == last) {
          break;
      }
      std::swap(*first, *last);
      ++first;
    }
  }

 private:
  ListNode<T> *create_node(const_reference value) {
    ListNode<T> *newNode =
        std::allocator_traits<node_allocator>::allocate(allocator_node_, 1);
    try {
      std::allocator_traits<allocator_type>::construct(
          allocator_, &(newNode->data_), value);
    } catch (...) {
      std::allocator_traits<node_allocator>::deallocate(allocator_node_,
                                                        newNode, 1);
      throw;
    }
    return newNode;
  }

  void setup_connections(ListNode<T> *node, ListNode<T> *new_next,
                         ListNode<T> *new_prev) {
    setup_next(node, new_next);
    setup_prev(node, new_prev);
  }

  void setup_next(ListNode<T> *node, ListNode<T> *new_next) {
    node->next_ = new_next;
  }

  void setup_prev(ListNode<T> *node, ListNode<T> *new_prev) {
    node->prev_ = new_prev;
  }

  void delete_node(ListNode<T> *node) {
    destroy_data_in_node(&(node->data_));
    deallocate_node(node);
  }

  void destroy_data_in_node(const T *data) {
    std::allocator_traits<allocator_type>::destroy(allocator_, data);
  }

  void deallocate_node(ListNode<T> *node) {
    std::allocator_traits<node_allocator>::deallocate(allocator_node_, node, 1);
  }

 private:
  allocator_type allocator_;
  node_allocator allocator_node_;
  size_type size_;
  ListNode<T> *phantom_node_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_LIST_LIST_H_
