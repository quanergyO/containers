#include <set>

#include "../src/multiset/multiset.h"

template <typename T>
void check_equals(const s21::multiset<T> &lhs, const std::multiset<T> &rhs) {
  ASSERT_EQ(lhs.size(), rhs.size());
  auto stdIterator = rhs.cbegin();
  auto schoolIterator = lhs.cbegin();
  while (schoolIterator != lhs.cend()) {
    ASSERT_EQ(*schoolIterator, *stdIterator);
    ++schoolIterator;
    ++stdIterator;
  }
}

TEST(Multiset, DefaultConstructor) {
  s21::multiset<int> school1;
  ASSERT_TRUE(school1.empty());
}

TEST(Multiset, InitListConstructor) {
  s21::multiset<int> school1{7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  std::multiset<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
  }
  check_equals(school1, std1);
}

TEST(Multiset, CopyConstructor) {
  s21::multiset<int> school1{7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  std::multiset<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
  }

  s21::multiset<int> school2 = school1;
  std::multiset<int> std2 = std1;
  check_equals(school2, std2);
}

TEST(Multiset, MoveConstructor) {
  s21::multiset<int> school1{7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  std::multiset<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
  }

  s21::multiset<int> school2 = std::move(school1);
  std::multiset<int> std2 = std::move(std1);
  check_equals(school2, std2);
}

TEST(Multiset, OperatorEqualCopy) {
  s21::multiset<int> school1{7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  std::multiset<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
  }

  s21::multiset<int> school2;
  school2 = school1;
  std::multiset<int> std2;
  std2 = std1;
  check_equals(school2, std2);
}

TEST(Multiset, OperatorEqualMove) {
  s21::multiset<int> school1{7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  std::multiset<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
  }

  s21::multiset<int> school2;
  school2 = std::move(school1);
  std::multiset<int> std2;
  std2 = std::move(std1);
  check_equals(school2, std2);
}

TEST(Multiset, Empty) {
  s21::multiset<int> school1;
  ASSERT_TRUE(school1.empty());
  school1.insert(1);
  ASSERT_FALSE(school1.empty());
}

TEST(Multiset, Size) {
  s21::multiset<int> school1;
  ASSERT_EQ(school1.size(), static_cast<size_t>(0));
  school1.insert(1);
  ASSERT_EQ(school1.size(), static_cast<size_t>(1));
}

TEST(Multiset, MaxSize) {
  s21::multiset<int> school1;
  ASSERT_EQ(school1.max_size(),
            std::numeric_limits<size_t>::max() / sizeof(int));
}

TEST(Multiset, Clear) {
  s21::multiset<int> school1{7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  school1.clear();
  ASSERT_EQ(school1.size(), static_cast<size_t>(0));
}

TEST(Multiset, Insert) {
  s21::multiset<int> school1;
  std::multiset<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  check_equals(school1, std1);
}

TEST(Multiset, Erase) {
  s21::multiset<int> school1;
  std::multiset<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }

  school1.erase(school1.begin());
  std1.erase(std1.begin());
  check_equals(school1, std1);

  school1.erase(++school1.begin());
  std1.erase(++std1.begin());
  check_equals(school1, std1);

  school1.erase(++school1.begin());
  std1.erase(++std1.begin());
  check_equals(school1, std1);
}

TEST(Multiset, Swap) {
  s21::multiset<int> school1;
  std::multiset<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  s21::multiset<int> school2;
  std::multiset<int> std2;
  school1.swap(school2);
  std1.swap(std2);
  check_equals(school2, std2);
}

TEST(Multiset, Merge) {
  s21::multiset<int> school1{1, 2, 3};
  std::multiset<int> std1{1, 2, 3};
  s21::multiset<int> school2{1, 20, 30};
  std::multiset<int> std2{1, 20, 30};
  school1.merge(school2);
  std1.merge(std2);
  check_equals(school1, std1);
}

TEST(Multiset, Count) {
  s21::multiset<int> school1{7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  ASSERT_EQ(school1.count(7), static_cast<size_t>(2));
  ASSERT_EQ(school1.count(700), static_cast<size_t>(0));
}

TEST(Multiset, Find) {
  s21::multiset<int> school1;
  std::multiset<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  school1.find(3);
  std1.find(3);
  check_equals(school1, std1);
}

TEST(Multiset, ContainsEqualRange) {
  s21::multiset<int> school1;
  std::multiset<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  school1.equal_range(7);
  std1.equal_range(7);
  school1.lower_bound(7);
  std1.lower_bound(7);
  school1.upper_bound(7);
  std1.upper_bound(7);
  check_equals(school1, std1);
}

TEST(Multiset, Contains) {
  s21::multiset<int> school1{7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  ASSERT_TRUE(school1.contains(7));
  ASSERT_FALSE(school1.contains(77777));
}

TEST(Multiset, Find2) {
  s21::multiset<int> school1{7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  ASSERT_EQ(*school1.begin(), *school1.find(-6));
  // ASSERT_EQ(school1.end(), school1.find(9999));
}