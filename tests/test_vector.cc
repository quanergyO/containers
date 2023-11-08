#include <vector>

#include "../src/vector/vector.h"

TEST(VectorConstructors, True) {
  s21::vector<int> school1;
  std::vector<int> std1;
  ASSERT_EQ(school1.size(), std1.size());
  s21::vector<int> school2(5);
  std::vector<int> std2(5);
  ASSERT_EQ(school2.size(), std2.size());
  s21::vector<int> school3{1, 2, 3, 4, 5};
  std::vector<int> std3{1, 2, 3, 4, 5};
  for (size_t i = 0; i < school3.size(); ++i) {
    ASSERT_EQ(school3[i], std3[i]);
  }
  s21::vector<int> school4 = school3;
  std::vector<int> std4 = std3;
  for (size_t i = 0; i < school4.size(); ++i) {
    ASSERT_EQ(school4[i], std4[i]);
  }
  s21::vector<int> school5 = std::move(school4);
  std::vector<int> std5 = std::move(std4);
  for (size_t i = 0; i < school5.size(); ++i) {
    ASSERT_EQ(school5[i], std5[i]);
  }
}

TEST(VectorOperatorEquals, True) {
  s21::vector<int> school1{1, 2, 3};
  std::vector<int> std1{1, 2, 3};
  s21::vector<int> school2;
  std::vector<int> std2;
  school2 = school1;
  std2 = std1;
  for (size_t i = 0; i < school2.size(); ++i) {
    ASSERT_EQ(school2[i], std2[i]);
  }
}

TEST(Vector, OperatorMoveEqual) {
  s21::vector<int> school1{1, 2, 3};
  std::vector<int> std1{1, 2, 3};
  s21::vector<int> school2;
  std::vector<int> std2;
  school2 = std::move(school1);
  std2 = std::move(std1);
  for (size_t i = 0; i < school2.size(); ++i) {
    ASSERT_EQ(school2[i], std2[i]);
  }
}

TEST(VectorAt2, True) {
  s21::vector<int> school1{1, 2, 3};
  std::vector<int> std1{1, 2, 3};
  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1.at(i), std1.at(i));
  }
}

TEST(VectorAt, False) {
  s21::vector<int> school1{1, 2, 3};
  ASSERT_ANY_THROW(school1.at(4));
}

TEST(VectorOperatorBrackets, True) {
  s21::vector<int> school1(10);
  std::vector<int> std1(10);
  for (size_t i = 0; i < 10; ++i) {
    school1[i] = std1[i] = i * i;
  }
  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1[i], std1[i]);
  }
}

TEST(VectorFront, True) {
  s21::vector<int> school1{1, 2, 3};
  std::vector<int> std1{1, 2, 3};
  ASSERT_EQ(school1.front(), std1.front());
}

TEST(VectorFront, False) {
  s21::vector<int> school1;
  ASSERT_ANY_THROW(school1.front());
}

TEST(VectorBack, True) {
  s21::vector<int> school1{1, 2, 3};
  std::vector<int> std1{1, 2, 3};
  ASSERT_EQ(school1.back(), std1.back());
}

TEST(VectorBack, False) {
  s21::vector<int> school1;
  ASSERT_ANY_THROW(school1.back());
}

TEST(VectorData, True) {
  s21::vector<int> school1{1, 2, 3, 4, 5};
  int *tmp = school1.data();
  s21::vector<int> school2 = std::move(school1);
  ASSERT_EQ(tmp, school2.data());
}

TEST(VectorEmpty, True) {
  s21::vector<int> school1;
  ASSERT_EQ(school1.empty(), true);
  school1.push_back(1);
  ASSERT_EQ(school1.empty(), false);
}

TEST(VectorSize, True) {
  s21::vector<int> school1;
  ASSERT_EQ(school1.size(), (size_t)0);
  school1.push_back(1);
  ASSERT_EQ(school1.size(), (size_t)1);
  for (int i = 0; i < 10; ++i) school1.push_back(i);
  ASSERT_EQ(school1.size(), (size_t)11);
}

TEST(VectorCapacity, True) {
  s21::vector<int> school1;
  ASSERT_EQ(school1.capacity(), (size_t)10);
  school1.push_back(1);
  ASSERT_EQ(school1.capacity(), (size_t)10);
  for (int i = 0; i < 10; ++i) school1.push_back(i);
  ASSERT_EQ(school1.capacity(), (size_t)20);
}

TEST(VectorIterator2, True) {
  s21::vector<int> school1{1, 2, 3, 4, 5};
  s21::vector<int> school2(5);
  std::copy(school1.begin(), school1.end(), school2.begin());
  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1[i], school2[i]);
  }
}

