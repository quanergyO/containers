#include <queue>

#include "../src/queue/queue.h"

TEST(Queue, True) {
  s21::queue<int> a;
  std::queue<int> aa;
  a.push(7);
  aa.push(7);
  ASSERT_EQ(a.back(), aa.back());
  ASSERT_EQ(a.front(), aa.front());
  a.push(-7);
  aa.push(-7);
  ASSERT_EQ(a.back(), aa.back());
  ASSERT_EQ(a.front(), aa.front());
  a.push(77);
  aa.push(77);
  ASSERT_EQ(a.back(), aa.back());
  ASSERT_EQ(a.front(), aa.front());
  a.pop();
  aa.pop();
  ASSERT_EQ(a.back(), aa.back());
  ASSERT_EQ(a.front(), aa.front());
  s21::queue<int> b(a);
  std::queue<int> bb(aa);
  ASSERT_EQ(b.back(), bb.back());
  ASSERT_EQ(b.front(), bb.front());
  s21::queue<int> c(std::move(b));
  std::queue<int> cc(std::move(bb));
  ASSERT_EQ(c.back(), cc.back());
  ASSERT_EQ(c.front(), cc.front());
  ASSERT_EQ(c.size(), cc.size());
  ASSERT_EQ(c.empty(), cc.empty());
  s21::queue<int> f{1, 2, 3, 4, 5, 6, 7};
  a.swap(c);
  aa.swap(cc);
  ASSERT_EQ(c.front(), cc.front());
  // a = a;
  // a = std::move(a);
  a.insert_many_back(4, 5, 6);
  aa.push(4);
  aa.push(5);
  aa.push(6);
  ASSERT_EQ(a.front(), aa.front());
}

TEST(Queue, OperatorEqual) {
  s21::queue<int> school1;
  std::queue<int> std1;
  for (int i = 0; i < 10; ++i) {
    school1.push(i);
    std1.push(i);
  }
  s21::queue<int> school2;
  std::queue<int> std2;
  school2 = school1;
  std2 = std1;
  while (!school2.empty()) {
    ASSERT_EQ(school2.front(), std2.front());
    school2.pop();
    std2.pop();
  }
}

TEST(Queue, OperatorMoveEqual) {
  s21::queue<int> school1;
  std::queue<int> std1;
  for (int i = 0; i < 10; ++i) {
    school1.push(i);
    std1.push(i);
  }
  s21::queue<int> school2;
  std::queue<int> std2;
  school2 = std::move(school1);
  std2 = std::move(std1);
  while (!school2.empty()) {
    ASSERT_EQ(school2.front(), std2.front());
    school2.pop();
    std2.pop();
  }
}