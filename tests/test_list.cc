#include <list>

#include "../src/list/list.h"

TEST(ListConstruct, True) {
  s21::list<int> school1;
  std::list<int> std1;
  ASSERT_EQ(school1.size(), std1.size());
  s21::list<int> school2(10);
  std::list<int> std2(10);
  ASSERT_EQ(school2.size(), std2.size());
  s21::list<int> school3{1, 2, 3, 4, 5};
  std::list<int> std3{1, 2, 3, 4, 5};
  auto stdIterator = std3.begin();
  auto s21Iterator = school3.begin();
  while (s21Iterator != school3.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }
  s21::list<int> school4 = school3;
  auto s21Iterator1 = school3.begin();
  auto s21Iterator2 = school4.begin();
  while (s21Iterator1 != school3.end()) {
    ASSERT_EQ(*s21Iterator1, *s21Iterator2);
    ++s21Iterator1;
    ++s21Iterator2;
  }

  s21::list<int> school5 = std::move(school3);
  std::list<int> std5 = std::move(std3);
  auto s21Iterator5 = school5.begin();
  auto stdIterator5 = std5.begin();
  while (s21Iterator5 != school5.end()) {
    ASSERT_EQ(*s21Iterator5, *stdIterator5);
    ++s21Iterator5;
    ++stdIterator5;
  }
  ASSERT_EQ(school3.size(), std3.size());
}

TEST(ListOperatorCopy, True) {
  s21::list<int> school3{1, 2, 3, 4, 5};
  std::list<int> std3{1, 2, 3, 4, 5};
  s21::list<int> school1;
  std::list<int> std1;
  school1 = school3;
  std1 = std3;
  auto stdIterator = std1.begin();
  auto s21Iterator = school1.begin();
  while (s21Iterator != school1.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }
}

TEST(ListOperatorMoveCopy, True) {
  s21::list<int> school3{1, 2, 3, 4, 5};
  std::list<int> std3{1, 2, 3, 4, 5};
  s21::list<int> school1;
  std::list<int> std1;
  school1 = std::move(school3);
  std1 = std::move(std3);
  auto stdIterator = std1.begin();
  auto s21Iterator = school1.begin();
  while (s21Iterator != school1.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }
  ASSERT_EQ(school3.size(), std3.size());
}

TEST(ListPushBack, True) {
  s21::list<int> school1;
  std::list<int> std1;
  for (int i = 1; i < 10; ++i) {
    school1.push_back(i * i);
    std1.push_back(i * i);
  }
  auto stdIterator = std1.begin();
  auto s21Iterator = school1.begin();
  while (s21Iterator != school1.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }
}

TEST(ListInsert, True) {
  s21::list<int> school1{1, 2, 3, 4, 5};
  std::list<int> std1{1, 2, 3, 4, 5};

  auto stdIterator = std1.begin();
  auto s21Iterator = school1.begin();
  school1.insert(s21Iterator, 100);
  std1.insert(stdIterator, 100);
  while (s21Iterator != school1.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }

  s21::list<int> school2{1, 2, 3, 4, 5};
  std::list<int> std2{1, 2, 3, 4, 5};
  auto stdIterator2 = std2.begin();
  auto s21Iterator2 = school2.begin();
  for (size_t i = 0; i < 3; ++i) {
    ++stdIterator2;
    ++s21Iterator2;
  }
  school2.insert(s21Iterator2, 1111);
  std2.insert(stdIterator2, 1111);
  auto tempS21Iterator = school2.begin();
  auto tempStdIterator = std2.begin();
  while (tempS21Iterator != school2.end()) {
    ASSERT_EQ(*tempS21Iterator, *tempStdIterator);
    ++tempS21Iterator;
    ++tempStdIterator;
  }

  s21::list<int> school3;
  std::list<int> std3;
  school3.insert(school3.begin(), 100);
  std3.insert(std3.begin(), 100);
  ASSERT_EQ(*school3.begin(), *std3.begin());
}

TEST(ListErase, True) {
  s21::list<int> school1{1, 2, 3, 4, 5};
  std::list<int> std1{1, 2, 3, 4, 5};

  school1.erase(school1.begin());
  std1.erase(std1.begin());
  auto stdIterator = std1.begin();
  auto s21Iterator = school1.begin();
  while (s21Iterator != school1.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }

  s21::list<int> school2{1, 2, 3, 4, 5};
  std::list<int> std2{1, 2, 3, 4, 5};
  auto stdIterator2 = std2.begin();
  auto s21Iterator2 = school2.begin();
  for (size_t i = 0; i < 3; ++i) {
    ++stdIterator2;
    ++s21Iterator2;
  }
  school2.erase(s21Iterator2);
  std2.erase(stdIterator2);
  auto tempS21Iterator = school2.begin();
  auto tempStdIterator = std2.begin();
  while (tempS21Iterator != school2.end()) {
    ASSERT_EQ(*tempS21Iterator, *tempStdIterator);
    ++tempS21Iterator;
    ++tempStdIterator;
  }

  s21::list<int> school3{1};
  std::list<int> std3{1};
  school3.erase(school3.begin());
  std3.erase(std3.begin());
  ASSERT_EQ(school3.size(), std3.size());
}

