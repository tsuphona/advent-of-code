#include "day1.hpp"

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

static std::list<int> GetDigitsInString(std::string& line) {
  int nbr_characters = line.size();
  std::list<int> digits;

  // Check spelled out digits.
  std::list<std::string> lookup_table{"one",   "1", "two",   "2", "three", "3",
                                      "four",  "4", "five",  "5", "six",   "6",
                                      "seven", "7", "eight", "8", "nine",  "9"};

  std::map<std::string, int> str_to_int{
      {"one", 1},   {"1", 1}, {"two", 2},   {"2", 2}, {"three", 3}, {"3", 3},
      {"four", 4},  {"4", 4}, {"five", 5},  {"5", 5}, {"six", 6},   {"6", 6},
      {"seven", 7}, {"7", 7}, {"eight", 8}, {"8", 8}, {"nine", 9},  {"9", 9}};

  int nbr_table_elements = lookup_table.size();

  for (size_t i = 0; i < line.size(); i++) {
    for (std::string ref : lookup_table) {
      int l = ref.size();
      std::string sub_string = line.substr(i, l);

      if (sub_string == ref) {
        digits.push_back(str_to_int[ref]);
      }
    }
  }
  return digits;
}

int Day1(std::istream& stream) {
  // Read line by line.
  std::string line;
  int total_sum = 0;

  while (std::getline(stream, line)) {
    std::list<int> digits;
    digits = GetDigitsInString(line);
    int line_sum = 0;
    int nbr_elements = digits.size();
    line_sum = digits.front() * 10 + digits.back();

    total_sum += line_sum;
  }

  std::cout << "Sum: " << total_sum << std::endl;
  return total_sum;
}
