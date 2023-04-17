#include "gtest.h"
#include "HMap.h"

TEST(THMAP, can_create_hmap)
{
  try
  {
    THMap<char*, int> a();
  }
  catch (...)
  {
    FAIL();
  }
}

TEST(THMAP, can_add_element)
{
  THMap<char*, int> a;
  char* c1 = "First";
  int b = 5;
  ASSERT_NO_THROW(a.Add(&c1, &b));
}

TEST(THMAP, can_copy_hmap)
{
  THMap<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  try
  {
    THMap<char*, int> v(a);
  }
  catch (...)
  {
    FAIL();
  }
}

TEST(THMAP, can_find_element)
{
  THMap<char*, int> a;
  char* c1 = "First";
  int b = 5;
  a.Add(&c1, &b);
  EXPECT_EQ(b, a.Find(&c1));
}

TEST(THMAP, cant_find_non_existen_element)
{
  THMap<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  ASSERT_ANY_THROW(a.Find(&c2));
}

TEST(THMAP, can_delete_element_1)
{
  THMap<char*, int> a;
  char* c1 = "First";
  int b = 5;
  a.Add(&c1, &b);
  ASSERT_NO_THROW(a.Delete(&c1));
}

TEST(THMAP, can_delete_element_2)
{
  THMap<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  ASSERT_NO_THROW(a.Delete(&c2));
}

TEST(THMAP, can_delete_element_3)
{
  THMap<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  char* c3 = "Third";
  int b = 5, c = 10;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  a.Add(&c3, &b);
  a.Add(&c3, &c);
  ASSERT_NO_THROW(a.Delete(&c3));
}

TEST(THMAP, can_delete_element_4)
{
  THMap<char*, int> a;
  char* c1 = "First";
  char* c2 = "Second";
  char* c3 = "Third";
  int b = 5, c = 10, d = 20;
  a.Add(&c1, &b);
  a.Add(&c3, &b);
  a.Add(&c3, &c);
  a.Add(&c3, &d);
  ASSERT_NO_THROW(a.Delete(&c3));
}