TEST(ListPopBack, True) {
  s21::list<int> school1{1, 2, 3, 4, 5};
  std::list<int> std1{1, 2, 3, 4, 5};

  school1.pop_back();
  std1.pop_back();
  auto stdIterator = std1.begin();
  auto s21Iterator = school1.begin();
  while (s21Iterator != school1.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }

  s21::list<int> school2{1, 2, 3, 4, 5};
  std::list<int> std2{1, 2, 3, 4, 5};
  for (size_t i = 0; i < 3; ++i) {
    school2.pop_back();
    std2.pop_back();
  }
  auto tempS21Iterator = school2.begin();
  auto tempStdIterator = std2.begin();
  while (tempS21Iterator != school2.end()) {
    ASSERT_EQ(*tempS21Iterator, *tempStdIterator);
    ++tempS21Iterator;
    ++tempStdIterator;
  }
}

TEST(ListPopFront, True) {
  s21::list<int> school1{1, 2, 3, 4, 5};
  std::list<int> std1{1, 2, 3, 4, 5};

  school1.pop_front();
  std1.pop_front();
  auto stdIterator = std1.begin();
  auto s21Iterator = school1.begin();
  while (s21Iterator != school1.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }

  s21::list<int> school2{1, 2, 3, 4, 5};
  std::list<int> std2{1, 2, 3, 4, 5};
  for (size_t i = 0; i < 3; ++i) {
    school2.pop_front();
    std2.pop_front();
  }
  auto tempS21Iterator = school2.begin();
  auto tempStdIterator = std2.begin();
  while (tempS21Iterator != school2.end()) {
    ASSERT_EQ(*tempS21Iterator, *tempStdIterator);
    ++tempS21Iterator;
    ++tempStdIterator;
  }
}

TEST(ListPushFront, True) {
  s21::list<int> school1;
  std::list<int> std1;
  for (int i = 1; i < 10; ++i) {
    school1.push_front(i * i);
    std1.push_front(i * i);
  }
  auto stdIterator = std1.begin();
  auto s21Iterator = school1.begin();
  while (s21Iterator != school1.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }
}

TEST(ListMerge, True) {
  s21::list<int> school1{1, 2, 3, 4, 5};
  s21::list<int> school2{10, 20, 30, 40, 50};
  std::list<int> std1{1, 2, 3, 4, 5};
  std::list<int> std2{10, 20, 30, 40, 50};
  school1.merge(school2);
  std1.merge(std2);
  auto stdIterator = std1.begin();
  auto s21Iterator = school1.begin();
  while (s21Iterator != school1.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }

  s21::list<int> school3;
  s21::list<int> school4{10, 20, 30, 40, 50};
  std::list<int> std3;
  std::list<int> std4{10, 20, 30, 40, 50};
  school3.merge(school4);
  std3.merge(std4);
  stdIterator = std3.begin();
  s21Iterator = school3.begin();
  while (s21Iterator != school3.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }

  s21::list<int> school5{10, 20, 30, 40, 50};
  s21::list<int> school6;
  std::list<int> std5{10, 20, 30, 40, 50};
  std::list<int> std6;
  school5.merge(school6);
  std5.merge(std6);
  stdIterator = std5.begin();
  s21Iterator = school5.begin();
  while (s21Iterator != school5.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }

  s21::list<int> school7{1, 3, 5, 7, 9};
  s21::list<int> school8{2, 4, 6, 8, 10};
  std::list<int> std7{1, 3, 5, 7, 9};
  std::list<int> std8{2, 4, 6, 8, 10};
  school7.merge(school8);
  std7.merge(std8);
  stdIterator = std7.begin();
  s21Iterator = school7.begin();
  while (s21Iterator != school7.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }
}

