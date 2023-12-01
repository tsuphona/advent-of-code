#include "day1.hpp"

#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

static std::list<int> GetDigitsInString(const std::string& line) {
  int nbr_characters = line.size();
  std::list<int> digits;
  const char* chars = line.c_str();

  for (size_t i = 0; i < nbr_characters; i++) {
    int ch_ascii = static_cast<int>(chars[i]);
    if (ch_ascii > 47 && ch_ascii < 58) {
      int number = ch_ascii - 48;
      digits.push_back(number);
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
