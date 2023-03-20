#include "gtest.h"
#include "USMap.h"

TEST(TUSMap, can_create_map)
{
  try
  {
    TUSMap<char, int> mp(4);
  }
  catch (const char* c)
  {
    ADD_FAILURE();
  }
}
