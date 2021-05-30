#include <gtest.h>

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "RUS");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
