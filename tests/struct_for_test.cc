#ifndef CPP2_S21_CONTAINERS_1_TESTS_STRUCT_FOR_TEST
#define CPP2_S21_CONTAINERS_1_TESTS_STRUCT_FOR_TEST

#include <cstddef>
#include <iostream>

namespace s21 
{

struct StructWithExceptionInConstruct {
  size_t *num_;
  size_t size_;
  static size_t count_;
  static size_t COUNT_OBJECTS_FOR_EXCEPTION;
  StructWithExceptionInConstruct() : num_(new size_t[10]), size_(10) {
    ++count_;
    if (count_ == COUNT_OBJECTS_FOR_EXCEPTION)
      throw std::invalid_argument("Test Exception");
  }

  StructWithExceptionInConstruct(const StructWithExceptionInConstruct &rhs)
      : num_(new size_t[rhs.size_]), size_(rhs.size_) {
    for (size_t i = 0; i < size_; ++i) {
      num_[i] = rhs.num_[i];
    }
  }

  StructWithExceptionInConstruct &operator=(
      const StructWithExceptionInConstruct &rhs) {
    if (this == &rhs) return *this;
    delete[] num_;
    num_ = new size_t[rhs.size_];
    size_ = rhs.size_;
    for (size_t i = 0; i < size_; ++i) num_[i] = rhs.num_[i];

    return *this;
  }

  ~StructWithExceptionInConstruct() {
    --count_;
    delete[] num_;
  }

  bool operator==(const StructWithExceptionInConstruct &rhs) const {
    if (size_ != rhs.size_) return false;
    for (size_t i = 0; i < size_; ++i) {
      if (num_[i] != rhs.num_[i]) return false;
    }
    return true;
  }
};

size_t s21::StructWithExceptionInConstruct::count_ = 0;
size_t s21::StructWithExceptionInConstruct::COUNT_OBJECTS_FOR_EXCEPTION = 5;

} // namespace s21

#endif // CPP2_S21_CONTAINERS_1_TESTS_STRUCT_FOR_TEST