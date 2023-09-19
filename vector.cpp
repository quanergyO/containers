#include <iostream>

template <typename T>
class Vector
{
private:
    T* begin_;
    T* end_;
    T* buff_end_;
public:
    size_t size() const noexcept
    {
        return end_ - begin_;
    }

    size_t capacity() const noexcept
    {
        return buff_end_ - begin_;
    }

    Vector(size_t count, const T& value = T())
        : begin_(reinterpret_cast<T*>(new char[count * sizeof(T)]))
        , end_ (begin_ + count)
        , buff_end_ (begin_ + count)
    {
        T* it = begin_;
        try
        {
            for (; it != end_; ++it)
            {
                new (it) T(value);
            }
        }
        catch (...)
        {
            for (T* del = begin_; del != it; ++del)
            {
                del->~T();
            }
            delete[] reinterpret_cast<char*>(begin_);
            throw;
        }
    }

    void reserve(const size_t newCap)
    {
        if (capacity() > newCap) return;
        T* newArr = reinterpret_cast<T*>(new char[newCap * sizeof(T)]);
        size_t i = 0;
        try
        {
            for (; i < size(); ++i)
            {
                new (newArr + i) T(begin_[i]);
            }
        } catch (...)
        {
            for (size_t j = 0; j < i; ++j) {
                (newArr + j)->~T();
            }
            delete[] reinterpret_cast<char*>(newArr);
            throw;
        }
        size_t end = size();
        for (T* del = begin_; del != end_; ++del) {
            del->~T();
        }
        delete[] reinterpret_cast<char*>(begin_);
        begin_ = newArr;
        end_ = begin_ + end;
        buff_end_ = begin_ + newCap;
    }

    void push_back(const T& value)
    {
        if (end_ == buff_end_) {
            reserve(std::max(1, 2 * capacity()));
        }

        new (end_) T(value);
        ++end_;
    }

};
