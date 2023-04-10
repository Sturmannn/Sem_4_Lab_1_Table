#include "gtest.h"
#include "SMap.h"
#include <string>

using std::string;

TEST(SMap, can_create_map)
{
  try
  {
    TSMap<char, int> mp(5);
  }
  catch (const char* c)
  {
    ADD_FAILURE();
  }
}

TEST(SMap, can_create_map_with_negative_size)
{
  try
  {
    TSMap<char, int> mp1(0);
  }
  catch (const char* ex)
  {
    EXPECT_TRUE(true);
  }

  try
  {
    TSMap<char, int> mp2(-5);
  }
  catch (const char* ex)
  {
    EXPECT_TRUE(true);
  }
}

TEST(SMap, can_add_string_into_smap)
{
  TSMap<string, int> mp(5);
  string key = "Seven";
  int data = 7;
  EXPECT_NO_THROW(mp.Add(&key, &data));
}

TEST(SMap, can_delete_string_of_smap)
{
  TSMap<string, int> mp(5);
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

TEST(SMap, can_find_id_of_key_if_key_exists)
{
  TSMap<string, int> mp(5);
  string key = "Seven";
  int data = 7;
  mp.Add(&key, &data);
  EXPECT_NO_THROW(mp.Find(&key));
}

TEST(SMap, cant_find_id_of_key_if_key_doesnt_exist)
{
  TSMap<string, int> mp(5);
  string key = "Seven";
  EXPECT_ANY_THROW(mp.Find(&key));
}

TEST(SMap, can_use_operator_indexing)
{
  TSMap<string, int> mp(5);
  string key = "Seven";
  int data = 7;
  mp.Add(&key, &data);
  int index = *(mp[&key]);
  EXPECT_EQ(7, index);
}

TEST(SMap, can_find_data_using_key)
{
  TSMap<string, int> mp(5);
  string key = "Seven";
  int data = 7;
  mp.Add(&key, &data);
  EXPECT_EQ(7, *(mp.Find(&key)));
}

TEST(SMap, can_check_if_map_is_full)
{
  TSMap<string, int> mp(1);
  string key = "Seven";
  int data = 7;
  mp.Add(&key, &data);
  EXPECT_TRUE(mp.IsFull());
}

TEST(SMap, can_check_if_map_is_empty)
{
  TSMap<string, int> mp(1);
  EXPECT_TRUE(mp.IsEmpty());
}