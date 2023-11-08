#include <list>
#include <stack>

#include "../src/list/list.h"
#include "../src/stack/stack.h"

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

TEST(Stack, InsertMany) {
  s21::stack<int> school1;
  std::stack<int> std1;
  for (int i = 0; i < 10; ++i) {
    school1.push(i);
    std1.push(i);
  }
  std1.push(7);
  std1.push(7);
  std1.push(7);
  school1.insert_many_front(7, 7, 7);
  while (!school1.empty()) {
    ASSERT_EQ(school1.top(), std1.top());
    school1.pop();
    std1.pop();
  }
}

TEST(Stack, MoveConstructor) {
  s21::stack<int> school1;
  std::stack<int> std1;
  for (int i = 0; i < 10; ++i) {
    school1.push(i);
    std1.push(i);
  }
  s21::stack<int> school2 = std::move(school1);
  std::stack<int> std2 = std::move(std1);
  while (!school2.empty()) {
    ASSERT_EQ(school2.top(), std2.top());
    school2.pop();
    std2.pop();
  }
  ASSERT_EQ(school1.empty(), true);
}

TEST(Stack, OperatorMoveEqual) {
  s21::stack<int> school1;
  std::stack<int> std1;
  for (int i = 0; i < 10; ++i) {
    school1.push(i);
    std1.push(i);
  }
  s21::stack<int> school2;
  std::stack<int> std2;
  school2 = std::move(school1);
  std2 = std::move(std1);
  while (!school2.empty()) {
    ASSERT_EQ(school2.top(), std2.top());
    school2.pop();
    std2.pop();
  }
  ASSERT_EQ(school1.empty(), true);
}