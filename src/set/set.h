#ifndef CPP2_S21_CONTAINERS_1_SET_SET_H_
#define CPP2_S21_CONTAINERS_1_SET_SET_H_

#include <cstddef>
#include <limits>
#include <utility>

#include "../iterators/iterator_tree.h"
#include "../../utils/allocator.h"

namespace s21 {

template <class Key, class Compare = std::less<Key>,
          class Allocator = Allocator<Key>>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = TreeIterator<Key, iterator_traits<const Key*>, set>;
  using const_iterator = TreeIterator<Key, iterator_traits<const Key*>, set>;
  using size_type = size_t;
  using allocator_type = Allocator;
  using node_allocator = typename std::allocator_traits<
      allocator_type>::template rebind_alloc<TreeNode<Key>>;

 public:
  set(const Allocator& alloc = Allocator())
      : comparator_(Compare()),
        allocator_(
            std::allocator_traits<
                allocator_type>::select_on_container_copy_construction(alloc)),
        allocator_node_(
            std::allocator_traits<node_allocator>::
                select_on_container_copy_construction(node_allocator())),
        size_(0),
        phantom_node_(std::allocator_traits<node_allocator>::allocate(
            allocator_node_, 1)) {
    initNode(phantom_node_);
  }

  set(std::initializer_list<value_type> const& items,
      const Allocator& alloc = Allocator())
      : comparator_(Compare()),
        allocator_(
            std::allocator_traits<
                allocator_type>::select_on_container_copy_construction(alloc)),
        allocator_node_(
            std::allocator_traits<node_allocator>::
                select_on_container_copy_construction(node_allocator())),
        size_(0),
        phantom_node_(std::allocator_traits<node_allocator>::allocate(
            allocator_node_, 1)) {
    initNode(phantom_node_);
    for (auto& item : items) {
      insert(item);
    }
  }

  set(const set& rhs)
      : comparator_(rhs.comparator_),
        allocator_(std::allocator_traits<allocator_type>::
                       select_on_container_copy_construction(rhs.allocator_)),
        allocator_node_(
            std::allocator_traits<node_allocator>::
                select_on_container_copy_construction(rhs.allocator_node_)),
        size_(0),
        phantom_node_(std::allocator_traits<node_allocator>::allocate(
            allocator_node_, 1)) {
    initNode(phantom_node_);
    for (auto& item : rhs) {
      insert(item);
    }
  }

  set(set&& rhs)
      : comparator_(std::move(rhs.comparator_)),
        allocator_(std::move(rhs.allocator_)),
        allocator_node_(std::move(rhs.allocator_node_)),
        size_(std::exchange(rhs.size_, 0)),
        phantom_node_(std::exchange(rhs.phantom_node_, nullptr)) {}

  ~set() {
    if (phantom_node_) {
      _clear(phantom_node_->left_);
      std::allocator_traits<node_allocator>::deallocate(allocator_node_,
                                                        phantom_node_, 1);
    }
  }

  set& operator=(const set& rhs) {
    if (this == &rhs) {
      return *this;
    }
    set copy = rhs;
    swap(copy);
    return *this;
  }

  set& operator=(set&& rhs) {
    if (this == &rhs) {
      return *this;
    }
    swap(rhs);
    rhs.clear();
    return *this;
  }

  std::pair<iterator, bool> insert(const_reference value) {
    bool is_append = true;
    auto it = iterator(phantom_node_->left_);
    if (empty()) {
      phantom_node_->left_ = allocateAndConstruct(value);
      phantom_node_->left_->parent_ = phantom_node_;
    } else {
      size_t old_size = size_;
      phantom_node_->left_ = _insert(phantom_node_->left_, nullptr, value);
      if (size_ == old_size) {
        is_append = false;
        it = end();
      } else {
        it = find(value);
      }
    }
    return std::make_pair(it, is_append);
  }

