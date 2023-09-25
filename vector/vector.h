#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <limits>
#include "../allocator.h"

namespace s21 {


template <typename T, typename Allocator = Allocator<T>>
class vector {
public:
    class VectorIterator;
    class VectorConstIterator;

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

    vector(const Allocator& alloc = Allocator());
    explicit vector(size_type n, const Allocator& alloc = Allocator());
    vector(std::initializer_list<value_type> const &items
         , const Allocator& alloc = Allocator());
    vector(const vector &rhs);
    vector(vector &&rhs) noexcept;
    ~vector();
    vector& operator=(vector &&rhs) noexcept;

    reference at(size_type pos);
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    const_reference front() const;
    const_reference back() const;
    iterator data() noexcept;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void reserve(size_type size);
    size_type capacity() const noexcept;
    void shrink_to_fit();

    void clear();
    iterator insert(iterator pos, const_reference value);
    void erase(iterator pos);
    void push_back(const_reference value);
    void pop_back();
    void swap(vector &other);

    template <typename ...Args>
    iterator insert_many(const_iterator pos, Args&&... args);

    template <typename ...Args>
    void insert_many_back(Args&&... args);

private:
    size_type size_;
    size_type capacity_;
    Allocator allocator_;
    T* data_;
};
} // namespace s21

#ifndef VECTOR_ITERATOR_H_
#define VECTOR_ITERATOR_H_

namespace s21 {

template <typename T, typename Allocator>
class vector<T, Allocator>::VectorIterator {
public:
    VectorIterator() = default;
    VectorIterator(iterator ptr);

    reference operator*();
    VectorIterator operator++(int);
    VectorIterator operator--(int);
    VectorIterator& operator++();
    VectorIterator& operator--();

    bool operator==(const VectorIterator& rhs) const;
    bool operator!=(const VectorIterator& rhs) const;
    bool operator<(const VectorIterator& rhs) const;
    bool operator>(const VectorIterator& rhs) const;
    bool operator<=(const VectorIterator& rhs) const;
    bool operator>=(const VectorIterator& rhs) const;

    VectorIterator operator+(int n) const;
    VectorIterator operator-(int n) const;
    ptrdiff_t operator-(const VectorIterator& other) const;

private:
    iterator ptr_;
};

} // namespace s21

#ifndef VECTOR_ITERATOR_TPP_
#define VECTOR_ITERATOR_TPP_

