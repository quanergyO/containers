#ifndef CPP2_S21_CONTAINERS_1_VECTOR_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_VECTOR_VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>

#include "../iterators/random_access_iterator.h"
#include "../utils/allocator.h"

namespace s21 {
template <typename T, typename Allocator = Allocator<T>>
class vector {
<<<<<<< HEAD
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = RandomAccessIterator<T, iterator_traits<T *>>;
  using const_iterator = RandomAccessIterator<T, iterator_traits<const T *>>;
  using size_type = size_t;
  using allocator_type = Allocator;

  vector(const Allocator &alloc = Allocator())
      : size_(0),
        capacity_(10),
        allocator_(alloc),
        data_(std::allocator_traits<allocator_type>::allocate(allocator_,
                                                              capacity_)) {}

  explicit vector(size_type n, const Allocator &alloc = Allocator())
      : size_(n),
        capacity_(n * 2),
        allocator_(alloc),
        data_(std::allocator_traits<allocator_type>::allocate(allocator_,
                                                              capacity_)) {
    for (auto &it : *this) {
      std::allocator_traits<allocator_type>::construct(allocator_, &it);
    }
  }

  vector(std::initializer_list<value_type> const &items,
         const Allocator &alloc = Allocator())
      : size_(items.size()),
        capacity_(size_ * 2),
        allocator_(alloc),
        data_(std::allocator_traits<allocator_type>::allocate(allocator_,
                                                              capacity_)) {
    auto ptr = items.begin();
    for (auto &it : *this) {
      std::allocator_traits<allocator_type>::construct(allocator_, &it, *ptr);
      ++ptr;
    }
  }

  vector(const vector &rhs)
      : size_(rhs.size_),
        capacity_(rhs.capacity_),
        allocator_(rhs.allocator_),
        data_(std::allocator_traits<allocator_type>::allocate(allocator_,
                                                              capacity_)) {
    size_t i = 0;
    for (auto &it : *this)
    {
      std::allocator_traits<allocator_type>::construct(allocator_, &it,
                                                       rhs.data_[i++]);
    }
  }

  vector(vector &&rhs) noexcept {
    size_ = std::exchange(rhs.size_, 0);
    capacity_ = std::exchange(rhs.capacity_, 0);
    allocator_ = std::move(rhs.allocator_);
    data_ = std::exchange(rhs.data_, nullptr);
  }

  vector &operator=(const vector &rhs) {
    vector<value_type> copy = rhs;
    swap(copy);

    return *this;
  }

  vector &operator=(vector &&rhs) noexcept {
    if (this == &rhs) return *this;
    swap(rhs);
    destroy_objects_in_array(rhs.begin(), rhs.end());
    std::allocator_traits<allocator_type>::deallocate(rhs.allocator_, rhs.data_,
                                                      rhs.capacity_);
    return *this;
  }

  ~vector() {
    destroy_objects_in_array(begin(), end());
    std::allocator_traits<allocator_type>::deallocate(allocator_, data_,
                                                      capacity_);
  }



  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference operator[](size_type pos) const { return data_[pos]; }

  const_reference front() const {
    if (!size_) {
      throw std::out_of_range("vector is empty");
    }
    return data_[0];
  }

  const_reference back() const {
    if (!size_) {
      throw std::out_of_range("vector is empty");
    }
    return data_[size_ - 1];
  }

  T *data() noexcept { return data_; }

  iterator begin() { return iterator(data_); }

  const_iterator begin() const { return const_iterator(data_); }

  iterator end() { return iterator(data_ + size_); }

  const_iterator end() const { return const_iterator(data_ + size_); }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
  }

