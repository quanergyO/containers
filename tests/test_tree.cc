
#include "../src/adt/tree.h"

TEST(Tree, True) {
  s21::Tree<int, int> a;
  ASSERT_EQ(a.empty(), true);
  a.insert(7);
  a.insert(11);
  a.insert(3);
  a.insert(15);
  a.insert(13);
  a.insert(-7);
  a.insert(1);
  auto it = a.begin();
  ASSERT_EQ(*it, -7);
  ASSERT_EQ(static_cast<int>(a.size()), 7);  // Размер дерева должен быть 7
  ASSERT_TRUE(a.contains(7));  // Ключ 7 должен быть в дереве
  ASSERT_TRUE(a.contains(3));  // Ключ 3 должен быть в дереве
  ASSERT_TRUE(a.contains(13));  // Ключ 13 должен быть в дереве
  ASSERT_FALSE(a.contains(5));  // Ключ 5 не должен быть в дереве
  ASSERT_FALSE(a.contains(0));  // Ключ 0 не должен быть в дереве

  s21::Tree<int, int> b;
  b.insert(55);
  b.insert(23);
  b.insert(33);
  auto it1 = b.begin();
  ASSERT_EQ(*it1, 23);

  a.merge(b);

  auto it3 = a.begin();
  ASSERT_EQ(*it3, -7);

  s21::Tree<int, int> c;
  c.insert(55);
  c.insert(23);
  c.insert(33);
  c.insert(77);
  c.insert(88);

  a.swap(c);
  auto it2 = a.begin();
  ASSERT_EQ(*it2, 23);
}
