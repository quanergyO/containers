#ifndef CPP2_S21_CONTAINERS_1_ITERATORS_RANDOM_ACCESS_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_ITERATORS_RANDOM_ACCESS_ITERATOR_H_

#include "iterators_traits.h"

namespace s21
{
    template <typename T, typename IteratorTraits>
    class RandomAccessIterator
    {
    public:
        using value_type = typename IteratorTraits::value_type;
        using difference_type = typename IteratorTraits::difference_type;
        using pointer = typename IteratorTraits::pointer;
        using reference = typename IteratorTraits::reference;
        using iterator_category = typename IteratorTraits::iterator_category;

        RandomAccessIterator() = delete;
        RandomAccessIterator(pointer ptr) : ptr_(ptr) {}
        RandomAccessIterator(const RandomAccessIterator<T, IteratorTraits> &rhs)
            : ptr_(rhs.ptr_) {}
        RandomAccessIterator &operator=(const RandomAccessIterator<T, IteratorTraits> &rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }
            ptr_ = rhs.ptr_;
            return *this;
        }

        ~RandomAccessIterator() = default;

        RandomAccessIterator &operator++()
        {
            ++ptr_;
            return *this;
        }

        RandomAccessIterator &operator--()
        {
            --ptr_;
            return *this;
        }

        RandomAccessIterator<T, IteratorTraits> operator++(int)
        {
            RandomAccessIterator<T, IteratorTraits> copy = *this;
            ++ptr_;
            return copy;
        }

        RandomAccessIterator<T, IteratorTraits> operator--(int)
        {
            RandomAccessIterator<T, IteratorTraits> copy = *this;
            --ptr_;
            return copy;
        }

        RandomAccessIterator &operator+=(int step)
        {
            ptr_ += step;
            return *this;
        }

        RandomAccessIterator &operator-=(int step)
        {
            ptr_ -= step;
            return *this;
        }

        RandomAccessIterator &operator+=(const RandomAccessIterator<T, IteratorTraits> &rhs)
        {
            ptr_ += rhs.ptr_;
            return *this;
        }

        RandomAccessIterator &operator-=(const RandomAccessIterator<T, IteratorTraits> &rhs)
        {
            ptr_ -= rhs.ptr_;
            return *this;
        }

        RandomAccessIterator<T, IteratorTraits> operator+(int step) const
        {
            return RandomAccessIterator<T, IteratorTraits>(ptr_ + step);
        }

        friend RandomAccessIterator &operator+(const int num, const RandomAccessIterator& rhs)
        {
            return rhs + num;
        }

        RandomAccessIterator<T, IteratorTraits> operator-(int step) const
        {
            return RandomAccessIterator<T, IteratorTraits>(ptr_ - step);
        }

        RandomAccessIterator<T, IteratorTraits> operator+(const RandomAccessIterator<T, IteratorTraits> &rhs)
        {
            return RandomAccessIterator<T, IteratorTraits>(ptr_ + rhs.ptr_);
        }

        difference_type operator-(const RandomAccessIterator<T, IteratorTraits> &rhs)
        {
            return ptr_ - rhs.ptr_;
        }

        bool operator==(const RandomAccessIterator<T, IteratorTraits> &rhs) const noexcept
        {
            return ptr_ == rhs.ptr_;
        }

        bool operator!=(const RandomAccessIterator<T, IteratorTraits> &rhs) const noexcept
        {
            return ptr_ != rhs.ptr_;
        }

        reference operator*()
        {
            return *ptr_;
        }

        pointer operator->()
        {
            return ptr_;
        }

        reference operator[](size_t index)
        {
            return *(ptr_ + index);
        }

        bool operator<(const RandomAccessIterator<T, IteratorTraits> &rhs) const noexcept
        {
            return ptr_ < rhs.ptr_;
        }

        bool operator>(const RandomAccessIterator<T, IteratorTraits> &rhs) const noexcept
        {
            return ptr_ > rhs.ptr_;
        }

        bool operator<=(const RandomAccessIterator<T, IteratorTraits> &rhs) const noexcept
        {
            return ptr_ <= rhs.ptr_;
        }

        bool operator>=(const RandomAccessIterator<T, IteratorTraits> &rhs) const noexcept
        {
            return ptr_ >= rhs.ptr_;
        }

    private:
        pointer ptr_;
    };

} // namespace s21

#endif // CPP2_S21_CONTAINERS_1_ITERATORS_RANDOM_ACCESS_ITERATOR_H_