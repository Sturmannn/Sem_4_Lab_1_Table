#include "gtest.h"
#include "Map.h"

TEST(TMap, can_create_map)
{
  try
  {
    TMap<char*, int> a(50);
  }
  catch (...)
  {
    FAIL();
  }
}

TEST(TMap, cant_create_map_with_negative_size)
{
  try
  {
    TMap<char*, int> a(-50);
  }
  catch(...)
  {
    SUCCEED();
  }
}

TEST(TMap, can_copy_map)
{
  TMap<char*, int> a(50);
  try 
  {
    TMap<char*, int> b(a);
  }
  catch (...)
  {
    FAIL();
  }
}

TEST(TMap, can_add_element)
{
  TMap<char*, int> a(50);
  char* c = "First";
  int b = 5;
  try
  {
    a.Add(&c, &b);
  }
  catch (...)
  {
    FAIL();
  }
}

TEST(TMap, can_find_elements)
{
  TMap<char*, int> a(50);
  char* c1 = "First";
  char* c2 = "Second";
  char* c3 = "Third";
  int b = 5, d = 6;
  a.Add(&c1, &b);
  a.Add(&c2, &d);
  a.Add(&c3, &b);
  try
  {
    a.Find(&c2);
  }
  catch(...)
  {
    FAIL();
  }
  EXPECT_EQ(a.Find(&c1), 5);
}

TEST(TMap, can_check_is_map_full)
{
  TMap<char*, int> a(2);
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  EXPECT_EQ(a.IsFull(), true);
}

TEST(TMap, can_check_is_map_empty)
{
  TMap<char*, int> a(2);
  EXPECT_EQ(a.IsEmpty(), true);
}

TEST(TMap, can_check_is_map_not_full)
{
  TMap<char*, int> a(3);
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  EXPECT_EQ(a.IsFull(), false);
}

TEST(TMap, can_check_is_map_not_empty)
{
  TMap<char*, int> a(2);
  char* c1 = "First";
  int b = 5;
  a.Add(&c1, &b);
  EXPECT_EQ(a.IsEmpty(), false);
}

TEST(TMap, can_delete_element)
{
  TMap<char*, int> a(3);
  char* c1 = "First";
  char* c2 = "Second";
  int b = 5;
  a.Add(&c1, &b);
  a.Add(&c2, &b);
  a.Delete(&c2);
  ASSERT_ANY_THROW(a.Find(&c2));
}