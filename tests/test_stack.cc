#include <list>
#include <stack>

#include "../list/list.h"
#include "../stack/stack.h"

TEST(Stack, True) {
  s21::stack<int> a;
  s21::stack<int> aa;
  s21::stack<int> f{1, 2, 3, 4, 5, 6, 7};  // default stack cant do it
  s21::stack<int> ff{1, 2, 3, 4, 5, 6, 7};
  a.push(7);
  aa.push(7);
  ASSERT_EQ(a.top(), aa.top());
  a.push(22);
  aa.push(22);
  ASSERT_EQ(a.top(), aa.top());
  a.push(-7);
  aa.push(-7);
  ASSERT_EQ(a.top(), aa.top());
  a.pop();
  aa.pop();
  ASSERT_EQ(a.top(), aa.top());
  ASSERT_EQ(a.size(), aa.size());
  while (!a.empty()) {
    a.pop();
  }
  ASSERT_EQ(a.empty(), true);
  a = f;
  ASSERT_EQ(a.top(), f.top());
  aa.swap(f);
  ASSERT_EQ(aa.top(), ff.top());
}