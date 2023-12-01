#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include "day1.hpp"

TEST(Day1Test, BasicAssertions) {
  std::string str = "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet\n";
  std::istringstream iss(str);

  int sum = Day1(iss);

  EXPECT_EQ(sum, 142);
}
