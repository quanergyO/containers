#include <iostream>
#include <utility>

template <typename T>
class Tree {
  struct Node {
    Node* left_;
    Node* right_;
    Node* parent_;
    T data_;
    size_t height_;

    Node() : left_(nullptr), right_(nullptr), parent_(nullptr), height_(0) {}

    Node(T value)
        : left_(nullptr),
          right_(nullptr),
          parent_(nullptr),
          data_(value),
          height_(1) {}
  };

 public:
  Tree() : root_(nullptr) {}
  ~Tree() { clear(root_); }

  Node* insert(T value) { return _insert(root_, value); }

  void erase(Node* pos) { _remove(root_, pos->data_); }

  void show() { _show(root_); }

 private:
  void _show(Node* node) {
    if (node == nullptr) return;
    if (node->left_) _show(node->left_);
    std::cout << node->data_ << ' ';
    if (node->right_) _show(node->right_);
  }

  void swapNode(Node* lhs, Node* rhs) {
    std::swap(lhs->data_, rhs->data_);
    std::swap(lhs->left_, rhs->left_);
    std::swap(lhs->right_, rhs->right_);
    std::swap(lhs->parent_, rhs->parent_);
  }

  size_t height(Node* node) { return node ? node->height_ : 0; }

  int bfactor(Node* node) { return height(node->right_) - height(node->left_); }

  void fixheigh(Node* node) {
    size_t hl = height(node->left_);
    size_t hr = height(node->right_);
    node->height_ = (hl > hr ? hl : hr) + 1;
  }

  Node* rotateright(Node*& node) {
    Node* tmp = node->left_;
    node->left_ = tmp->right_;
    tmp->right_ = node;
    fixheigh(node);
    fixheigh(tmp);
    return tmp;
  }

  Node* rotateleft(Node*& node) {
    Node* tmp = node->right_;
    node->right_ = tmp->left_;
    tmp->left_ = node;
    fixheigh(node);
    fixheigh(tmp);
    return tmp;
  }

  Node* balance(Node*& p) {
    fixheigh(p);
    if (bfactor(p) == 2) {
      if (bfactor(p->right_) < 0) {
        p->right_ = rotateright(p->right_);
      }
      return rotateleft(p);
    }
    if (bfactor(p) == -2) {
      if (bfactor(p->left_) > 0) {
        p->left_ = rotateleft(p->left_);
      }
      return rotateright(p);
    }
    return p;
  }

  Node* _insert(Node*& p, T value) {
    if (!p) {
      p = new Node(value);
      return p;
    }
    if (value < p->data_) {
      p->left_ = _insert(p->left_, value);
    } else {
      p->right_ = _insert(p->right_, value);
    }
    return balance(p);
  }

  Node* findmin(Node* node) { return node->left ? findmin(node->left_) : node; }

  Node* removemin(Node* node) {
    if (node->left_ == nullptr) return node->right_;
    node->left_ = removemin(node->left_);
    return balance(node);
  }

  Node* _remove(Node* node, T value) {
    if (!node) return nullptr;
    if (value < node->data_) {
      node->left_ = remove(node->left_, value);
    } else if (value > node->data_) {
      node->right_ = remove(node->right_, value);
    } else {
      Node* q = node->left_;
      Node* r = node->right_;
      delete node;
      if (!r) return q;
      Node* min = findmin(r);
      min->right_ = removemin(r);
      min->left_ = q;
      return balance(min);
    }
    return balance(node);
  }

  void clear(Node* node) {
    if (node->left_) clear(node->left_);
    if (node->right_) clear(node->right_);
    if (node) delete node;
  }

  Node* root_;
};