  TreeNode<Key>* find(TreeNode<Key>* node, const_reference value) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (comparator_(value, node->data_)) {
      return find(node->left_, value);
    }
    if (comparator_(node->data_, value)) {
      return find(node->right_, value);
    } else {
      return node;
    }
    return nullptr;
  }

  iterator end() { return iterator(phantom_node_); }

  iterator begin() {
    TreeNode<Key>* node = findMin(phantom_node_->left_);
    return iterator(node);
  }

  iterator rbegin() {
    TreeNode<Key>* node = findMax(phantom_node_->left_);
    return iterator(node);
  }

  iterator rbegin() const {
    TreeNode<Key>* node = findMax(phantom_node_->left_);
    return iterator(node);
  }

  iterator rend() { return iterator(phantom_node_); }

  iterator end() const { return iterator(phantom_node_); }

  iterator begin() const {
    TreeNode<Key>* node = findMin(phantom_node_->left_);
    return iterator(node);
  }

  size_t max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  size_type size() const noexcept { return size_; }

  void erase(iterator pos) { deleteNode(pos.ptr_); }

  void erase(const_reference value) {
    TreeNode<Key>* node_for_delete = find(phantom_node_->left_, value);
    if (node_for_delete) {
      deleteNode(node_for_delete);
      // if (size_ != 0) {
      //   balance(phantom_node_->left_);
      // }
    }
  }

  bool empty() const noexcept { return size_ == 0; }

  void clear() {
    _clear(phantom_node_->left_);
    phantom_node_->left_ = nullptr;
  }

  void swap(set& rhs) {
    std::swap(allocator_, rhs.allocator_);
    std::swap(allocator_node_, rhs.allocator_node_);
    std::swap(size_, rhs.size_);
    std::swap(phantom_node_, rhs.phantom_node_);
    std::swap(comparator_, rhs.comparator_);
  }

  void merge(set& rhs) {
    set new_rhs;
    for (auto& item : rhs) {
      std::pair<iterator, bool> answer = insert(item);
      if (answer.second == false) {
        new_rhs.insert(item);
      }
    }
    rhs = new_rhs;
  }

  iterator find(const Key& key) const {
    TreeNode<Key>* it = find(phantom_node_->left_, key);
    if (it == nullptr) {
      return end();
    }
    return iterator(it);
  }

  bool contains(const Key& key) const { return find(key) != end(); }

 private:
  void _clear(TreeNode<Key>* node) {
    if (node == nullptr) {
      return;
    }
    if (!node->left_ && !node->right_) {
      deleteLeaf(node);
      return;
    }
    if (node->left_) {
      _clear(node->left_);
    }
    if (node->right_) {
      _clear(node->right_);
    }
    deleteLeaf(node);
  }

  void deleteNode(TreeNode<Key>* node) {
    if (node == nullptr) {
      return;
    }
    size_t count_childs = howManyChildren(node);
    switch (count_childs) {
      case 0:
        deleteLeaf(node);
        break;
      case 1:
        deleteNodeWithOneChild(node);
        break;
      case 2:
        node = deleteNodeWithTwoChildren(node);
        break;
    }
  }

  TreeNode<Key>* deleteNodeWithTwoChildren(TreeNode<Key>*& node) {
    TreeNode<Key>* min = findMin(node->right_);
    if (node->right_ == min) {
      min->parent_ = node->parent_;
      node->parent_ = setupParent(min, node->parent_);
      min->left_ = node->left_;
      node->left_->parent_ = min;
      destroyAndDeallocate(node);
    } else if (howManyChildren(min) == 0) {
      min->parent_->left_ = nullptr;
      min->parent_ = node->parent_;
      node->parent_ = setupParent(min, node->parent_);
      min->left_ = node->left_;
      min->right_ = node->right_;
      node->left_->parent_ = min;
      node->right_->parent_ = min;
      destroyAndDeallocate(node);
    } else {
      min->parent_->left_ = min->right_;
      min->right_->parent_ = min->parent_;
      min->parent_ = node->parent_;
      node->parent_ = setupParent(min, node->parent_);
      min->left_ = node->left_;
      min->right_ = node->right_;
      node->left_->parent_ = min;
      node->right_->parent_ = min;
      destroyAndDeallocate(node);
    }
    return min;
  }

  TreeNode<Key>* setupParent(TreeNode<Key>* node, TreeNode<Key>* parent) {
    if (parent == end().ptr_) {
      parent->left_ = node;
    } else {
      if (comparator_(node->data_, parent->data_)) {
        parent->left_ = node;
      } else {
        parent->right_ = node;
      }
    }
    node->parent_ = parent;
    return parent;
  }

  void deleteNodeWithOneChild(TreeNode<Key>* node) {
    if (node->right_) {
      deleteNodeWithRightChild(node);
    } else if (node->left_) {
      deleteNodeWithLeftChild(node);
    }
  }

  void deleteNodeWithRightChild(TreeNode<Key>* node) {
    TreeNode<Key>* child = node->right_;
    TreeNode<Key>* parent = node->parent_;
    child->parent_ = parent;
    if (comparator_(parent->data_, child->data_)) {
      parent->right_ = child;
    } else if (comparator_(child->data_, parent->data_)) {
      parent->left_ = child;
    }
    destroyAndDeallocate(node);
  }

  void deleteNodeWithLeftChild(TreeNode<Key>* node) {
    TreeNode<Key>* child = node->left_;
    TreeNode<Key>* parent = node->parent_;
    child->parent_ = parent;
    if (comparator_(parent->data_, child->data_) && parent != phantom_node_) {
      parent->right_ = child;

    } else if (comparator_(child->data_, parent->data_)) {
      parent->left_ = child;
    }
    destroyAndDeallocate(node);
  }

  void deleteLeaf(TreeNode<Key>* node) {
    TreeNode<Key>* parent = node->parent_;
    if (parent == phantom_node_) {
      destroyAndDeallocate(node);
      phantom_node_->left_ = nullptr;
      return;
    }
    if (comparator_(node->data_, parent->data_)) {
      parent->left_ = nullptr;
    } else {
      parent->right_ = nullptr;
    }

    destroyAndDeallocate(node);
  }

  size_t howManyChildren(TreeNode<Key>* node) const {
    size_t count = 0;
    if (node->right_) ++count;
    if (node->left_) ++count;
    return count;
  }

  TreeNode<Key>* findMin(TreeNode<Key>* node) const {
    while (node && node->left_) {
      node = node->left_;
    }
    return node;
  }

  TreeNode<Key>* findMax(TreeNode<Key>* node) const {
    while (node && node->right_) {
      node = node->right_;
    }
    return node;
  }

  void destroyAndDeallocate(TreeNode<Key>* node) {
    std::allocator_traits<allocator_type>::destroy(allocator_, &(node->data_));
    std::allocator_traits<node_allocator>::deallocate(allocator_node_, node, 1);
    --size_;
  }

  TreeNode<Key>* allocateAndConstruct(const_reference value) {
    TreeNode<Key>* node =
        std::allocator_traits<node_allocator>::allocate(allocator_node_, 1);
    std::allocator_traits<allocator_type>::construct(allocator_, &(node->data_),
                                                     value);
    ++size_;
    initNode(node);
    return node;
  }

  void initNode(TreeNode<Key>* node) {
    node->left_ = nullptr;
    node->right_ = nullptr;
    node->parent_ = nullptr;
    node->height_ = 0;
  }

  TreeNode<Key>* leftRotate(TreeNode<Key>* node) {
    TreeNode<Key>* tmp_node = node->left_;
    if (tmp_node->right_ != nullptr) {
      tmp_node->right_->parent_ = node;
    }
    node->left_ = tmp_node->right_;
    if (node->left_ != nullptr) {
      node->left_->parent_ = node;
    }
    tmp_node->right_ = node;
    tmp_node->parent_ = node->parent_;
    node->parent_ = tmp_node;
    if (tmp_node->parent_ != phantom_node_ &&
        comparator_(node->data_, tmp_node->parent_->data_)) {
      tmp_node->parent_->left_ = tmp_node;
    } else {
      if (tmp_node->parent_ != phantom_node_) {
        tmp_node->parent_->right_ = tmp_node;
      }
    }
    node = tmp_node;
    setHeight(node->left_);
    setHeight(node->right_);
    setHeight(node);
    setHeight(node->parent_);
    return node;
  }

  TreeNode<Key>* rightRotate(TreeNode<Key>* node) {
    TreeNode<Key>* tmp_node = node->right_;
    node->right_ = tmp_node->left_;
    if (tmp_node->left_ != nullptr) {
      tmp_node->left_->parent_ = node;
    }
    tmp_node->left_ = node;
    tmp_node->parent_ = node->parent_;
    node->parent_ = tmp_node;
    if (tmp_node->parent_ != nullptr && tmp_node->parent_ != phantom_node_ &&
        comparator_(node->data_, tmp_node->parent_->data_)) {
      tmp_node->parent_->left_ = tmp_node;
    } else {
      if (tmp_node->parent_ != nullptr && tmp_node->parent_ != phantom_node_) {
        tmp_node->parent_->right_ = tmp_node;
      }
    }
    node = tmp_node;
    setHeight(node->left_);
    setHeight(node->right_);
    setHeight(node);
    setHeight(node->parent_);
    return node;
  }

  TreeNode<Key>* rightLeftRotate(TreeNode<Key>* node) {
    node->left_ = rightRotate(node->left_);
    return leftRotate(node);
  }

  TreeNode<Key>* leftRightRotate(TreeNode<Key>* node) {
    node->right_ = leftRotate(node->right_);
    return rightRotate(node);
  }

  TreeNode<Key>* balance(TreeNode<Key>* node) {
    int first_height = 0;
    int second_height = 0;
    if (node->left_ != nullptr) {
      first_height = node->left_->height_;
    }
    if (node->right_ != nullptr) {
      second_height = node->right_->height_;
    }
    if (std::abs(first_height - second_height) == 2) {
      if (first_height < second_height) {
        int right_height1 = 0;
        int right_height2 = 0;
        if (node->right_->right_ != nullptr) {
          right_height2 = node->right_->right_->height_;
        }
        if (node->right_->left_ != nullptr) {
          right_height1 = node->right_->left_->height_;
        }
        if (right_height1 > right_height2) {
          node = leftRightRotate(node);
        } else {
          node = rightRotate(node);
        }
      } else {
        int left_height1 = 0;
        int left_height2 = 0;
        if (node->left_->right_ != nullptr) {
          left_height2 = node->left_->right_->height_;
        }
        if (node->left_->left_ != nullptr) {
          left_height1 = node->left_->left_->height_;
        }
        if (left_height1 > left_height2) {
          node = leftRotate(node);
        } else {
          node = rightLeftRotate(node);
        }
      }
    }
    return node;
  }

  TreeNode<Key>* _insert(TreeNode<Key>* node, TreeNode<Key>* parent,
                         const_reference value) {
    if (node == nullptr) {
      node = allocateAndConstruct(value);
      node->height_ = 1;
      node->parent_ = parent;
    } else if (comparator_(value, node->data_)) {
      node->left_ = _insert(node->left_, node, value);
      int first_height = 0;
      int second_height = 0;
      if (node->left_ != nullptr) {
        first_height = node->left_->height_;
      }
      if (node->right_ != nullptr) {
        second_height = node->right_->height_;
      }
      if (std::abs(first_height - second_height) == 2) {
        if (node->left_ != nullptr && comparator_(value, node->left_->data_)) {
          node = leftRotate(node);
        } else {
          node = rightLeftRotate(node);
        }
      }
    } else if (comparator_(node->data_, value)) {
      node->right_ = _insert(node->right_, node, value);
      int first_height = 0;
      int second_height = 0;
      if (node->left_ != nullptr) {
        first_height = node->left_->height_;
      }
      if (node->right_ != nullptr) {
        second_height = node->right_->height_;
      }
      if (std::abs(first_height - second_height) == 2) {
        if (node->right_ != nullptr &&
            comparator_(value, node->right_->data_)) {
          node = leftRightRotate(node);
        } else {
          node = rightRotate(node);
        }
      }
    } else {
    }
    setHeight(node);
    return node;
  }

  void setHeight(TreeNode<Key>* node) {
    if (node == nullptr) return;
    int val = 1;
    if (node->left_ != nullptr) val = node->left_->height_ + 1;
    if (node->right_ != nullptr) val = std::max(val, node->right_->height_ + 1);
    node->height_ = val;
  }

 private:
  Compare comparator_;
  allocator_type allocator_;
  node_allocator allocator_node_;
  size_t size_;
  TreeNode<Key>* phantom_node_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SET_SET_H_
