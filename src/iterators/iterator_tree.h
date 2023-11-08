#ifndef CPP2_S21_CONTAINERS_1_ITERATORS_ITERATOR_TREE_H_
#define CPP2_S21_CONTAINERS_1_ITERATORS_ITERATOR_TREE_H_

#include "iterators_traits.h"

namespace s21 {

template <typename Data>
struct TreeNode {
  TreeNode() : left_(nullptr), right_(nullptr), parent_(nullptr), height_(0) {}

  TreeNode(Data data)
      : data_(data),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr),
        height_(0) {}

  TreeNode(Data data, TreeNode* parent)
      : data_(data),
        left_(nullptr),
        right_(nullptr),
        parent_(parent),
        height_(1) {}

  TreeNode(const TreeNode&& rhs)
      : data_(std::move(rhs.data_)),
        left_(std::exchange(rhs.left_, nullptr)),
        right_(std::exchange(rhs.right_, nullptr)),
        parent_(std::exchange(rhs.parent_, nullptr)),
        height_(std::exchange(rhs.height_, 0)) {}

  Data data_;
  TreeNode* left_;
  TreeNode* right_;
  TreeNode* parent_;
  int height_;
};

template <typename T, typename IteratorTraits, typename Container>
class TreeIterator {
  friend Container;

 public:
  using value_type = typename IteratorTraits::value_type;
  using difference_type = typename IteratorTraits::difference_type;
  using pointer = typename IteratorTraits::pointer;
  using reference = typename IteratorTraits::reference;
  using iterator_category = typename IteratorTraits::iterator_category;

  TreeIterator() = delete;
  TreeIterator(TreeNode<value_type>* ptr) : ptr_(ptr) {}

  TreeIterator& operator++() {
    if (ptr_->right_) {
      ptr_ = getMin(ptr_->right_);
    } else {
      while (ptr_->parent_->parent_ && ptr_->parent_->right_ == ptr_) {
        ptr_ = ptr_->parent_;
      }
      ptr_ = ptr_->parent_;
    }
    return *this;
  }

  TreeIterator operator++(int) {
    TreeIterator temp = *this;
    ++(*this);
    return temp;
  }

  TreeIterator& operator--() {
    if (ptr_->left_) {
      ptr_ = getMax(ptr_->left_);
    } else {
      while (ptr_->parent_->parent_ && ptr_->parent_->left_ == ptr_) {
        ptr_ = ptr_->parent_;
      }
      ptr_ = ptr_->parent_;
    }
    return *this;
  }

  TreeIterator operator--(int) {
    TreeIterator temp = *this;
    --(*this);
    return temp;
  }

  reference operator*() { return ptr_->data_; }

  pointer operator->() { return &(ptr_->data_); }

  bool operator==(const TreeIterator& rhs) const noexcept {
    return ptr_ == rhs.ptr_;
  }

  bool operator!=(const TreeIterator& rhs) const noexcept {
    return ptr_ != rhs.ptr_;
  }

 private:
  TreeNode<value_type>* getMin(TreeNode<value_type>* node) {
    if (node == nullptr) return nullptr;
    if (node->left_ == nullptr) return node;
    return getMin(node->left_);
  }

  TreeNode<value_type>* getMax(TreeNode<value_type>* node) {
    if (node == nullptr) return nullptr;
    if (node->right_ == nullptr) return node;
    return getMax(node->right_);
  }

 private:
  TreeNode<value_type>* ptr_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_ITERATORS_ITERATOR_TREE_H_