TEST(ListSplice, True) {
  s21::list<int> school1{1, 2, 3, 4, 5};
  s21::list<int> school2{10, 20, 30, 40, 50};
  std::list<int> std1{1, 2, 3, 4, 5};
  std::list<int> std2{10, 20, 30, 40, 50};
  auto iterForInsertS21 = school1.cbegin();
  auto iterForInsertStd = std1.begin();
  ++iterForInsertS21;
  ++iterForInsertS21;
  ++iterForInsertStd;
  ++iterForInsertStd;
  school1.splice(iterForInsertS21, school2);
  std1.splice(iterForInsertStd, std2);
  auto stdIterator = std1.begin();
  auto s21Iterator = school1.begin();
  while (s21Iterator != school1.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }

  s21::list<int> school3{1};
  s21::list<int> school4{10, 20, 30, 40, 50};
  std::list<int> std3{1};
  std::list<int> std4{10, 20, 30, 40, 50};
  iterForInsertS21 = school3.cbegin();
  iterForInsertStd = std3.begin();
  school3.splice(iterForInsertS21, school4);
  std3.splice(iterForInsertStd, std4);
  stdIterator = std3.begin();
  s21Iterator = school3.begin();
  while (s21Iterator != school3.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }

  s21::list<int> school5{10, 20, 30, 40, 50};
  s21::list<int> school6;
  std::list<int> std5{10, 20, 30, 40, 50};
  std::list<int> std6;
  iterForInsertS21 = school3.cbegin();
  iterForInsertStd = std3.begin();
  school5.splice(iterForInsertS21, school6);
  std5.splice(iterForInsertStd, std6);
  stdIterator = std5.begin();
  s21Iterator = school5.begin();
  while (s21Iterator != school5.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }

  s21::list<int> school7{1, 3, 5, 7, 9};
  s21::list<int> school8{2, 4, 6, 8, 10};
  std::list<int> std7{1, 3, 5, 7, 9};
  std::list<int> std8{2, 4, 6, 8, 10};
  iterForInsertS21 = school7.cbegin();
  iterForInsertStd = std7.begin();
  ++iterForInsertS21;
  ++iterForInsertS21;
  ++iterForInsertStd;
  ++iterForInsertStd;
  school7.splice(iterForInsertS21, school8);
  std7.splice(iterForInsertStd, std8);
  stdIterator = std7.begin();
  s21Iterator = school7.begin();
  while (s21Iterator != school7.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }
}

TEST(ListUnique, True) {
  s21::list<int> school1{1, 3, 5, 7, 9, 1, 3, 5, 7, 9};
  std::list<int> std1{1, 3, 5, 7, 9, 1, 3, 5, 7, 9};
  school1.unique();
  std1.unique();
  EXPECT_EQ(school1.size(), std1.size());
  auto s21Iterator = school1.begin();
  auto stdIterator = std1.begin();
  while (s21Iterator != school1.end()) {
    EXPECT_EQ(*s21Iterator, *stdIterator);
    ++s21Iterator;
    ++stdIterator;
  }

  s21::list<int> school2{1, 1, 1, 2, 2, 2};
  std::list<int> std2{1, 1, 1, 2, 2, 2};
  school2.unique();
  std2.unique();
  EXPECT_EQ(school2.size(), std2.size());
  s21Iterator = school2.begin();
  stdIterator = std2.begin();
  while (s21Iterator != school2.end()) {
    EXPECT_EQ(*s21Iterator, *stdIterator);
    ++s21Iterator;
    ++stdIterator;
  }
}

TEST(ListMoveConstructor, MoveEmptyList) {
  s21::list<int> school1;
  s21::list<int> custom_list2(std::move(school1));

  EXPECT_EQ(school1.size(), static_cast<size_t>(0));
  EXPECT_EQ(custom_list2.size(), static_cast<size_t>(0));
}

TEST(ListMoveConstructor, MoveNonEmptyList) {
  s21::list<int> school1 = {1, 2, 3};
  s21::list<int> custom_list2(std::move(school1));
  std::list<int> std1 = {1, 2, 3};
  std::list<int> std2(std::move(std1));

  EXPECT_EQ(school1.size(), std1.size());
  auto stdIterator = std2.begin();
  auto s21Iterator = custom_list2.begin();
  while (s21Iterator != custom_list2.end()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++stdIterator;
    ++s21Iterator;
  }
}

TEST(S21ListReverse, Test1) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  s21::list<int> my_list2 = {5, 4, 3, 2, 1};
  my_list.reverse();
  auto s21Iterator1 = my_list.begin();
  auto s21Iterator2 = my_list2.begin();
  while (s21Iterator1 != my_list.end()) {
    ASSERT_EQ(*s21Iterator2, *s21Iterator1);
    ++s21Iterator1;
    ++s21Iterator2;
  }
}

TEST(S21ListReverse, Test3) {
  s21::list<int> my_list;
  my_list.reverse();
  ASSERT_TRUE(my_list.empty());
}

TEST(S21ListSort, Test1) {
  s21::list<int> my_list = {5, 2, 8, 1, 6};
  s21::list<int> my_list2 = {1, 2, 5, 6, 8};
  my_list.sort();
  auto s21Iterator1 = my_list.begin();
  auto s21Iterator2 = my_list2.begin();
  while (s21Iterator1 != my_list.end()) {
    ASSERT_EQ(*s21Iterator2, *s21Iterator1);
    ++s21Iterator1;
    ++s21Iterator2;
  }
}