  void reserve(size_type size) {
    if (size <= capacity_) return;
    if (size > max_size()) throw std::invalid_argument("Too large size");

    T *newArr =
        std::allocator_traits<allocator_type>::allocate(allocator_, size);
    size_type count_constructed_objects = 0;
    iterator it = begin();
    try {
      for (; it != end(); ++it, ++count_constructed_objects) {
        std::allocator_traits<allocator_type>::construct(allocator_, newArr + count_constructed_objects,
                                                         *it);
      }
    } catch (...) {
      destroy_objects_in_array(newArr, newArr + count_constructed_objects);
      std::allocator_traits<allocator_type>::deallocate(allocator_, newArr,
                                                        size);
      throw;
    }
    destroy_objects_in_array(begin(), end());
    std::allocator_traits<allocator_type>::deallocate(allocator_, data_,
                                                      capacity_);
    capacity_ = size;
    data_ = newArr;
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() {
    if (size_ == capacity_) return;

    T *newArr =
        std::allocator_traits<allocator_type>::allocate(allocator_, size_);
    size_type count_constructed_objects = 0;
    iterator it = begin();
    try {
      for (; it != end(); ++it, ++count_constructed_objects) {
        std::allocator_traits<allocator_type>::construct(allocator_, newArr + count_constructed_objects,
                                                         *it);
      }
    } catch (...) {
      destroy_objects_in_array(newArr, newArr + count_constructed_objects);
      std::allocator_traits<allocator_type>::deallocate(allocator_, newArr,
                                                        size_);
      throw;
    }
    destroy_objects_in_array(begin(), end());
    std::allocator_traits<allocator_type>::deallocate(allocator_, data_,
                                                      capacity_);
    capacity_ = size_;
    data_ = newArr;
  }

  void clear() {
    destroy_objects_in_array(begin(), end());
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    size_t index = pos - begin();
    if (size_ == capacity_) {
      reserve(capacity_ ? capacity_ * 2 : 1);
    }
    pos = begin() + index;
    for (auto ptr = end(); ptr != pos; --ptr) {
      *ptr = std::move(*(ptr - 1));  // !?
    }
    *pos = value;
    ++size_;
    return pos;
  }

  void erase(iterator pos) {
    destroy_objects_in_array(pos, pos+1);
    for (auto ptr = pos; ptr != end(); ++ptr) {
      *ptr = std::move(*(ptr + 1));
    }
    --size_;
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(capacity_ ? capacity_ * 2 : 1);
    }
    std::allocator_traits<allocator_type>::construct(allocator_, data_ + size_,
                                                     value);
    ++size_;
  }

  void pop_back() {
    if (size_ > 0) {
      destroy_objects_in_array(data_ + size_ - 1, data_ + size_);
      --size_;
    }
  }

  void swap(vector &other) {
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(allocator_, other.allocator_);
    std::swap(size_, other.size_);
  }

  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args) {
    size_t args_count = sizeof...(args);
    size_t capacity_need = capacity_ > size_ + args_count ? capacity_ : capacity_ * 2;
    T* newArr = std::allocator_traits<allocator_type>::allocate(allocator_, capacity_need);
    size_t count_constructed_objects = 0;
    iterator newPos = newArr;
    try {
      for (auto it = begin(); it != pos; ++it) {
        newArr[count_constructed_objects++] = *it;
      }
      newPos += count_constructed_objects;
      for (auto &it : {args...}) {
        newArr[count_constructed_objects++] = it;
      }
      for (auto it = pos; it != end(); ++it) {
        newArr[count_constructed_objects++] = *it;
      }
    } catch (...) {
      destroy_objects_in_array(newArr, newArr + count_constructed_objects);
      throw;
    }

    destroy_objects_in_array(begin(), end());
    std::allocator_traits<allocator_type>::deallocate(allocator_, data_, capacity_);
    data_ = newArr;
    capacity_ = capacity_need;
    size_ += args_count;

    return newPos;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
  }
 private:
  void destroy_objects_in_array(iterator begin, iterator end)
  {
    for (auto it = begin; it != end; ++it)
    {
      std::allocator_traits<allocator_type>::destroy(allocator_, &*it);
    }
  }
  

 private:
  size_type size_;
  size_type capacity_;
  Allocator allocator_;
  T *data_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_VECTOR_VECTOR_H_
