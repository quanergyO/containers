#include <queue>

#include "../queue/queue.h"

TEST(Queque, True) {
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
  a = a;
  // a = std::move(a);
}