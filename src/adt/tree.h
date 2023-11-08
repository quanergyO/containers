#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_ADT_TREE_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_ADT_TREE_H_

#include <iostream>

namespace s21 {
template <typename Key, typename Value>
class Tree {
 protected:
  struct Node;

 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = Value;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator();
    Iterator(Node *node, Node *last_node = nullptr);
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    reference operator*();
    bool operator==(const iterator &it);
    friend class Tree<Key, Value>;  // только если его тут разместить, взлетает
    bool operator!=(const iterator &it);

   protected:
    Node *iter_node_;
    Node *iter_last_node_;
    Node *Forward(Node *node);
    Node *Back(Node *node);
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    const_reference operator*() const { return Iterator::operator*(); };
  };

  Tree();
  Tree(const Tree &other);
  Tree(Tree &&other);
  ~Tree();
  Tree &operator=(Tree &&other);
  Tree &operator=(const Tree &other);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const Key &key);
  void erase(iterator pos);
  void swap(Tree &other);
  void merge(Tree &other);
  bool contains(const Key &key);

 protected:
  iterator Find(const Key &key);
  struct Node {
    Node(Key key, value_type value);
    Node(Key key, value_type value, Node *parent);
    Key key_;
    value_type value_;
    Node *left_ = nullptr;
    Node *right_ = nullptr;
    Node *parent_ = nullptr;
    int height_ = 0;
    friend class Tree<Key, Value>;
  };
  Node *root_;

  void FreeNode(Node *node);
  Node *CopyTree(Node *node, Node *parent);

  static Node *GetMin(Node *node);
  static Node *GetMax(Node *node);

  // функции балансировки
  void SwapValue(Node *a, Node *b);  // swap only key and value
  void RightRotate(Node *node);
  void LeftRotate(Node *node);
  void Balance(Node *node);
  int GetBalance(Node *node);
  int GetHeight(Node *node);
  void SetHeight(Node *node);

  // проверки рекурсией
  bool RecuInsert(Node *node, const Key &key, Value value);
  Node *RecuDelete(Node *node, Key key);
  size_t RecuSize(Node *node);
  Node *RecuFind(Node *node, const Key &key);
};

template <typename Key, typename Value>
Tree<Key, Value>::Tree() : root_(nullptr) {}

