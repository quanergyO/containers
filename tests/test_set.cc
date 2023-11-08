#include <set>
#include <vector>

#include "../src/set/set.h"

template <typename T>
void check_equals(const s21::set<T> &lhs, const std::set<T> &rhs) {
  ASSERT_EQ(lhs.size(), rhs.size());
  auto stdIterator = rhs.begin();
  auto schoolIterator = lhs.begin();
  while (schoolIterator != lhs.end()) {
    ASSERT_EQ(*schoolIterator, *stdIterator);
    ++schoolIterator;
    ++stdIterator;
  }
}

TEST(Set, DefaultConstructor) {
  s21::set<int> school1;
  std::set<int> std1;
  ASSERT_EQ(school1.size(), std1.size());
}

TEST(Set, Insert) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  check_equals(school1, std1);
}

TEST(Set, Erase) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }

  school1.erase(11);
  std1.erase(11);
  check_equals(school1, std1);

  school1.erase(5);
  std1.erase(5);
  check_equals(school1, std1);

  school1.erase(7);
  std1.erase(7);
  check_equals(school1, std1);
}

TEST(Set, EraseEmptySet) {
  s21::set<int> school1;
  std::set<int> std1;
  std1.erase(1);
  school1.erase(1);
  ASSERT_EQ(school1.size(), std1.size());
}

TEST(Set, CopyConstructor) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }

  s21::set<int> school2 = school1;
  std::set<int> std2 = std1;
  check_equals(school2, std2);
}

TEST(Set, InitListConstructor) {
  s21::set<int> school1{7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  std::set<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
  }

  check_equals(school1, std1);
}

TEST(Set, MoveConstructor) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  s21::set<int> school2 = std::move(school1);
  std::set<int> std2 = std::move(std1);
  check_equals(school2, std2);
}

TEST(Set, EraseItreator) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  auto schoolIterator = school1.begin();
  auto stdIterator = std1.begin();
  for (int i = 0; i < 3; ++i) {
    ++schoolIterator;
    ++stdIterator;
  }
  school1.erase(schoolIterator);
  std1.erase(stdIterator);
  check_equals(school1, std1);
}

TEST(Set, DeleteOneLeaf) {
  s21::set<int> school1 = {7};
  school1.erase(7);
  ASSERT_EQ(school1.size(), static_cast<size_t>(0));
}

TEST(Set, DeleteLeaf) {
  s21::set<int> school1{5, 3, 1};
  school1.erase(1);
  ASSERT_EQ(school1.size(), static_cast<size_t>(2));
}

TEST(Set, Empty) {
  s21::set<int> school1;
  ASSERT_EQ(school1.empty(), true);
  school1.insert(10);
  ASSERT_EQ(school1.empty(), false);
  school1.erase(10);
  ASSERT_EQ(school1.empty(), true);
}

TEST(Set, Clear) {
  s21::set<int> school1{7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  school1.clear();
  ASSERT_EQ(school1.size(), static_cast<size_t>(0));
}

TEST(Set, MaxSize) {
  s21::set<int> school1;
  ASSERT_EQ(school1.max_size(),
            std::numeric_limits<size_t>::max() / sizeof(int));
}

TEST(Set, Swap) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  s21::set<int> school2;
  std::set<int> std2;
  school1.swap(school2);
  std1.swap(std2);
  check_equals(school2, std2);
}

TEST(Set, FindTrue) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }

  auto schoolFind = school1.find(25);
  auto stdFind = std1.find(25);
  ASSERT_EQ(*schoolFind, *stdFind);
}

TEST(Set, FindFalse) {
  s21::set<int> school1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    school1.insert(num);
  }
  auto schoolFind = school1.find(100);
  ASSERT_EQ(schoolFind, school1.end());
}

TEST(Set, Contains) {
  s21::set<int> school1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    school1.insert(num);
  }
  bool isInSet = school1.contains(11);
  ASSERT_EQ(isInSet, true);
  isInSet = school1.contains(100);
  ASSERT_EQ(isInSet, false);
}

