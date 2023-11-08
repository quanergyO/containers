#ifndef CPP2_S21_CONTAINERS_1_MAP_MAP_H_
#define CPP2_S21_CONTAINERS_1_MAP_MAP_H_

#include <functional>
#include <limits>
#include <memory>
#include <utility>
#include <vector>

#include "../iterators/iterator_tree.h"
#include "../../utils/allocator.h"
#include "../../utils/compare_for_map.h"

namespace s21 {

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>>
class map {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = TreeIterator<value_type, iterator_traits<value_type*>, map>;
  using const_iterator =
      TreeIterator<value_type, iterator_traits<const value_type*>, map>;
  using size_type = size_t;
  using allocator_type = Allocator;
  using node_allocator = typename std::allocator_traits<
      allocator_type>::template rebind_alloc<TreeNode<value_type>>;

 public:
  map(const Allocator& alloc = Allocator())
      : comparator_(MapCompare<value_type, Compare>()),
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

  map(std::initializer_list<value_type> const& items,
      const Allocator& alloc = Allocator())
      : map(alloc) {
    for (auto& item : items) {
      insert(item);
    }
  }

  map(const map& other)
      : comparator_(other.comparator_),
        allocator_(other.allocator_),
        allocator_node_(other.allocator_node_),
        size_(0),
        phantom_node_(std::allocator_traits<node_allocator>::allocate(
            allocator_node_, 1)) {
    initNode(phantom_node_);
    // can be optimization (insert(root) insert(root->left) insert(root->right))
    for (auto& item : other) {
      insert(item);
    }
  }

  map(map&& other)
      : comparator_(std::move(other.comparator_)),
        allocator_(std::move(other.allocator_)),
        allocator_node_(std::move(other.allocator_node_)),
        size_(std::exchange(other.size_, 0)),
        phantom_node_(std::exchange(other.phantom_node_, nullptr)) {}

  ~map() noexcept {
    if (phantom_node_) {
      clear();
      std::allocator_traits<node_allocator>::deallocate(allocator_node_,
                                                        phantom_node_, 1);
    }
  }

  map operator=(const map& other) {
    if (this == &other) {
      return *this;
    }
    map copy = other;
    swap(copy);
    return *this;
  }

  map operator=(map&& other) {
    if (this == &other) {
      return *this;
    }
    swap(other);
    other.clear();
    return *this;
  }

  mapped_type& at(const key_type& key) const {
    TreeNode<value_type>* node = _find(phantom_node_->left_, key);
    if (node == nullptr) {
      throw std::out_of_range("Key not in map");
    }
    return node->data_.second;
  }

