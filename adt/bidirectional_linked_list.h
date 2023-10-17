#ifndef CPP2_S21_CONTAINERS_1_ADT_BIDIRECTIONAL_LINKED_LIST_H_
#define CPP2_S21_CONTAINERS_1_ADT_BIDIRECTIONAL_LINKED_LIST_H_

namespace s21
{

template <typename T>
class Node {
public:
    T data_;
    Node* prev_ = nullptr;
    Node* next_ = nullptr;
};

template <typename T>
class BidirectionalLinkedList
{
public:
    Node<T>* head_;
    Node<T>* tail_;

    BidirectionalLinkedList()
        : head_(nullptr)
        , tail_(nullptr)
        {}
    
    ~BidirectionalLinkedList() {
        while (head_ != nullptr) {
            pop_front();
        }
    }
    
    Node<T>* push_front(const T& data) {
        Node<T> *ptr = new Node(data);
        ptr->next_ = head_;
        if (head_ != nullptr) {
            head_->prev_ = ptr;
        }
        if (tail_ == nullptr) {
            tail_ = ptr;
        }
        head_ = ptr;

        return ptr;
    }

    Node<T>* push_back(const T& data) {
        Node<T> *ptr = new Node(data);
        ptr->prev_ = tail_;
        if (tail_ != nullptr) {
            tail_->next_ = ptr;
        }
        if (head_ == nullptr) {
            head_ = ptr;
        }
        tail_ = ptr;

        return ptr;
    }

    void pop_front() {
        if (head_ == nullptr) return;
        Node<T> *ptr = head_->next_;
        if (ptr != nullptr) {
            ptr->prev_ = nullptr;
        }
        else {
            tail_ = nullptr;
        }
        delete head_;
        head_ = ptr;
    }

    void pop_back() {
        if (tail_ == nullptr) return;
        Node<T> *ptr = tail_->prev_;
        if (ptr != nullptr) {
            ptr->next_ = nullptr;
        }
        else {
            head_ = nullptr;
        }
        delete tail_;
        tail_ = ptr;
    }

    Node<T>* getAt(size_t index) {
        Node<T> *ptr = head_;
        for (size_t i = 0; i < index; ++i) {
            ptr = ptr->next_;
        }
        return ptr;
    }

    Node<T>* operator[](size_t index) {
        return getAt(index);
    }

    Node<T>* insert(int index, const T& data) {
        Node<T> *right = getAt(index);
        if (right == nullptr) {
            return push_back(data);
        }

        Node<T> *left = right->prev_;
        if (left == nullptr) {
            return push_front(data);
        }

        Node<T> *ptr = new Node(data);
        ptr->prev_ = left;
        ptr->next_ = right;
        left->next_ = ptr;
        right->prev_ = ptr;

        return ptr;
    }

    void erase(size_t index) {
        Node<T>* ptr = getAt(index);
        if (ptr == nullptr) {
            return;
        }

        if (ptr->prev_ == nullptr) {
            pop_front();
            return;
        }
        if (ptr->next_ == nullptr) {
            pop_back();
            return;
        }
        Node<T> *left = ptr->prev_;
        Node<T> *right = ptr->next_;
        left->next_ = right;
        right->prev_ = left;
        delete ptr;
    }
};

} // namespace s21

#endif // CPP2_S21_CONTAINERS_1_ADT_BIDIRECTIONAL_LINKED_LIST_H_
