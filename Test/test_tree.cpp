#include "gtest.h"
#include "Tree.h"

TEST(TTreeMap, can_create_tree)
{
  try
  {
    TTreeMap<char*, int> a();
  }
  catch (...)
  {
    FAIL();
  }
}

TEST(TTreeMap, can_add_element)
{
  TTreeMap<char*, int> a;
  char* c1 = "First";
  int b = 5;
  ASSERT_NO_THROW(a.Add(&c1, &b));
}

TEST(TTreeMap, can_copy_tree)
{
  TTreeMap<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  try 
  {
    TTreeMap<char*, int> v(a);
  }
  catch (...)
  {
    FAIL();
  }
}

TEST(TTreeMap, can_find_element)
{
  TTreeMap<char*, int> a;
  char* c1 = "First";
  int b = 5;
  a.Add(&c1, &b);
  EXPECT_EQ(5, a.Find(&c1));
}

TEST(TTreeMap, cant_find_non_existen_element)
{
  TTreeMap<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  ASSERT_ANY_THROW(a.Find(&c2));
}

TEST(TTreeMap, can_delete_element_1)
{
  TTreeMap<char*, int> a;
  char* c1 = "First";
  int b = 5;
  a.Add(&c1, &b);
  ASSERT_NO_THROW(a.Delete(&c1));
}

TEST(TTreeMap, can_delete_element_2)
{
  TTreeMap<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  ASSERT_NO_THROW(a.Delete(&c2));
}

TEST(TTreeMap, can_delete_element_3)
{
  TTreeMap<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  char* c3 = "Third";
  char* c4 = "Ta";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  a.Add(&c3, &b);
  a.Add(&c4, &b);
  ASSERT_NO_THROW(a.Delete(&c2));
}

TEST(TTreeMap, can_add_tree_item)
{
  TTreeMap<char*, int> a;
  TTreeItem<char*, int> d;
  TTreeItem<char*, int> d1;
  char* c1 = "First";
  char* c2 = "Second";
  char* c3 = "Third";
  char* c4 = "Ta";
  int b = 5;
  d.SetKey(&c3);
  d.SetData(&b);
  d1.SetKey(&c4);
  d1.SetData(&b);
  d.SetRight(&d1);
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  ASSERT_NO_THROW(a.Add(&d));
}

TEST(TTreeMap, can_add_tree)
{
  TTreeMap<char*, int> a;
  TTreeMap<char*, int> d;
  char* c1 = "First";
  char* c2 = "Second";
  char* c3 = "Third";
  char* c4 = "Ta";
  int b = 5;
  d.Add(&c3, &b);
  d.Add(&c4, &b);
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  ASSERT_NO_THROW(a.Add(d));
}