=======
public:
    class VectorIterator;

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = VectorIterator;
    using const_iterator = const VectorIterator;
    using size_type = size_t;

    class VectorIterator {
    public:
        VectorIterator() = delete;
        VectorIterator(T* ptr) : ptr_(ptr) {}

        reference operator*() {
            return *ptr_;
        }

        VectorIterator operator++(int) {
            VectorIterator tmp(*this);
            ++ptr_;
            return tmp;
        };

        VectorIterator operator--(int) {
            VectorIterator tmp(*this);
            --ptr_;
            return tmp;
        }

        VectorIterator& operator++() {
            ++ptr_;
            return *this;
        }

        VectorIterator& operator--() {
            --ptr_;
            return *this;
        }
        // all noexcept
        bool operator==(const VectorIterator& rhs) const {
            return ptr_ == rhs.ptr_;
        }

        bool operator!=(const VectorIterator& rhs) const {
            return ptr_ != rhs.ptr_;
        }

        bool operator<(const VectorIterator& rhs) const {
            return ptr_ < rhs.ptr_;
        }

        bool operator>(const VectorIterator& rhs) const {
            return ptr_ > rhs.ptr_;
        }

        bool operator<=(const VectorIterator& rhs) const {
            return ptr_ <= rhs.ptr_;
        }

        bool operator>=(const VectorIterator& rhs) const {
            return ptr_ >= rhs.ptr_;
        }

        VectorIterator operator+(int n) const {
            return VectorIterator(ptr_ + n);
        }

        VectorIterator operator-(int n) const {
            return VectorIterator(ptr_ - n);
        }

        ptrdiff_t operator-(const VectorIterator& other) const {
            return ptr_ - other.ptr_;
        }

    private:
        T* ptr_;
    };
    class VectorConstIterator;



    vector(const Allocator& alloc = Allocator())
        : size_(0)
        , capacity_(10)
        , allocator_(alloc)
        , data_(allocator_.allocate(capacity_))
    {}

    explicit vector(size_type n, const Allocator& alloc = Allocator())
        : size_(0)
        , capacity_(n * 2)
        , allocator_(alloc)
        , data_(allocator_.allocate(capacity_))
    {}

    vector(std::initializer_list<value_type> const &items , const Allocator& alloc = Allocator())
        : size_(items.size())
        , capacity_(size_ * 2)
        , allocator_(alloc)
        , data_(allocator_.allocate(capacity_)) {
        std::copy(items.begin(), items.end(), data_);
    }

    vector(const vector &rhs)
        : size_(rhs.size_)
        , capacity_(rhs.capacity_)
        , allocator_(rhs.allocator_)
        , data_(allocator_.allocate(capacity_)) {
        std::copy(rhs.begin(), rhs.end(), data_);
    }

    vector(vector &&rhs) noexcept {
        size_ = std::exchange(rhs.size_, 0);
        capacity_ = std::exchange(rhs.capacity_, 0);
        allocator_ = std::move(rhs.allocator_);
        data_ = std::exchange(rhs.data_, nullptr);
    }

    ~vector() {
        for (auto it = this->begin(); it != this->end(); ++it) {
            allocator_.destroy(&*it);
        }
        allocator_.deallocate(data_, capacity_);
    }

    // operator=(copy)

    vector& operator=(vector &&rhs) noexcept {
        if (this == &rhs) return *this;
        this->swap(rhs);

        for (auto it = rhs.begin(); it != rhs.end(); ++it) {
            rhs.allocator_.destroy(&*it);
        }
        rhs.allocator_.deallocate(rhs.data_, rhs.capacity_);
    }

    reference at(size_type pos) {
        if (pos >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[pos];
    }

    reference operator[](size_type pos) {
        return data_[pos];
    }

    const_reference operator[](size_type pos) const {
        return data_[pos];
    }

    const_reference front() const {
        if (!size_) {
            throw std::out_of_range("vector is empty");
        }
        return data_[0];
    }

    const_reference back() const {
        if (!size_) {
            throw std::out_of_range("vector is empty");
        }
        return data_[size_ - 1];
    }

    T* data() noexcept {
        return data_;
    }

    iterator begin() {
        return VectorIterator(data_);
    }

    iterator begin() const {
        return VectorIterator(data_);
    }

    iterator end()  {
        return VectorIterator(data_ + size_);
    }

    iterator end() const  {
        return VectorIterator(data_ + size_);
    }

    const_iterator cbegin() const {
        const T* tmp = data_;
        return VectorIterator (tmp);
    }

    const_iterator cend() const {
        const T* tmp = data_;
        return VectorIterator (tmp);
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    size_type size() const noexcept {
        return size_;
    }

    size_type max_size() const noexcept {
        return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
    }

    void reserve(size_type size) {
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

    size_type capacity() const noexcept {
        return capacity_;
    }

    void shrink_to_fit() {
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

    void clear()  {
        for (auto &it : *this) {
            allocator_.destroy(&it);
        }
        size_ = 0;
    }

    iterator insert(iterator pos, const_reference value) {
        if (size_ == capacity_) {
            reserve(capacity_ ? capacity_ * 2 : 1);
        }

        for (auto ptr = end(); ptr != pos; --ptr) {
            *ptr = *(ptr - 1);  // operator= delete
            // construct
        }
        *pos = value;
        ++size_;
        return pos;
    }

    void erase(iterator pos) {
        // destroy current
        for (auto ptr = pos; ptr != end(); ++ptr) {
            *ptr = *(ptr + 1);
        }
        --size_;
    }

    void push_back(const_reference value) {
        if (size_ == capacity_) {
            reserve(capacity_ ? capacity_ * 2 : 1);
        }
        allocator_.construct(data_ + size_, value);
        ++size_;
    }

    void pop_back() {
        if (size_ > 0) {
            allocator_.destroy(data_ + size_ - 1);
            --size_;
        }
    }

    void swap(vector &other) {
        std::swap(data_, other.data_);
        std::swap(capacity_, other.capacity_);
        std::swap(allocator_, other.allocator_);
        std::swap(size_, other.size_);
    }

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

#endif // VECTOR_H_
>>>>>>> c90c561a36ae65f801b5381ae85dec9a25b8e911