namespace s21 {

template <typename T, typename Allocator>
vector<T, Allocator>::VectorIterator::VectorIterator(iterator ptr) : ptr_(ptr) {}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::VectorIterator::operator*() {
    return *ptr_;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::VectorIterator vector<T, Allocator>::VectorIterator::operator++(int) {
    VectorIterator tmp(*this);
    ++ptr_;
    return tmp;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::VectorIterator vector<T, Allocator>::VectorIterator::operator--(int) {
    VectorIterator tmp(*this);
    --ptr_;
    return tmp;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::VectorIterator& vector<T, Allocator>::VectorIterator::operator++() {
    ++ptr_;
    return *this;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::VectorIterator& vector<T, Allocator>::VectorIterator::operator--() {
    --ptr_;
    return *this;
}

template <typename T, typename Allocator>
bool vector<T, Allocator>::VectorIterator::operator==(const VectorIterator& rhs) const {
    return ptr_ == rhs.ptr_;
}

template <typename T, typename Allocator>
bool vector<T, Allocator>::VectorIterator::operator!=(const VectorIterator& rhs) const {
    return ptr_ != rhs.ptr_;
}

template <typename T, typename Allocator>
bool vector<T, Allocator>::VectorIterator::operator<(const VectorIterator& rhs) const {
    return ptr_ < rhs.ptr_;
}

template <typename T, typename Allocator>
bool vector<T, Allocator>::VectorIterator::operator>(const VectorIterator& rhs) const {
    return ptr_ > rhs.ptr_;
}

template <typename T, typename Allocator>
bool vector<T, Allocator>::VectorIterator::operator<=(const VectorIterator& rhs) const {
    return ptr_ <= rhs.ptr_;
}

template <typename T, typename Allocator>
bool vector<T, Allocator>::VectorIterator::operator>=(const VectorIterator& rhs) const {
    return ptr_ >= rhs.ptr_;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::VectorIterator vector<T, Allocator>::VectorIterator::operator+(int n) const {
    return VectorIterator(ptr_ + n);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::VectorIterator vector<T, Allocator>::VectorIterator::operator-(int n) const {
    return VectorIterator(ptr_ - n);
}

template <typename T, typename Allocator>
ptrdiff_t vector<T, Allocator>::VectorIterator::operator-(const VectorIterator& other) const {
    return ptr_ - other.ptr_;
}


} // namespace s21

#endif // VECTOR_ITERATOR_TPP_

#endif // VECTOR_ITERATOR_H_

#include "vector_iterator.h"

#endif // VECTOR_H_


#ifndef VECTOR_TPP_
#define VECTOR_TPP_

namespace s21 {

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const Allocator& alloc)
    : size_(0)
    , capacity_(10)
    , allocator_(alloc)
    , data_(allocator_.allocate(capacity_))
    {}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(size_type n, const Allocator& alloc)
    : size_(0)
    , capacity_(n * 2)
    , allocator_(alloc)
    , data_(allocator_.allocate(capacity_))
    {}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(std::initializer_list<value_type> const &items
                            , const Allocator& alloc)
    : size_(items.size())
    , capacity_(size_ * 2)
    , allocator_(alloc)
    , data_(allocator_.allocate(capacity_)) {
    std::copy(items.begin(), items.end(), data_);
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const vector &rhs)
    : size_(rhs.size_)
    , capacity_(rhs.capacity_)
    , allocator_(rhs.allocator_)
    , data_(allocator_.allocate(capacity_)) {
    std::copy(rhs.begin(), rhs.end(), data_);
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(vector &&rhs) noexcept {
    size_ = std::exchange(rhs.size_, 0);
    capacity_ = std::exchange(rhs.capacity_, 0);
    allocator_ = std::move(rhs.allocator_);
    data_ = std::exchange(rhs.data_, nullptr);
}

template <typename T, typename Allocator>
vector<T, Allocator>::~vector() {
    for (auto it = this->begin(); it != this->end(); ++it) {
        allocator_.destroy(&*it);
    }
    allocator_.deallocate(data_, capacity_);
}

template <typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(vector &&rhs) noexcept {
    if (this == &rhs) return *this;
    this->swap(rhs);

    for (auto it = rhs.begin(); it != rhs.end(); ++it) {
        rhs.allocator_.destroy(&*it);
    }
    rhs.allocator_.deallocate(rhs.data_, rhs.capacity_);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos) {
    if (pos >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[pos];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](size_type pos) {
    return data_[pos];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](size_type pos) const {
    return data_[pos];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const {
    if (!size_) {
        throw std::out_of_range("vector is empty");
    }
    return data_[0];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const {
    if (!size_) {
        throw std::out_of_range("vector is empty");
    }
    return data_[size_ - 1];
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::data() noexcept {
    return data_;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() {
    return VectorIterator(data_);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::end() {
    return VectorIterator(data_ + size_);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::cbegin() const {
    const VectorIterator it(data_);
    return it;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::cend() const {
    const VectorIterator it(data_ + size_);
    return it;
}

template <typename T, typename Allocator>
bool vector<T, Allocator>::empty() const noexcept {
    return size_ == 0;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const noexcept {
    return size_;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const noexcept {
    return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_type size) {
    if (size <= capacity_) return;
    if (size > max_size()) throw std::invalid_argument("Too large size");

    T* newArr = allocator_.allocate(size);
    size_type i = 0;
    iterator it = begin();
    try {
        for (; it != end(); ++it, ++i) {
            allocator_.construct(newArr + i, *it);
        }
    } catch (...) {
        for (size_type j = 0; j < i; ++j) {
            allocator_.destroy(newArr + j);
        }
        allocator_.deallocate(newArr, size);
    }
    for (auto &it : *this) {
        allocator_.destroy(&it);
    }
    allocator_.deallocate(data_, capacity_);
    capacity_ = size;
    data_ = newArr;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const noexcept {
    return capacity_;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::shrink_to_fit() {
    if (size_ == capacity_) return;

    T* newArr = allocator_.allocate(size_);
    size_type i = 0;
    iterator it = begin();
    try {
        for (; it != end(); ++it, ++i) {
            allocator_.construct(newArr + i, *it);
        }
    } catch (...) {
        for (size_type j = 0; j < i; ++j) {
            allocator_.destroy(newArr + j);
        }
        allocator_.deallocate(newArr, size_);
    }
    for (auto &it : *this) {
        allocator_.destroy(&it);
    }
    allocator_.deallocate(data_, capacity_);
    capacity_ = size_;
    data_ = newArr;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::clear() {
    size_ = 0;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator pos, const_reference value) {
    if (size_ == capacity_) {
        reserve(capacity_ ? capacity_ * 2 : 1);
    }

    for (auto ptr = end(); ptr != pos; --ptr) {
        *ptr = *(ptr - 1);
    }
    *pos = value;
    ++size_;
    return pos;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::erase(iterator pos) {
    for (auto ptr = pos; ptr != end(); ++ptr) {
        *ptr = *(ptr + 1);
    }
    --size_;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::push_back(const_reference value) {
    if (size_ == capacity_) {
        reserve(capacity_ ? capacity_ * 2 : 1);
    }
    allocator_.construct(data_ + size_, value);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::pop_back() {
    if (size_ > 0) {
        allocator_.destroy(data_ + size_ - 1);
        --size_;
    }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::swap(vector &other) {
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(allocator_, other.allocator_);
    std::swap(size_, other.size_);
}

template <typename T, typename Allocator>
template <typename... Args>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert_many(const_iterator pos,
                                                                          Args&&... args) {

}


} // namespace s21

#endif // VECTOR_TPP_
