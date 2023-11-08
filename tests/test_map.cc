#include <functional>
#include <map>

#include "../src/map/map.h"

template <typename Key, typename Value>
void check_equals(const s21::map<Key, Value> &lhs,
                  const std::map<Key, Value> &rhs) {
  ASSERT_EQ(lhs.size(), rhs.size());
  if (lhs.size() != 0) {
    auto stdIterator = rhs.begin();
    auto schoolIterator = lhs.begin();
    while (schoolIterator != lhs.end()) {
      ASSERT_EQ(schoolIterator->first, stdIterator->first);
      ASSERT_EQ(schoolIterator->second, stdIterator->second);
      ++schoolIterator;
      ++stdIterator;
    }
  }
}

TEST(Map, DefaultConstructor) {
  s21::map<int, char> school1;
  std::map<int, char> std1;
  check_equals(school1, std1);
}

TEST(Map, InitConstructor) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  check_equals(school1, std1);
}

TEST(Map, CopyConstructor) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> school2 = school1;
  std::map<int, char> std2 = std1;
  check_equals(school2, std2);
}

TEST(Map, CopyConstructor1) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> school2{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  school2 = school1;
  std::map<int, char> std2{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ;
  std2 = std1;
  check_equals(school2, std2);
}

TEST(Map, MoveConstructor) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> school2 = std::move(school1);
  std::map<int, char> std2 = std::move(std1);
  check_equals(school2, std2);
}

TEST(Map, OperatorCopyEqual) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> school2;
  std::map<int, char> std2;
  school2 = school1;
  std2 = std1;
  check_equals(school2, std2);
}

TEST(Map, OperatorMoveEqual) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> school2;
  std::map<int, char> std2;
  school2 = std::move(school1);
  std2 = std::move(std1);
  check_equals(school2, std2);
}

TEST(Map, At) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ASSERT_EQ(school1.at(2), std1.at(2));
  ASSERT_ANY_THROW(school1.at(5));
}

TEST(Map, OperatorBracket) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ASSERT_EQ(school1[2], std1[2]);
}

TEST(Map, Empty) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ASSERT_EQ(school1.empty(), std1.empty());
  s21::map<int, char> school2;
  std::map<int, char> std2;
  ASSERT_EQ(school2.empty(), std2.empty());
}

TEST(Map, Size) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ASSERT_EQ(school1.size(), std1.size());
  s21::map<int, char> school2;
  std::map<int, char> std2;
  ASSERT_EQ(school2.size(), std2.size());
}

TEST(Map, MaxSize) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ASSERT_EQ(school1.max_size(),
            std::numeric_limits<size_t>::max() / sizeof(std::pair<int, char>));
}

TEST(Map, Clear) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  school1.clear();
  std1.clear();
  check_equals(school1, std1);
}

TEST(Map, Insert1) {
  s21::map<int, char> school1;
  std::map<int, char> std1;
  school1.insert(std::make_pair(10, 'X'));
  std1.insert(std::make_pair(10, 'X'));
  check_equals(school1, std1);
}

TEST(Map, Insert2) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  school1.insert(10, 'X');
  std1.insert(std::make_pair(10, 'X'));
  check_equals(school1, std1);
}

// TEST(Map, InsertWithLeftRotate) {
//   s21::map<int, char> school1{
//       {8, 'a'}, {9, 'b'}, {11, 'c'}, {14, 'c'}, {17, 'c'}};
//   std::map<int, char> std1{{8, 'a'}, {9, 'b'}, {11, 'c'}, {14, 'c'}, {17,
//   'c'}}; school1.insert(10, 'X'); std1.insert(std::make_pair(10, 'X'));
//   check_equals(school1, std1);
// }

TEST(Map, InsertOrAssign) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  school1.insert_or_assign(5, 'X');
  std1.insert_or_assign(5, 'X');
  check_equals(school1, std1);
  school1.insert_or_assign(5, 'E');
  std1.insert_or_assign(5, 'E');
  check_equals(school1, std1);
}

TEST(Map, Erase) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  school1.erase(++(school1.begin()));
  std1.erase(++(std1.begin()));
  check_equals(school1, std1);
}

TEST(Map, Erase2) {
  s21::map<int, char> school1{{1, 'a'},  {2, 'b'},  {3, 'c'},
                              {10, 'a'}, {20, 'b'}, {30, 'c'},
                              {5, 'a'},  {7, 'b'},  {9, 'c'}};
  std::map<int, char> std1{{1, 'a'},  {2, 'b'}, {3, 'c'}, {10, 'a'}, {20, 'b'},
                           {30, 'c'}, {5, 'a'}, {7, 'b'}, {9, 'c'}};
  school1.erase(school1.begin());
  std1.erase(std1.begin());
  school1.erase(--school1.end());
  std1.erase(--std1.end());
  auto schoolIterator = school1.begin();
  auto stdIterator = std1.begin();
  ++schoolIterator;
  ++schoolIterator;
  ++stdIterator;
  ++stdIterator;
  std1.erase(stdIterator);
  school1.erase(schoolIterator);
  check_equals(school1, std1);
}

