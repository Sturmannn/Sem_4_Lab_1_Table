#include "gtest.h"
#include "USMap.h"
#include <string>

using std::string;

TEST(USMap, can_create_map)
{
  try
  {
    TUSMap<char, int> mp(5);
  }
  catch (const char* c)
  {
    ADD_FAILURE();
  }
}

TEST(USMap, can_create_map_with_negative_size)
{
  try
  {
    TUSMap<char, int> mp1(0);
  }
  catch (const char* ex)
  {
    EXPECT_TRUE(true);
  }

  try
  {
    TUSMap<char, int> mp2(-5);
  }
  catch (const char* ex)
  {
    EXPECT_TRUE(true);
  }
}

TEST(USMap, can_add_string_into_usmap)
{
  TUSMap<string, int> mp(5);
  string key = "Seven";
  int data = 7;
  EXPECT_NO_THROW(mp.Add(&key, &data));
}

TEST(USMap, can_delete_string_of_usmap)
{
  TUSMap<string, int> mp(5);
  string key = "Seven";
  int data = 7;
  mp.Add(&key, &data);
  EXPECT_NO_THROW(mp.Find(&key));
  try
  {
    mp.Delete(&key);
  }
  catch (const char* ex)
  {
    ADD_FAILURE();
  }
  EXPECT_ANY_THROW(mp.Find(&key));
}

TEST(USMap, can_find_id_of_key_if_key_exists)
{
  TUSMap<string, int> mp(5);
  string key = "Seven";
  int data = 7;
  mp.Add(&key, &data);
  EXPECT_NO_THROW(mp.Find(&key));
}

TEST(USMap, cant_find_id_of_key_if_key_doesnt_exist)
{
  TUSMap<string, int> mp(5);
  string key = "Seven";
  EXPECT_ANY_THROW(mp.Find(&key));
}

TEST(USMap, can_use_operator_indexing)
{
  TUSMap<string, int> mp(5);
  string key = "Seven";
  int data = 7;
  mp.Add(&key, &data);
  int index = *(mp[&key]);
  EXPECT_EQ(7, index);
}

TEST(USMap, can_find_data_using_key)
{
  TUSMap<string, int> mp(5);
  string key = "Seven";
  int data = 7;
  mp.Add(&key, &data);
  EXPECT_EQ(7, *(mp.Find(&key)));
}

TEST(USMap, can_check_if_map_is_full)
{
  TUSMap<string, int> mp(1);
  string key = "Seven";
  int data = 7;
  mp.Add(&key, &data);
  EXPECT_TRUE(mp.IsFull());
}

TEST(USMap, can_check_if_map_is_empty)
{
  TUSMap<string, int> mp(1);
  EXPECT_TRUE(mp.IsEmpty());
}