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

