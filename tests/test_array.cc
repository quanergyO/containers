#include <array>

#include "../array/array.h"

TEST(ArrayConstructors, True) {
  s21::array<int, 3> school1{1, 2, 3};
  std::array<int, 3> std1{1, 2, 3};
  ASSERT_EQ(school1[0], 1);
  ASSERT_EQ(school1[1], 2);
  ASSERT_EQ(school1[2], 3);
  ASSERT_EQ(school1.size(), std1.size());

  s21::array<int, 10> school2;
  std::array<int, 10> std2;
  ASSERT_EQ(school2.size(), std2.size());
  ASSERT_EQ(school2.max_size(), std2.max_size());

  s21::array<int, 3> school3 = {5, 6, 7};
  std::array<int, 3> std3 = {5, 6, 7};
  auto school4 = school3;
  auto std4 = std3;
  ASSERT_EQ(school4[0], 5);
  ASSERT_EQ(school3.size(), std3.size());
  ASSERT_EQ(school4.size(), std4.size());

  s21::array<int, 3> school5 = {1, 2, 3};
  std::array<int, 3> std5 = {1, 2, 3};
  auto school6 = school5;
  auto std6 = std5;
  auto it3 = school5.begin();
  for (auto it4 = std6.begin(); it4 != std6.end(); ++it3, ++it4)
    ASSERT_EQ(*it3, *it4);
  ASSERT_EQ(school5.size(), std5.size());
  ASSERT_EQ(school6.size(), std6.size());
}

TEST(ArrayOperatorEquals, True) {
  s21::array<int, 5> school1{1, 2, 66, 73, 3};
  std::array<int, 5> std1{1, 2, 66, 73, 3};
  s21::array<int, 5> school2;
  std::array<int, 5> std2;
  school2 = school1;
  std2 = std1;
  for (size_t i = 0; i < school2.size(); ++i) {
    ASSERT_EQ(school2[i], std2[i]);
  }
}

TEST(ArraySwap, True) {
  s21::array<int, 5> school1{1, 2, 66, 73, 3};
  std::array<int, 5> std1{1, 2, 66, 73, 3};
  s21::array<int, 5> school2;
  std::array<int, 5> std2;
  school2.swap(school1);
  std2.swap(std1);
  for (size_t i = 0; i < school2.size(); ++i) {
    ASSERT_EQ(school2[i], std2[i]);
  }

  s21::array<int, 5> school3;
  std::array<int, 5> std3;
  school3.fill(5);
  std3.fill(5);
  for (size_t i = 0; i < school2.size(); ++i) {
    ASSERT_EQ(school2[i], std2[i]);
  }
}