TEST(S21ListMaxSize, Test1) {
  s21::list<int> my_list;
  size_t max_size = my_list.max_size();

  ASSERT_EQ(max_size, std::numeric_limits<size_t>::max() / sizeof(int));
}

TEST(List, InsertMany) {
  s21::list<int> school1{1, 2, 3, 4, 5};
  std::list<int> std1{1, 2, 3, 4, 5};
  auto s21Iterator1 = school1.begin();
  auto stdIterator1 = std1.begin();
  ++s21Iterator1;
  ++s21Iterator1;
  ++stdIterator1;
  ++stdIterator1;
  school1.insert_many(s21Iterator1, 10, 20, 30);
  std1.insert(stdIterator1, {10, 20, 30});
  s21Iterator1 = school1.begin();
  stdIterator1 = std1.begin();
  while (s21Iterator1 != school1.end()) {
    ASSERT_EQ(*s21Iterator1, *stdIterator1);
    ++s21Iterator1;
    ++stdIterator1;
  }
}

TEST(List, InsertManyBack) {
  s21::list<int> school1{1, 2, 3, 4, 5};
  std::list<int> std1{1, 2, 3, 4, 5};
  school1.insert_many_back(10, 20, 30);
  std1.insert(std1.end(), {10, 20, 30});
  auto s21Iterator1 = school1.begin();
  auto stdIterator1 = std1.begin();
  while (s21Iterator1 != school1.end()) {
    ASSERT_EQ(*s21Iterator1, *stdIterator1);
    ++s21Iterator1;
    ++stdIterator1;
  }
}

TEST(List, InsertManyFront) {
  s21::list<int> school1{1, 2, 3, 4, 5};
  std::list<int> std1{1, 2, 3, 4, 5};
  school1.insert_many_front(10, 20, 30);
  std1.insert(std1.begin(), {10, 20, 30});
  auto s21Iterator1 = school1.begin();
  auto stdIterator1 = std1.begin();
  while (s21Iterator1 != school1.end()) {
    ASSERT_EQ(*s21Iterator1, *stdIterator1);
    ++s21Iterator1;
    ++stdIterator1;
  }
}

// TEST(List, OperatorEqualWithThis)
// {
//   s21::list<int> school1{1, 2, 3};
//   s21::list<int> result1 = school1;
//   school1 = school1;
//   auto s21Iterator1 = school1.begin();
//   auto s21Iterator2 = result1.begin();
//   while (s21Iterator1 != school1.end())
//   {
//     ASSERT_EQ(*s21Iterator1, *s21Iterator2);
//     ++s21Iterator1;
//     ++s21Iterator2;
//   }
// }

TEST(List, FrontInEmptyList) {
  s21::list<int> school1;
  ASSERT_ANY_THROW(school1.front());
}

TEST(List, BackInEmptyList) {
  s21::list<int> school1;
  ASSERT_ANY_THROW(school1.back());
}

TEST(List, UniqueWithOneSize) {
  s21::list<int> school1{1};
  s21::list<int> result{1};
  school1.unique();
  auto s21Iterator1 = school1.begin();
  auto resultIterator = result.begin();
  while (s21Iterator1 != school1.end()) {
    ASSERT_EQ(*s21Iterator1, *resultIterator);
    ++s21Iterator1;
    ++resultIterator;
  }
}

TEST(List, ReverseIterator) {
  s21::list<int> school1{1, 2, 3, 4, 5};
  std::list<int> std1{1, 2, 3, 4, 5};
  auto s21Iterator1 = school1.rbegin();
  auto stdIterator1 = std1.rbegin();
  while (s21Iterator1 != school1.rend()) {
    ASSERT_EQ(*s21Iterator1, *stdIterator1);
    ++s21Iterator1;
    ++stdIterator1;
  }
}

TEST(List, ConstIterator) {
  s21::list<int> school1{1, 2, 3, 4, 5};
  std::list<int> std1{1, 2, 3, 4, 5};
  auto stdIterator = std1.cbegin();
  auto s21Iterator = school1.cbegin();
  while (s21Iterator != school1.cend()) {
    ASSERT_EQ(*stdIterator, *s21Iterator);
    ++s21Iterator;
    ++stdIterator;
  }
}

TEST(List, ConstReverseIterator) {
  const s21::list<int> school1{1, 2, 3, 4, 5};
  const std::list<int> std1{1, 2, 3, 4, 5};
  auto stdIterator = std1.rbegin();
  auto s21Iterator = school1.rbegin();
  auto s21End = school1.rend();
  while (s21Iterator != s21End) {
    ASSERT_EQ(*s21Iterator, *stdIterator);
    ++s21Iterator;
    ++stdIterator;
  }
}