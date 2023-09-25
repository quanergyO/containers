#ifndef VECTOR_ITERATOR_H_
#define VECTOR_ITERATOR_H_

namespace s21 {

template <typename T, typename Allocator = Allocator<T>>
class vector<T>::VectorIterator {
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

#endif // VECTOR_ITERATOR_H_