TEST(Set, OperatorEqualCopy) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  s21::set<int> school2;
  std::set<int> std2;
  school2 = school1;
  std2 = std1;
  check_equals(school2, std2);
  check_equals(school1, std1);
}

TEST(Set, OperatorEqualMove) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {7, 5, 3, 7, 11, 25, 1, -6, 11, 27, 33};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  s21::set<int> school2;
  std::set<int> std2;
  school2 = std::move(school1);
  std2 = std::move(std1);
  check_equals(school2, std2);
}

TEST(Set, DeleteNodeWitchTwoChildren) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {2, 3, 4, 5, 7, 8, 9};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }

  auto schoolFind = school1.find(5);
  auto stdFind = std1.find(5);
  ASSERT_EQ(*schoolFind, *stdFind);

  school1.erase(schoolFind);
  std1.erase(stdFind);
  check_equals(school1, std1);
}

TEST(Set, LeftRotate) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {100, 50, 25, 31, 150, 175, 180};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }

  school1.insert(20);
  std1.insert(20);
  check_equals(school1, std1);
}

TEST(Set, DeleteNodeWitchTwoChildren2) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {100, 50, 25, 31, 150, 175, 180, 179, 190, 176};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  auto it = school1.find(150);
  school1.erase(it);
  std1.erase(150);
  check_equals(school1, std1);
}

TEST(Set, DeleteNodeWitchTwoChildrenCaseNodeChildfree) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {10, 1, 70, 67, 80};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  auto it = school1.find(10);
  school1.erase(it);
  std1.erase(10);
  check_equals(school1, std1);
}

TEST(Set, DeleteNodeWitchTwoChildrenCaseNodeOneChildLeft) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {10, 1, 70, 67};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  auto it = school1.find(70);
  school1.erase(it);
  std1.erase(70);
  check_equals(school1, std1);
}

TEST(Set, DeleteNodeWitchTwoChildrenCaseNodeOneChildLRight) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {10, 1, 70, 80};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  auto it = school1.find(70);
  school1.erase(it);
  std1.erase(70);
  check_equals(school1, std1);
}

TEST(Set, DeleteNodeWitchTwoChildrenCaseLeaf) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {10, 1, 70, 67, 80};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  auto it = school1.find(80);
  school1.erase(it);
  std1.erase(80);
  check_equals(school1, std1);
}

TEST(Set, DeleteNodeRoot) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {10, 1, 70};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  auto it = school1.find(10);
  school1.erase(it);
  std1.erase(10);
  check_equals(school1, std1);
}

TEST(Set, LeftRightRotate) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {100, 101, 85, 80, 88};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  school1.insert(89);
  std1.insert(89);
  check_equals(school1, std1);
}

TEST(Set, NewLeftRightRotate) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {100, 30, 150, 176, 180, 190};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  school1.insert(89);
  std1.insert(89);
  check_equals(school1, std1);
}

TEST(Set, NewRightLeftRotate) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {100, 150, 30, 25, 35};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  school1.insert(20);
  std1.insert(20);
  auto it = school1.begin();
  it++;
  it--;
  check_equals(school1, std1);
}

TEST(Set, Merge) {
  s21::set<int> school1{1, 2, 3};
  std::set<int> std1{1, 2, 3};
  s21::set<int> school2{1, 20, 30};
  std::set<int> std2{1, 20, 30};
  school1.merge(school2);
  std1.merge(std2);
  check_equals(school1, std1);
  check_equals(school2, std2);
}

TEST(Set, CheckRbeginRendIterators) {
  s21::set<int> school1;
  std::set<int> std1;
  std::vector<int> vec = {100, 150, 30, 25, 35};
  for (const auto &num : vec) {
    std1.insert(num);
    school1.insert(num);
  }
  school1.insert(20);
  std1.insert(20);
  for (auto it = school1.rbegin(); it != school1.rend(); --it) {
    for (auto stdIterator = std1.rbegin(); stdIterator != std1.rend();
         ++stdIterator) {
      check_equals(school1, std1);
    }
  }
}