template <typename Key, typename Value>
Tree<Key, Value>::Tree(const Tree &other) {
  root_ = CopyTree(other.root_, nullptr);
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree(Tree &&other) {
  root_ = other.root_;
  other.root_ = nullptr;
}

template <typename Key, typename Value>
Tree<Key, Value>::~Tree() {
  clear();
}

template <typename Key, typename Value>
Tree<Key, Value> &Tree<Key, Value>::operator=(Tree &&other) {
  if (this != &other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }
  return *this;
}

template <typename Key, typename Value>
Tree<Key, Value> &Tree<Key, Value>::operator=(const Tree &other) {
  if (this != &other) {
    Tree temp(other);
    FreeNode(root_);
    *this = std::move(temp);
  }
  return *this;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator Tree<Key, Value>::begin() {
  return Tree::Iterator(GetMin(root_));
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator Tree<Key, Value>::end() {
  if (root_ == nullptr) return begin();

  Node *last_node = GetMax(root_);
  Iterator test(nullptr, last_node);
  return test;
}

template <typename Key, typename Value>
bool Tree<Key, Value>::empty() {
  return root_ == nullptr;
}

template <typename Key, typename Value>
size_t Tree<Key, Value>::size() {
  return RecuSize(root_);
}

template <typename Key, typename Value>
size_t Tree<Key, Value>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename Tree<Key, Value>::Node);
}

template <typename Key, typename Value>
void Tree<Key, Value>::clear() {
  if (root_ != nullptr) FreeNode(root_);
  root_ = nullptr;
}

template <typename Key, typename Value>
std::pair<typename Tree<Key, Value>::Iterator, bool> Tree<Key, Value>::insert(
    const Key &key) {  // обертка для рекурс вставки
  std::pair<Iterator, bool> return_value;
  if (root_ == nullptr) {
    root_ = new Node(key, key);
    return_value.first = Iterator(root_);
    return_value.second = true;
  } else {
    bool is_insert = RecuInsert(root_, key, key);
    return_value.first = Find(key);
    return_value.second = is_insert;
  }
  return return_value;
}

template <typename Key, typename Value>
void Tree<Key, Value>::erase(iterator pos) {
  if (root_ == nullptr || pos.iter_node_ == nullptr) return;
  root_ = RecuDelete(root_, *pos);
}

template <typename Key, typename Value>
void Tree<Key, Value>::swap(Tree &other) {
  std::swap(root_, other.root_);
}

template <typename Key, typename Value>
void Tree<Key, Value>::merge(Tree &other) {
  Tree const_tree(other);
  Iterator const_it = const_tree.begin();
  for (; const_it != const_tree.end(); ++const_it) {
    std::pair<Iterator, bool> pr = insert(*const_it);
    if (pr.second) other.erase(pr.first);
  }
}

template <typename Key, typename Value>
typename Tree<Key, Value>::iterator Tree<Key, Value>::Find(const Key &key) {
  Node *exact_node = RecuFind(root_, key);
  return Iterator(exact_node);
}

template <typename Key, typename Value>
bool Tree<Key, Value>::contains(const Key &key) {
  Node *contain_node = RecuFind(root_, key);
  return !(contain_node == nullptr);
}

// итератор, как его вынести отдельно в папку с итераторами????

template <typename Key, typename Value>
typename Tree<Key, Value>::Node *Tree<Key, Value>::Iterator::Forward(
    Tree::Node *node) {
  if (node->right_ != nullptr) {
    return GetMin(node->right_);
  }
  Node *parent = node->parent_;
  while (parent != nullptr && node == parent->right_) {
    node = parent;
    parent = parent->parent_;
  }
  return parent;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node *Tree<Key, Value>::Iterator::Back(
    Tree::Node *node) {
  if (node->left_ != nullptr) {
    return GetMax(node->left_);
  }
  Node *parent = node->parent_;
  while (parent != nullptr && node == parent->left_) {
    node = parent;
    parent = node->parent_;
  }
  return parent;
}

template <typename Key, typename Value>
Tree<Key, Value>::Iterator::Iterator()
    : iter_node_(nullptr), iter_last_node_(nullptr) {}

template <typename Key, typename Value>
Tree<Key, Value>::Iterator::Iterator(Tree::Node *node, Tree::Node *last_node)
    : iter_node_(node), iter_last_node_(last_node) {}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator &Tree<Key, Value>::Iterator::operator++() {
  Node *tmp;
  if (iter_node_ != nullptr) {
    tmp = GetMax(iter_node_);
  }
  iter_node_ = Forward(iter_node_);
  if (iter_node_ == nullptr) {
    iter_last_node_ = tmp;
  }
  return *this;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator Tree<Key, Value>::Iterator::operator++(
    int) {
  Iterator temp = *this;
  operator++();
  return temp;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator &Tree<Key, Value>::Iterator::operator--() {
  if (iter_node_ == nullptr && iter_last_node_ != nullptr) {
    *this = iter_last_node_;
    return *this;
  }
  iter_node_ = Back(iter_node_);
  return *this;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Iterator Tree<Key, Value>::Iterator::operator--(
    int) {
  Iterator temp = *this;
  operator--();
  return temp;
}

template <typename Key, typename Value>
Value &Tree<Key, Value>::Iterator::operator*() {
  if (iter_node_ == nullptr) {
    static Value dummy_value{};
    return dummy_value;
  }
  return iter_node_->key_;
}

template <typename Key, typename Value>
bool Tree<Key, Value>::Iterator::operator==(const Tree::Iterator &it) {
  return iter_node_ == it.iter_node_;
}

template <typename Key, typename Value>
bool Tree<Key, Value>::Iterator::operator!=(const Tree::Iterator &it) {
  return iter_node_ != it.iter_node_;
}

template <typename Key, typename Value>
Tree<Key, Value>::Node::Node(Key key, value_type value)
    : key_(key), value_(value) {}

template <typename Key, typename Value>
Tree<Key, Value>::Node::Node(Key key, value_type value, Node *node)
    : key_(key), value_(value), parent_(node) {}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node *Tree<Key, Value>::CopyTree(
    Tree::Node *node,
    Tree::Node *parent) {  //  копирование поддерева, ну или дерева
  if (node == nullptr) return nullptr;
  Node *new_node = new Node(node->key_, node->value_, parent);
  new_node->left_ = CopyTree(node->left_, new_node);
  new_node->right_ = CopyTree(node->right_, new_node);
  return new_node;
}

template <typename Key, typename Value>
void Tree<Key, Value>::FreeNode(Node *node) {
  if (node == nullptr) return;
  FreeNode(node->left_);
  FreeNode(node->right_);
  delete node;
}

// балансировка

template <typename Key, typename Value>
int Tree<Key, Value>::GetHeight(Tree::Node *node) {
  return node == nullptr ? -1 : node->height_;  // если ноды нет – высота = -1
}

template <typename Key, typename Value>
int Tree<Key, Value>::GetBalance(Tree::Node *node) {
  return node == nullptr
             ? 0
             : GetHeight(node->right_) -
                   GetHeight(node->left_);  // если ноды нет – баланс- фактор =
                                            // 0 (иначе по формуле)
}

template <typename Key, typename Value>
void Tree<Key, Value>::SetHeight(Tree::Node *node) {
  node->height_ = std::max(GetHeight(node->left_), GetHeight(node->right_)) +
                  1;  // макс это неоптимально, но зато просто; вычисление
                      // высоты для существующей ноды
}

template <typename Key, typename Value>
void Tree<Key, Value>::SwapValue(Tree::Node *a, Tree::Node *b) {
  std::swap(a->key_, b->key_);
  std::swap(a->value_, b->value_);
}

template <typename Key, typename Value>
void Tree<Key, Value>::RightRotate(Tree::Node *node) {
  Node *new_left = node->left_->left_;
  Node *new_right_right = node->right_;
  Node *new_right_left = node->left_->right_;

  SwapValue(node, node->left_);
  node->right_ = node->left_;
  // тут надо перераскидать указатели, ненавижу

  node->left_ = new_left;
  if (node->left_) {
    node->left_->parent_ = node;
  }

  node->right_->left_ = new_right_left;
  if (node->right_->left_) {
    node->right_->left_->parent_ = node->right_;
  }

  node->right_->right_ = new_right_right;
  if (node->right_->right_) {
    node->right_->right_->parent_ = node->right_;
  }
  // вроде работает, но хз
  SetHeight(node->right_);
  SetHeight(node);
}

template <typename Key, typename Value>
void Tree<Key, Value>::LeftRotate(Tree::Node *node) {
  Node *new_right = node->right_->right_;
  Node *new_left_left = node->left_;
  Node *new_left_right = node->right_->left_;

  SwapValue(node, node->right_);
  node->left_ = node->right_;
  // и тут

  node->right_ = new_right;
  if (node->right_) {
    node->right_->parent_ = node;
  }

  node->left_->right_ = new_left_right;
  if (node->left_->right_) {
    node->left_->right_->parent_ = node->left_;
  }

  node->left_->left_ = new_left_left;
  if (node->left_->left_) {
    node->left_->left_->parent_ = node->left_;
  }

  SetHeight(node->left_);
  SetHeight(node);
}

template <typename Key, typename Value>
void Tree<Key, Value>::Balance(Node *node) {  // какой вид поворота нужен
  int balance = GetBalance(node);
  if (balance == -2) {
    if (GetBalance(node->left_) == 1) LeftRotate(node->left_);
    RightRotate(node);
  } else if (balance == 2) {
    if (GetBalance(node->right_) == -1) RightRotate(node->right_);
    LeftRotate(node);
  }
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node *Tree<Key, Value>::GetMin(Tree::Node *node) {
  if (node == nullptr) return nullptr;
  if (node->left_ == nullptr) return node;
  return GetMin(node->left_);
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node *Tree<Key, Value>::GetMax(Tree::Node *node) {
  if (node == nullptr) return nullptr;
  if (node->right_ == nullptr) return node;
  return GetMax(node->right_);
}

// рекурсивные функции, мать всех событий

template <typename Key, typename Value>
size_t Tree<Key, Value>::RecuSize(
    Tree::Node *node) {  // число узлов вроде не проблема
  if (node == nullptr) return 0;
  size_t left_size = RecuSize(node->left_);
  size_t right_size = RecuSize(node->right_);
  return 1 + left_size + right_size;
}

template <typename Key, typename Value>
bool Tree<Key, Value>::RecuInsert(Tree::Node *node, const Key &key,
                                  Value value) {
  bool is_insert = false;
  if (key < node->key_) {
    if (node->left_ == nullptr) {
      node->left_ = new Node(key, value, node);
      is_insert = true;
    } else {
      is_insert = RecuInsert(node->left_, key, value);
    }
  } else if (key > node->key_) {
    if (node->right_ == nullptr) {
      node->right_ = new Node(key, value, node);
      is_insert = true;
    } else {
      is_insert = RecuInsert(node->right_, key, value);
    }
  } else if (key == node->key_) {
    return is_insert;  // инсерт не произошел - такой ключ уже был
  }
  SetHeight(node);
  Balance(node);
  return is_insert;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node *Tree<Key, Value>::RecuDelete(Tree::Node *node,
                                                              Key key) {
  if (node == nullptr) return nullptr;  // нет такого ключа
  if (key < node->key_) {
    node->left_ = RecuDelete(node->left_, key);
  } else if (key > node->key_) {
    node->right_ = RecuDelete(node->right_, key);  // в какое поддерево итти
  } else {
    if (node->left_ == nullptr || node->right_ == nullptr) {  // ищу потомка
      Node *node_right = node->right_;
      Node *node_left = node->left_;
      Node *node_parent = node->parent_;  // запоминаю для перестройки
      delete node;
      if (node_left == nullptr) {
        node = node_right;
      } else {
        node = node_left;
      }
      if (node != nullptr) node->parent_ = node_parent;
    } else {
      Node *min_in_right = GetMin(node->right_);  // это узел на замену текущему
      node->key_ = min_in_right->key_;
      node->value_ = min_in_right->value_;
      node->right_ = RecuDelete(
          node->right_,
          min_in_right->key_);  // убрать текущий после переноса данных
    }
  }
  if (node != nullptr) {
    SetHeight(node);
    Balance(node);
  }
  return node;
}

template <typename Key, typename Value>
typename Tree<Key, Value>::Node *Tree<Key, Value>::RecuFind(Tree::Node *node,
                                                            const Key &key) {
  if (node == nullptr || node->key_ == key) return node;
  if (key > node->key_) {
    return RecuFind(node->right_, key);
  } else {
    return RecuFind(node->left_, key);
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_ADT_TREE_H_