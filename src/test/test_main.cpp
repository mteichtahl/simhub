#include <gtest/gtest.h>
 
TEST(SquareRootTest, PositiveNos) 
{ 
}
 
TEST (SquareRootTest, ZeroAndNegativeNos) 
{ 
}
 
int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