  mapped_type& operator[](const key_type& key) {
    return _find(phantom_node_->left_, key)->data_.second;
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
        it = find(value.first);
      }
    }
    return std::make_pair(it, is_append);
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    return insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
    iterator it = find(key);
    if (it == end()) {
      return insert(key, obj);
    }
    operator[](key) = obj;
    return std::make_pair(it, true);
  }

  iterator find(const key_type& key) const {
    TreeNode<value_type>* node = _find(phantom_node_->left_, key);
    if (node == nullptr) {
      return end();
    }
    return iterator(node);
  }

  iterator begin() noexcept { return iterator(findMin(phantom_node_->left_)); }
  iterator end() noexcept { return iterator(phantom_node_); }
  iterator begin() const noexcept {
    return iterator(findMin(phantom_node_->left_));
  }
  iterator end() const noexcept { return iterator(phantom_node_); }
  size_type size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }
  size_t max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(value_type);
  }

  void clear() noexcept {
    _clear(phantom_node_->left_);
    initNode(phantom_node_);
  }

  void swap(map& rhs) noexcept {
    std::swap(comparator_, rhs.comparator_);
    std::swap(allocator_, rhs.allocator_);
    std::swap(allocator_node_, rhs.allocator_node_);
    std::swap(size_, rhs.size_);
    std::swap(phantom_node_, rhs.phantom_node_);
  }

  void erase(iterator pos) { deleteNode(pos.ptr_); }

  bool contains(const key_type& key) { return find(key) != end(); }

  void merge(map& other) {
    map new_other;
    for (auto& item : other) {
      if (!contains(item.first)) {
        insert(item);
      } else {
        new_other.insert(item);
      }
    }
    other = new_other;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> return_vector;
    for (auto& item : {args...}) {
      return_vector.push_back(insert(item));
    }
    return return_vector;
  }

 private:
  void initNode(TreeNode<value_type>* node) {
    node->left_ = nullptr;
    node->right_ = nullptr;
    node->parent_ = nullptr;
  }

  void _clear(TreeNode<value_type>* node) noexcept {
    if (node == nullptr) {
      return;
    }
    if (node->left_) {
      _clear(node->left_);
    }
    if (node->right_) {
      _clear(node->right_);
    }
    destroyAndDeallocate(node);
  }

  void updateHeight(TreeNode<value_type>* root) {
    if (root == nullptr) return;
    int val = 1;
    if (root->left_ != nullptr) val = root->left_->height_ + 1;
    if (root->right_ != nullptr) val = std::max(val, root->right_->height_ + 1);
    root->height_ = val;
  }

  TreeNode<value_type>* leftRotate(TreeNode<value_type>* root) {
    TreeNode<value_type>* tmp_node = root->left_;
    if (tmp_node->right_ != nullptr) {
      tmp_node->right_->parent_ = root;
    }
    root->left_ = tmp_node->right_;
    if (root->left_ != nullptr) {
      root->left_->parent_ = root;
    }
    tmp_node->right_ = root;
    tmp_node->parent_ = root->parent_;
    root->parent_ = tmp_node;
    if (tmp_node->parent_ != phantom_node_ &&
        comparator_(root->data_, tmp_node->parent_->data_)) {
      tmp_node->parent_->left_ = tmp_node;
    } else {
      if (tmp_node->parent_ != phantom_node_) {
        tmp_node->parent_->right_ = tmp_node;
      }
    }
    root = tmp_node;
    updateHeight(root->left_);
    updateHeight(root->right_);
    updateHeight(root);
    updateHeight(root->parent_);
    return root;
  }

  TreeNode<value_type>* rightRotate(TreeNode<value_type>* root) {
    TreeNode<value_type>* tmp_node = root->right_;
    root->right_ = tmp_node->left_;
    if (tmp_node->left_ != nullptr) {
      tmp_node->left_->parent_ = root;
    }
    tmp_node->left_ = root;
    tmp_node->parent_ = root->parent_;
    root->parent_ = tmp_node;
    if (tmp_node->parent_ != nullptr && tmp_node->parent_ != phantom_node_ &&
        comparator_(root->data_, tmp_node->parent_->data_)) {
      tmp_node->parent_->left_ = tmp_node;
    } else {
      if (tmp_node->parent_ != nullptr && tmp_node->parent_ != phantom_node_) {
        tmp_node->parent_->right_ = tmp_node;
      }
    }
    root = tmp_node;
    updateHeight(root->left_);
    updateHeight(root->right_);
    updateHeight(root);
    updateHeight(root->parent_);
    return root;
  }

  TreeNode<value_type>* rightLeftRotate(TreeNode<value_type>* root) {
    root->left_ = rightRotate(root->left_);
    return leftRotate(root);
  }

  TreeNode<value_type>* leftRightRotate(TreeNode<value_type>* root) {
    root->right_ = leftRotate(root->right_);
    return rightRotate(root);
  }

  TreeNode<value_type>* balance(TreeNode<value_type>* root) {
    int first_height = 0;
    int second_height = 0;
    if (root->left_ != nullptr) {
      first_height = root->left_->height_;
    }
    if (root->right_ != nullptr) {
      second_height = root->right_->height_;
    }
    if (std::abs(first_height - second_height) == 2) {
      if (first_height < second_height) {
        int right_height1 = 0;
        int right_height2 = 0;
        if (root->right_->right_ != nullptr) {
          right_height2 = root->right_->right_->height_;
        }
        if (root->right_->left_ != nullptr) {
          right_height1 = root->right_->left_->height_;
        }
        if (right_height1 > right_height2) {
          root = leftRightRotate(root);
        } else {
          root = rightRotate(root);
        }
      } else {
        int left_height1 = 0;
        int left_height2 = 0;
        if (root->left_->right_ != nullptr) {
          left_height2 = root->left_->right_->height_;
        }
        if (root->left_->left_ != nullptr) {
          left_height1 = root->left_->left_->height_;
        }
        if (left_height1 > left_height2) {
          root = leftRotate(root);
        } else {
          root = rightLeftRotate(root);
        }
      }
    }
    return root;
  }

  TreeNode<value_type>* _insert(TreeNode<value_type>* root,
                                TreeNode<value_type>* parent,
                                const_reference value) {
    if (root == nullptr) {
      root = allocateAndConstruct(value);
      root->height_ = 1;
      root->parent_ = parent;
    } else if (comparator_(value, root->data_)) {
      root->left_ = _insert(root->left_, root, value);
      int first_height = 0;
      int second_height = 0;
      if (root->left_ != nullptr) {
        first_height = root->left_->height_;
      }
      if (root->right_ != nullptr) {
        second_height = root->right_->height_;
      }
      if (std::abs(first_height - second_height) == 2) {
        if (root->left_ != nullptr && comparator_(value, root->left_->data_)) {
          root = leftRotate(root);
        } else {
          root = rightLeftRotate(root);
        }
      }
    } else if (comparator_(root->data_, value)) {
      root->right_ = _insert(root->right_, root, value);
      int first_height = 0;
      int second_height = 0;
      if (root->left_ != nullptr) {
        first_height = root->left_->height_;
      }
      if (root->right_ != nullptr) {
        second_height = root->right_->height_;
      }
      if (std::abs(first_height - second_height) == 2) {
        if (root->right_ != nullptr &&
            comparator_(value, root->right_->data_)) {
          root = leftRightRotate(root);
        } else {
          root = rightRotate(root);
        }
      }
    } else {
    }
    updateHeight(root);
    return root;
  }

  TreeNode<value_type>* _find(TreeNode<value_type>* node,
                              const key_type& key) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (Compare{}(key, node->data_.first)) {
      return _find(node->left_, key);
    }
    if (Compare{}(node->data_.first, key)) {
      return _find(node->right_, key);
    }
    return node;
  }

  TreeNode<value_type>* findMin(TreeNode<value_type>* node) const {
    while (node && node->left_) {
      node = node->left_;
    }
    return node;
  }

  void deleteNode(TreeNode<value_type>*& node) {
    if (node == nullptr) {
      return;
    }
    size_t count_childs = howMuchChildren(node);
    switch (count_childs) {
      case 0:
        deleteLeaf(node);
        break;
      case 1:
        deleteNodeWithOneChild(node);
        break;
      case 2:
        node = deleteNodeWitchTwoChildren(node);
        break;
    }
  }

  TreeNode<value_type>* deleteNodeWitchTwoChildren(
      TreeNode<value_type>*& node) {
    TreeNode<value_type>* min = findMin(node->right_);
    if (node->right_ == min) {
      min->parent_ = node->parent_;
      node->parent_ = setupParent(min, node->parent_);
      min->left_ = node->left_;
      node->left_->parent_ = min;
      destroyAndDeallocate(node);
    } else if (howMuchChildren(min) == 0) {
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

  TreeNode<value_type>* setupParent(TreeNode<value_type>* node,
                                    TreeNode<value_type>* parent) {
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

  void deleteNodeWithOneChild(TreeNode<value_type>* node) {
    if (node->right_) {
      deleteNodeWithRightChild(node);
    } else if (node->left_) {
      deleteNodeWithLeftChild(node);
    }
  }

  void deleteNodeWithRightChild(TreeNode<value_type>* node) {
    TreeNode<value_type>* child = node->right_;
    TreeNode<value_type>* parent = node->parent_;
    child->parent_ = parent;
    if (comparator_(parent->data_, child->data_)) {
      parent->right_ = child;
    } else if (comparator_(child->data_, parent->data_)) {
      parent->left_ = child;
    }
    destroyAndDeallocate(node);
  }

  void deleteNodeWithLeftChild(TreeNode<value_type>* node) {
    TreeNode<value_type>* child = node->left_;
    TreeNode<value_type>* parent = node->parent_;
    child->parent_ = parent;
    if (comparator_(parent->data_, child->data_) && parent != phantom_node_) {
      parent->right_ = child;

    } else if (comparator_(child->data_, parent->data_)) {
      parent->left_ = child;
    }
    destroyAndDeallocate(node);
  }

  void deleteLeaf(TreeNode<value_type>* node) {
    TreeNode<value_type>* parent = node->parent_;
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

  size_t howMuchChildren(TreeNode<value_type>* node) const {
    size_t count = 0;
    if (node->right_) ++count;
    if (node->left_) ++count;
    return count;
  }

  // #############################################

  void destroyAndDeallocate(TreeNode<value_type>* node) {
    std::allocator_traits<allocator_type>::destroy(allocator_, &(node->data_));
    std::allocator_traits<node_allocator>::deallocate(allocator_node_, node, 1);
    --size_;
  }

  TreeNode<value_type>* allocateAndConstruct(const_reference value) {
    TreeNode<value_type>* node =
        std::allocator_traits<node_allocator>::allocate(allocator_node_, 1);
    std::allocator_traits<allocator_type>::construct(allocator_, &(node->data_),
                                                     value);
    ++size_;
    initNode(node);
    return node;
  }

 private:
  MapCompare<value_type, Compare> comparator_;
  allocator_type allocator_;
  node_allocator allocator_node_;
  size_t size_;
  TreeNode<value_type>* phantom_node_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_MAP_MAP_H_
