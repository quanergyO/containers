#include <vector>

#include "../vector/vector.h"
#include "struct_for_test.cc"

using test_struct = s21::StructWithExceptionInConstruct;

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

// TEST(VectorConstructorsWithException1, False) {
//   s21::vector<test_struct> school1;
//   std::vector<test_struct> std1;
//   test_struct a, b, c;
//   school1.push_back(a);
//   school1.push_back(b);
//   std1.push_back(a);
//   std1.push_back(b);
//   for (size_t i = 0; i < 2; ++i) {
//     ASSERT_EQ(school1[i], std1[i]);
//   }
//   std1.push_back(c);
//   school1.push_back(c);
//   for (size_t i = 0; i < 3; ++i) {
//     ASSERT_EQ(school1[i], std1[i]);
//   }
// }

// TEST(VectorConstructorsWithException2, False) {
//   test_struct a, b, c;
//   s21::vector<test_struct> school1;
//   std::vector<test_struct> std1;
//   school1.push_back(a);
//   school1.push_back(b);
//   school1.push_back(c);
//   std1.push_back(a);
//   std1.push_back(b);
//   std1.push_back(c);
//   try {
//     school1.reserve(100);
//     std1.reserve(100);
//   } catch (...) {
//     for (size_t i = 0; i < school1.size(); ++i) {
//       ASSERT_EQ(school1[i], std1[i]);
//     }
//   }
// }

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
  // s21::vector<test_struct> school3, school4, school5;
  // test_struct a, b, c, d, e, f;
  // school3.push_back(a);
  // school3.push_back(b);
  // school3.push_back(c);
  // school4.push_back(d);
  // school4.push_back(e);
  // school4.push_back(f);
  // school5 = school4;
  // school3 = school4;
  // for (size_t i = 0; i < school3.size(); ++i) {
  //   ASSERT_EQ(school3[i], school5[i]);
  // }
}

// TEST(VectorAt1, True) {
//   test_struct a, b, c, d, e, f;
//   s21::vector<test_struct> school1{a, b, c, d, e, f};
//   std::vector<test_struct> std1{a, b, c, d, e, f};
//   for (size_t i = 0; i < school1.size(); ++i) {
//     ASSERT_EQ(school1.at(i), std1.at(i));
//   }
// }

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

TEST(VectorIterator1, True)
{
  s21::vector<int> school1{5, 3, 2, 4, 8, 7, 9, 1};
  std::vector<int> std1{5, 3, 2, 4, 8, 7, 9, 1};
  std::sort(school1.begin(), school1.end());
  std::sort(std1.begin(), std1.end());
  for (size_t i = 0; i < school1.size(); ++i)
  {
    ASSERT_EQ(school1[i], std1[i]);
  }
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

TEST(VectorReserve1, False) {
  s21::vector<test_struct> school1;
  school1.reserve(100);
  ASSERT_EQ(school1.capacity(), static_cast<size_t>(100));
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