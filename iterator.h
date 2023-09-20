#pragma once
#include <iterator>

template <typename T>
class RandomAccessIterator
{
public:
    using difference_type = std::ptrdiff_t;

    RandomAccessIterator() : ptr_(nullptr) {}
    RandomAccessIterator(T* ptr) : ptr_(ptr) {}
    RandomAccessIterator(const RandomAccessIterator<T> &rhs)
        : ptr_(rhs.ptr_) {}

    ~RandomAccessIterator()   = default;
    RandomAccessIterator& operator++()
    {
        ++ptr_;
        return *this;
    }

    RandomAccessIterator& operator--()
    {
        --ptr_;
        return *this;
    }

    RandomAccessIterator<T> operator++(int)
    {
        RandomAccessIterator<T> copy = *this;
        ++ptr_;
        return copy;
    }

    RandomAccessIterator<T> operator--(int)
    {
        RandomAccessIterator<T> copy = *this;
        --ptr_;
        return copy;
    }

    RandomAccessIterator& operator+=(int step)
    {
        ptr_ += step;
        return *this;
    }

    RandomAccessIterator& operator-=(int step)
    {
        ptr_ -= step;
        return *this;
    }

    RandomAccessIterator& operator+=(const RandomAccessIterator<T> &rhs)
    {
        ptr_ += rhs.ptr_;
        return *this;
    }

    RandomAccessIterator& operator-=(const RandomAccessIterator<T> &rhs)
    {
        ptr_ -= rhs.ptr_;
        return *this;
    }

    RandomAccessIterator<T> operator+(int step) const
    {

        return RandomAccessIterator<T>(ptr_ + step);
    }

    RandomAccessIterator<T> operator-(int step) const
    {

        return RandomAccessIterator<T>(ptr_ - step);
    }

    RandomAccessIterator<T> operator+(const RandomAccessIterator<T> &rhs)
    {
        return RandomAccessIterator<T>(ptr_ + rhs.ptr_);
    }

    RandomAccessIterator<T> operator-(const RandomAccessIterator<T> &rhs)
    {
        return RandomAccessIterator<T>(ptr_ - rhs.ptr_);
    }

    bool operator==(const RandomAccessIterator<T> &rhs) const noexcept
    {
        return ptr_ == rhs.ptr_;
    }

    bool operator!=(const RandomAccessIterator<T> &rhs) const noexcept
    {
        return ptr_ != rhs.ptr_;
    }

    T& operator*()
    {
        return *ptr_;
    }

    T* operator->()
    {
        return ptr_;
    }

    bool operator<(const RandomAccessIterator<T> &rhs) const noexcept
    {
        return ptr_ < rhs.ptr_;
    }

    bool operator>(const RandomAccessIterator<T> &rhs) const noexcept
    {
        return ptr_ > rhs.ptr_;
    }

    bool operator<=(const RandomAccessIterator<T> &rhs) const noexcept
    {
        return ptr_ <= rhs.ptr_;
    }

    bool operator>=(const RandomAccessIterator<T> &rhs) const noexcept
    {
        return ptr_ >= rhs.ptr_;
    }





private:
    T* ptr_;
};
