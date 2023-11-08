#ifndef CPP2_S21_CONTAINERS_1_MULTISET_MULTISET_H_
#define CPP2_S21_CONTAINERS_1_MULTISET_MULTISET_H_

#include <initializer_list>

#include "../list/list.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = Allocator<Key> >
class multiset {
  using key_type = typename s21::list<Key>::value_type;
  using value_type = typename s21::list<Key>::value_type;
  using reference = typename s21::list<Key>::reference;
  using const_reference = typename s21::list<Key>::const_reference;
  using iterator = typename s21::list<Key>::iterator;
  using const_iterator = typename s21::list<Key>::const_iterator;
  using size_type = typename s21::list<Key>::size_type;

 public:
  multiset(const Allocator &alloc = Allocator()) : list_(alloc) {}

  multiset(std::initializer_list<value_type> const &items,
           const Allocator &alloc = Allocator())
      : list_(items, alloc) {
    list_.sort();
  }

  multiset(const multiset &ms) : list_(ms.list_) {}

  multiset(const multiset &&ms) : list_(std::move(ms.list_)) {}

  ~multiset() {}

  multiset &operator=(const multiset &other) {
    if (this == &other) {
      return *this;
    }
    list_ = other.list_;
    return *this;
  }

  multiset &operator=(const multiset &&other) {
    if (this == &other) {
      return *this;
    }
    list_.operator=(other.list_);
    return *this;
  }

  iterator begin() noexcept { return list_.begin(); }

  iterator begin() const noexcept { return list_.begin(); }

  iterator end() noexcept { return list_.end(); }

  iterator end() const noexcept { return list_.end(); }

  const_iterator cbegin() const noexcept { return list_.cbegin(); }

  const_iterator cend() const noexcept { return list_.cend(); }

  bool empty() const noexcept { return list_.empty(); }

  size_type size() const noexcept { return list_.size(); }

  size_type max_size() const noexcept { return list_.max_size(); }

  void clear() { list_.clear(); }

  iterator insert(const_reference value) {
    list_.push_back(value);
    list_.sort();
    return find(value);
  }

  void erase(iterator pos) {
    list_.erase(pos);
    list_.sort();
  }

  void swap(multiset &other) { list_.swap(other.list_); }

  void merge(multiset &other) {
    for (const auto &item : other) {
      insert(item);
    }
    other.clear();
  }

  size_type count(const_reference key) const noexcept {
    size_type count = 0;
    for (const auto &item : list_) {
      if (item == key) {
        ++count;
      }
    }
    return count;
  }

  iterator find(const_reference key) const {
    for (typename s21::list<Key>::iterator it = list_.begin();
         it != list_.end(); ++it) {
      if (*it == key) {
        return it;
      }
    }
    return list_.end();
  }

  bool contains(const_reference key) const {
    for (const auto &item : list_) {
      if (item == key) {
        return true;
      }
    }
    return false;
  }

  std::pair<iterator, iterator> equal_range(const_reference key) const {
    typename s21::list<Key>::iterator it = list_.begin();
    for (; it != list_.end(); ++it) {
      if (*it == key) {
        break;
      }
    }
    if (it == list_.end()) {
      return std::make_pair(it, it);
    }
    typename s21::list<Key>::iterator it2 = it;
    while (*(++it2) == key)
      ;

    return std::make_pair(it, --it2);
  }

  iterator lower_bound(const_reference key) const {
    typename s21::list<Key>::iterator it = list_.begin();
    for (; it != list_.end(); ++it) {
      if (*it >= key) {
        --it;
        break;
      }
    }
    return it;
  }

  iterator upper_bound(const_reference key) const {
    typename s21::list<Key>::iterator it = list_.begin();
    for (; it != list_.end(); ++it) {
      if (*it > key) {
        break;
      }
    }
    return it;
  }

 private:
  s21::list<Key> list_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_MULTISET_MULTISET_H_