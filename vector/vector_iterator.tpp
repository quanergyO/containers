#ifndef VECTOR_ITERATOR_TPP_
#define VECTOR_ITERATOR_TPP_

namespace s21 {

template <typename T>
vector<T>::VectorIterator::VectorIterator(iterator ptr) : ptr_(ptr) {}

template <typename T>
typename vector<T>::reference vector<T>::VectorIterator::operator*() {
    return *ptr_;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator++(int) {
    VectorIterator tmp(*this);
    ++ptr_;
    return tmp;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator--(int) {
    VectorIterator tmp(*this);
    --ptr_;
    return tmp;
}

template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator++() {
    ++ptr_;
    return *this;
}

template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator--() {
    --ptr_;
    return *this;
}

template <typename T>
bool vector<T>::VectorIterator::operator==(const VectorIterator& rhs) const {
    return ptr_ == rhs.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator!=(const VectorIterator& rhs) const {
    return ptr_ != rhs.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator<(const VectorIterator& rhs) const {
    return ptr_ < rhs.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator>(const VectorIterator& rhs) const {
    return ptr_ > rhs.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator<=(const VectorIterator& rhs) const {
    return ptr_ <= rhs.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator>=(const VectorIterator& rhs) const {
    return ptr_ >= rhs.ptr_;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator+(int n) const {
    return VectorIterator(ptr_ + n);
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator-(int n) const {
    return VectorIterator(ptr_ - n);
}

template <typename T>
ptrdiff_t vector<T>::VectorIterator::operator-(const VectorIterator& other) const {
    return ptr_ - other.ptr_;
}


} // namespace s21

#endif // VECTOR_ITERATOR_TPP_
