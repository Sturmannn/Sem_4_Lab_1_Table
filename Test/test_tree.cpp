#include "gtest.h"
#include "Tree.h"

TEST(TTree, can_create_tree)
{
  try
  {
    TTree<char*, int> a();
  }
  catch (...)
  {
    FAIL();
  }
}

TEST(TTree, can_add_element)
{
  TTree<char*, int> a;
  char* c1 = "First";
  int b = 5;
  ASSERT_NO_THROW(a.Add(&c1, &b));
}

TEST(TTree, can_copy_tree)
{
  TTree<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  try 
  {
    TTree<char*, int> v(a);
  }
  catch (...)
  {
    FAIL();
  }
}

TEST(TTree, can_find_element)
{
  TTree<char*, int> a;
  char* c1 = "First";
  int b = 5;
  a.Add(&c1, &b);
  EXPECT_EQ(b, a.Find(&c1));
}

TEST(TTree, cant_find_non_existen_element)
{
  TTree<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  ASSERT_ANY_THROW(a.Find(&c2));
}

TEST(TTree, can_delete_element_1)
{
  TTree<char*, int> a;
  char* c1 = "First";
  int b = 5;
  a.Add(&c1, &b);
  ASSERT_NO_THROW(a.Delete(&c1));
}

TEST(TTree, can_delete_element_2)
{
  TTree<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  ASSERT_NO_THROW(a.Delete(&c2));
}

TEST(TTree, can_add_tree_item)
{
  TTree<char*, int> a;
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

TEST(TTree, can_add_tree)
{
  TTree<char*, int> a;
  TTree<char*, int> d;
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