TEST(Map, Merge) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> school2{{1, 'a'}, {20, 'b'}, {30, 'c'}};
  std::map<int, char> std2{{1, 'a'}, {20, 'b'}, {30, 'c'}};
  school1.merge(school2);
  std1.merge(std2);
  check_equals(school1, std1);
  check_equals(school2, std2);
}

TEST(Map, Swap) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> school2{{1, 'a'}, {20, 'b'}, {30, 'c'}};
  std::map<int, char> std2{{1, 'a'}, {20, 'b'}, {30, 'c'}};
  school1.swap(school2);
  std1.swap(std2);
  check_equals(school1, std1);
  check_equals(school2, std2);
}

TEST(Map, InsertMany) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}, {20, 'b'}, {30, 'c'}};
  school1.insert_many(std::make_pair(1, 'a'), std::make_pair(20, 'b'),
                      std::make_pair(30, 'c'));
  check_equals(school1, std1);
}

TEST(Map, Contains) {
  s21::map<int, char> school1{{1, 'a'}, {2, 'b'}, {3, 'c'}};
  ASSERT_EQ(school1.contains(1), true);
  ASSERT_EQ(school1.contains(10), false);
}

TEST(Map, DeleteNodeWitchTwoChildren) {
  s21::map<int, char> school1{{100, 'a'}, {50, 'b'},  {25, 'c'},  {31, 'c'},
                              {150, 'c'}, {175, 'c'}, {180, 'c'}, {179, 'c'},
                              {190, 'c'}, {176, 'c'}};
  std::map<int, char> std1{{100, 'a'}, {50, 'b'},  {25, 'c'},  {31, 'c'},
                           {150, 'c'}, {175, 'c'}, {180, 'c'}, {179, 'c'},
                           {190, 'c'}, {176, 'c'}};
  auto it = school1.find(150);
  school1.erase(it);
  std1.erase(150);
  check_equals(school1, std1);
}

TEST(Map, DeleteNodeWitchTwoChildrenCaseNodeChildfree) {
  s21::map<int, char> school1{
      {10, 'a'}, {1, 'b'}, {70, 'c'}, {67, 'c'}, {80, 'c'}};
  std::map<int, char> std1{
      {10, 'a'}, {1, 'b'}, {70, 'c'}, {67, 'c'}, {80, 'c'}};
  auto it = school1.find(10);
  school1.erase(it);
  std1.erase(10);
  check_equals(school1, std1);
}

TEST(Map, DeleteNodeWitchTwoChildrenCaseNodeOneChildLeft) {
  s21::map<int, char> school1{{10, 'a'}, {1, 'b'}, {70, 'c'}, {67, 'c'}};
  std::map<int, char> std1{{10, 'a'}, {1, 'b'}, {70, 'c'}, {67, 'c'}};
  auto it = school1.find(70);
  school1.erase(it);
  std1.erase(70);
  check_equals(school1, std1);
}

TEST(Map, DeleteNodeWitchTwoChildrenCaseNodeOneChildLRight) {
  s21::map<int, char> school1{{10, 'a'}, {1, 'b'}, {70, 'c'}, {80, 'c'}};
  std::map<int, char> std1{{10, 'a'}, {1, 'b'}, {70, 'c'}, {80, 'c'}};
  auto it = school1.find(70);
  school1.erase(it);
  std1.erase(70);
  check_equals(school1, std1);
}

TEST(Map, DeleteNodeWitchTwoChildrenCaseLeaf) {
  s21::map<int, char> school1{
      {10, 'a'}, {1, 'b'}, {70, 'c'}, {67, 'c'}, {80, 'c'}};
  std::map<int, char> std1{
      {10, 'a'}, {1, 'b'}, {70, 'c'}, {67, 'c'}, {80, 'c'}};
  auto it = school1.find(80);
  school1.erase(it);
  std1.erase(80);
  check_equals(school1, std1);
}

TEST(Map, DeleteNodeRoot) {
  s21::map<int, char> school1{{10, 'a'}};
  std::map<int, char> std1{{10, 'a'}};
  auto it = school1.find(10);
  school1.erase(it);
  std1.erase(10);
  check_equals(school1, std1);
}

TEST(Map, NewRightLeftRotate) {
  s21::map<int, char> school1{
      {100, 'a'}, {150, 'b'}, {30, 'c'}, {25, 'c'}, {35, 'c'}};
  std::map<int, char> std1{
      {100, 'a'}, {150, 'b'}, {30, 'c'}, {25, 'c'}, {35, 'c'}};
  school1.insert(std::make_pair(36, 'X'));
  std1.insert(std::make_pair(36, 'X'));
  check_equals(school1, std1);
}

TEST(Map, NewRightLeftRotate1) {
  s21::map<int, char> school1{{100, 'a'}, {150, 'b'}, {30, 'c'}, {175, 'c'},
                              {176, 'c'}, {177, 'c'}, {178, 'c'}};
  std::map<int, char> std1{{100, 'a'}, {150, 'b'}, {30, 'c'}, {175, 'c'},
                           {176, 'c'}, {177, 'c'}, {178, 'c'}};
  school1.insert(std::make_pair(180, 'X'));
  std1.insert(std::make_pair(180, 'X'));
  check_equals(school1, std1);
}