TEST(VectorShrinkToFit, True) {
  s21::vector<int> school1{5, 3, 2, 4};
  std::vector<int> std1{5, 3, 2, 4};
  school1.shrink_to_fit();
  std1.shrink_to_fit();
  ASSERT_EQ(school1.capacity(), std1.capacity());
}

TEST(VectorReserve, True) {
  s21::vector<int> school1{5, 3, 2, 4};
  std::vector<int> std1{5, 3, 2, 4};
  school1.reserve(50);
  std1.reserve(50);
  ASSERT_EQ(school1.capacity(), std1.capacity());
}

TEST(VecotorClear, True) {
  s21::vector<int> school1{5, 3, 2, 4};
  std::vector<int> std1{5, 3, 2, 4};
  school1.clear();
  std1.clear();
  ASSERT_EQ(school1.size(), std1.size());
}

TEST(VectorInsert, True) {
  s21::vector<int> school1{5, 3, 2, 4};
  std::vector<int> std1{5, 3, 2, 4};
  school1.insert(school1.begin() + 2, 100);
  std1.insert(std1.begin() + 2, 100);
  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1[i], std1[i]);
  }
}

TEST(VectorErase, True) {
  s21::vector<int> school1{5, 3, 2, 4};
  std::vector<int> std1{5, 3, 2, 4};
  school1.erase(school1.begin() + 2);
  std1.erase(std1.begin() + 2);
  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1[i], std1[i]);
  }
}

TEST(VectorPushBack, True) {
  s21::vector<int> school1{5, 3, 2, 4};
  std::vector<int> std1{5, 3, 2, 4};
  for (size_t i = 1; i < 100; ++i) {
    school1.push_back(i * i);
    std1.push_back(i * i);
  }
  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1[i], std1[i]);
  }
}

TEST(VectorPopBack, True) {
  s21::vector<int> school1{5, 3, 2, 4};
  std::vector<int> std1{5, 3, 2, 4};
  for (size_t i = 1; i < 2; ++i) {
    school1.pop_back();
    std1.pop_back();
  }
  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1[i], std1[i]);
  }
}

TEST(VectorSwap, True) {
  s21::vector<int> school1{5, 3, 2, 4};
  std::vector<int> std1{5, 3, 2, 4};
  s21::vector<int> school2{1, 2, 3};
  std::vector<int> std2{1, 2, 3};
  school1.swap(school2);
  std1.swap(std2);

  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1[i], std1[i]);
  }
  for (size_t i = 0; i < school2.size(); ++i) {
    ASSERT_EQ(school2[i], std2[i]);
  }
}

TEST(VectorConstOperatorIndex, True) {
  const s21::vector<int> school1{5, 3, 2, 4};
  const std::vector<int> std1{5, 3, 2, 4};
  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1[i], std1[i]);
  }
}

TEST(VectorInsertMany, True) {
  s21::vector<int> school1{-1, -2, -3};
  s21::vector<int> school2{-1, -2, 1, 2, 3, 4, 5, -3};
  school1.insert_many(school1.begin() + 2, 1, 2, 3, 4, 5);
  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1[i], school2[i]);
  }
}

TEST(VectorInsertManyBack, True) {
  s21::vector<int> school1{-1, -2, -3};
  s21::vector<int> school2{-1, -2, -3, 1, 2, 3, 4, 5};
  school1.insert_many_back(1, 2, 3, 4, 5);
  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1[i], school2[i]);
  }
}

TEST(Vector, ReserveMaxSize) {
  s21::vector<int> school1;
  size_t max_size = school1.max_size();
  ASSERT_ANY_THROW(school1.reserve(max_size + 1));
}

TEST(Vector, InsertWithReserve) {
  s21::vector<int> school1{1, 2, 3};
  s21::vector<int> result1{10, 1, 2, 3};
  school1.shrink_to_fit();
  school1.insert(school1.begin(), 10);
  for (size_t i = 0; i < school1.size(); ++i) {
    ASSERT_EQ(school1[i], result1[i]);
  }
}

TEST(Vector, ShrinkToFitWithEqualsSizeAndCapacity) {
  s21::vector<int> school1;
  for (int i = 0; i < 10; ++i) {
    school1.push_back(i);
  }
  school1.shrink_to_fit();
  ASSERT_EQ(school1.capacity(), static_cast<size_t>(10));
}

TEST(Vector, ReserveManyThenCapacity) {
  s21::vector<int> school1;
  size_t current_capacity = school1.capacity();
  school1.reserve(1);
  ASSERT_EQ(school1.capacity(), current_capacity);
}
