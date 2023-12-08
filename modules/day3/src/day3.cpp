#include <iostream>
#include <vector>

static bool IsDigit(const char& c) {
  bool is_digit = false;
  if (static_cast<int>(c) > 47 && static_cast<int>(c) < 58) {
    is_digit = true;
  }
  return is_digit;
}

static bool IsSpecialCharacter(const char& c) {
  bool is_special_character = false;
  if ((static_cast<int>(c) >= 32 && static_cast<int>(c) <= 47) &&
          (static_cast<int>(c) != 46) ||
      (static_cast<int>(c) >= 58 && static_cast<int>(c) <= 64) ||
      (static_cast<int>(c) >= 91 && static_cast<int>(c) <= 96) ||
      (static_cast<int>(c) >= 123 && static_cast<int>(c) <= 127)) {
    is_special_character = true;
  }
  return is_special_character;
}

static void FillVectors(std::vector<int>& row_index,
                        std::vector<int>& col_index,
                        std::vector<int>& first_adjacent_number,
                        std::vector<int>& second_adjacent_number, int row,
                        int col, char c, int num) {
  if (c == '*') {
    bool found_match = false;
    int found_index;

    if (row_index.empty()) {
      row_index.push_back(row);
      col_index.push_back(col);
      first_adjacent_number.push_back(num);
      second_adjacent_number.push_back(0);

    } else {
      for (size_t i = 0; i < row_index.size(); i++) {
        if (row_index[i] == row && col_index[i] == col) {
          found_match = true;
          found_index = i;
          break;
        }
      }

      if (!found_match) {
        row_index.push_back(row);
        col_index.push_back(col);
        first_adjacent_number.push_back(num);
        second_adjacent_number.push_back(0);
      } else {
        second_adjacent_number[found_index] = num;
      }
    }
  }
}

int SumLine(std::string& current_line, std::string& neighbor_line,
            std::vector<int>& row_index, std::vector<int>& col_index,
            std::vector<int>& first_adjacent_number,
            std::vector<int>& second_adjacent_number, int line_number) {
  int k = (line_number == 0) ? 1 : line_number - 1;

  bool is_asterisk = false;

  bool left_is_special_character = false;
  bool right_is_special_character = false;
  bool up_down_is_special_character = false;
  bool diagonal_left_is_special_character = false;
  bool diagonal_right_is_special_character = false;

  char left_character = '\0';
  char right_character = '\0';
  char up_down_character = '\0';
  char diagonal_left_character = '\0';
  char diagonal_right_character = '\0';

  bool first_digit = false;
  bool second_digit = false;
  bool third_digit = false;
  std::string number = "";

  int sum = 0;
  std::vector<int> cols;
  int nbr_chars = current_line.size();

  for (size_t i = 0; i < nbr_chars; i++) {
    if (IsDigit(current_line[i]) && !first_digit && !second_digit &&
        !third_digit) {
      first_digit = true;
      number += current_line[i];
      cols.push_back(i);

      if (i != nbr_chars - 1) {
        continue;
      }
    } else if (IsDigit(current_line[i]) && first_digit && !second_digit &&
               !third_digit) {
      second_digit = true;
      number += current_line[i];
      cols.push_back(i);

      if (i != nbr_chars - 1) {
        continue;
      }
    } else if (IsDigit(current_line[i]) && first_digit && second_digit &&
               !third_digit) {
      third_digit = true;
      number += current_line[i];
      cols.push_back(i);

      if (i != nbr_chars - 1) {
        continue;
      }
    }

    if ((!IsDigit(current_line[i]) || (i == nbr_chars - 1)) &&
        (first_digit || second_digit || third_digit)) {
      int num = std::stoi(number);

      int j = 0;
      // Check neighbors when a number has been found.
      while (j < cols.size()) {
        // Down or up.
        up_down_character = neighbor_line[cols[j]];
        up_down_is_special_character = IsSpecialCharacter(up_down_character);

        FillVectors(row_index, col_index, first_adjacent_number,
                    second_adjacent_number, k, cols[j], up_down_character, num);

        if (cols[j] == 0) {
          // Right.
          right_character = current_line[cols[j] + 1];
          right_is_special_character = IsSpecialCharacter(right_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number, cols[j] + 1,
                      right_character, num);

          // Diagonal-right.
          diagonal_right_character = neighbor_line[cols[j] + 1];
          diagonal_right_is_special_character =
              IsSpecialCharacter(diagonal_right_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, k, cols[j] + 1,
                      diagonal_right_character, num);

        } else if (cols[j] == (nbr_chars - 1)) {
          // Left.
          left_character = current_line[cols[j] - 1];
          left_is_special_character = IsSpecialCharacter(left_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number, cols[j] - 1,
                      left_character, num);

          // Diagonal-left.
          diagonal_left_character = neighbor_line[cols[j] - 1];
          diagonal_left_is_special_character =
              IsSpecialCharacter(diagonal_left_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, k, cols[j] - 1,
                      diagonal_left_character, num);

        } else {
          // Left.
          left_character = current_line[cols[j] - 1];
          left_is_special_character = IsSpecialCharacter(left_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number, cols[j] - 1,
                      left_character, num);

          // Right.
          right_character = current_line[cols[j] + 1];
          right_is_special_character = IsSpecialCharacter(right_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number, cols[j] + 1,
                      right_character, num);

          // Diagonal-left.
          diagonal_left_character = neighbor_line[cols[j] - 1];
          diagonal_left_is_special_character =
              IsSpecialCharacter(diagonal_left_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, k, cols[j] - 1,
                      diagonal_left_character, num);

          // Diagonal-right.
          diagonal_right_character = neighbor_line[cols[j] + 1];
          diagonal_right_is_special_character =
              IsSpecialCharacter(diagonal_right_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, k, cols[j] + 1,
                      diagonal_right_character, num);
        }

        if (left_is_special_character || right_is_special_character ||
            up_down_is_special_character ||
            diagonal_left_is_special_character ||
            diagonal_right_is_special_character) {
          sum += num;
          break;
        }
        j++;
      }

      // Reset everything.
      first_digit = false;
      second_digit = false;
      third_digit = false;
      number = "";
      cols.clear();

      left_is_special_character = false;
      right_is_special_character = false;
      up_down_is_special_character = false;
      diagonal_left_is_special_character = false;
      diagonal_right_is_special_character = false;

      left_character = '\0';
      right_character = '\0';
      up_down_character = '\0';
      diagonal_left_character = '\0';
      diagonal_right_character = '\0';
    }
  }

  return sum;
}

int SumLine(std::string& current_line, std::string& previous_line,
            std::string& next_line, std::vector<int>& row_index,
            std::vector<int>& col_index,
            std::vector<int>& first_adjacent_number,
            std::vector<int>& second_adjacent_number, int line_number) {
  bool left_is_special_character = false;
  bool right_is_special_character = false;
  bool up_is_special_character = false;
  bool down_is_special_character = false;
  bool up_left_is_special_character = false;
  bool up_right_is_special_character = false;
  bool down_left_is_special_character = false;
  bool down_right_is_special_character = false;

  char left_character = '\0';
  char right_character = '\0';
  char up_character = '\0';
  char down_character = '\0';
  char up_left_character = '\0';
  char up_right_character = '\0';
  char down_left_character = '\0';
  char down_right_character = '\0';

  bool first_digit = false;
  bool second_digit = false;
  bool third_digit = false;
  std::string number = "";

  int sum = 0;
  std::vector<int> cols;
  int nbr_chars = current_line.size();

  for (size_t i = 0; i < nbr_chars; i++) {
    if (IsDigit(current_line[i]) && !first_digit && !second_digit &&
        !third_digit) {
      first_digit = true;
      number += current_line[i];
      cols.push_back(i);
      if (i != nbr_chars - 1) {
        continue;
      }
    } else if (IsDigit(current_line[i]) && first_digit && !second_digit &&
               !third_digit) {
      second_digit = true;
      number += current_line[i];
      cols.push_back(i);
      if (i != nbr_chars - 1) {
        continue;
      }
    } else if (IsDigit(current_line[i]) && first_digit && second_digit &&
               !third_digit) {
      third_digit = true;
      number += current_line[i];
      cols.push_back(i);
      if (i != nbr_chars - 1) {
        continue;
      }
    }

    if ((!IsDigit(current_line[i]) || (i == nbr_chars - 1)) &&
        (first_digit || second_digit || third_digit)) {
      int num = std::stoi(number);
      int j = 0;
      // Check neighbors when a number has been found.
      while (j < cols.size()) {
        // Up.
        up_character = previous_line[cols[j]];
        up_is_special_character = IsSpecialCharacter(up_character);

        FillVectors(row_index, col_index, first_adjacent_number,
                    second_adjacent_number, line_number - 1, cols[j],
                    up_character, num);

        // Down.
        down_character = next_line[cols[j]];
        down_is_special_character = IsSpecialCharacter(down_character);

        FillVectors(row_index, col_index, first_adjacent_number,
                    second_adjacent_number, line_number + 1, cols[j],
                    down_character, num);

        if (cols[j] == 0) {
          // Right.
          right_character = current_line[cols[j] + 1];
          right_is_special_character = IsSpecialCharacter(right_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number, cols[j] + 1,
                      right_character, num);

          // Up-right.
          up_right_character = previous_line[cols[j] + 1];
          up_right_is_special_character =
              IsSpecialCharacter(up_right_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number - 1, cols[j] + 1,
                      up_right_character, num);

          // Down-right.
          down_right_character = next_line[cols[j] + 1];
          down_right_is_special_character =
              IsSpecialCharacter(down_right_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number + 1, cols[j] + 1,
                      down_right_character, num);

        } else if (cols[j] == (nbr_chars - 1)) {
          // Left.
          left_character = current_line[cols[j] - 1];
          left_is_special_character = IsSpecialCharacter(left_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number, cols[j] - 1,
                      left_character, num);

          // Up-left.
          up_left_character = previous_line[cols[j] - 1];
          up_left_is_special_character = IsSpecialCharacter(up_left_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number - 1, cols[j] - 1,
                      up_left_character, num);

          // Down-left.
          down_left_character = next_line[cols[j] - 1];
          down_left_is_special_character =
              IsSpecialCharacter(down_left_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number + 1, cols[j] - 1,
                      down_left_character, num);

        } else {
          // Left.
          left_character = current_line[cols[j] - 1];
          left_is_special_character = IsSpecialCharacter(left_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number, cols[j] - 1,
                      left_character, num);

          // Right.
          right_character = current_line[cols[j] + 1];
          right_is_special_character = IsSpecialCharacter(right_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number, cols[j] + 1,
                      right_character, num);

          // Up-right.
          up_right_character = previous_line[cols[j] + 1];
          up_right_is_special_character =
              IsSpecialCharacter(up_right_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number - 1, cols[j] + 1,
                      up_right_character, num);

          // Down-right.
          down_right_character = next_line[cols[j] + 1];
          down_right_is_special_character =
              IsSpecialCharacter(down_right_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number + 1, cols[j] + 1,
                      down_right_character, num);

          // Up-left.
          up_left_character = previous_line[cols[j] - 1];
          up_left_is_special_character = IsSpecialCharacter(up_left_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number - 1, cols[j] - 1,
                      up_left_character, num);

          // Down-left.
          down_left_character = next_line[cols[j] - 1];
          down_left_is_special_character =
              IsSpecialCharacter(down_left_character);

          FillVectors(row_index, col_index, first_adjacent_number,
                      second_adjacent_number, line_number + 1, cols[j] - 1,
                      down_left_character, num);
        }

        if (left_is_special_character || right_is_special_character ||
            up_is_special_character || down_is_special_character ||
            up_left_is_special_character || down_left_is_special_character ||
            up_right_is_special_character || down_right_is_special_character) {
          sum += num;
          break;
        }
        j++;
      }

      // Reset everything.
      first_digit = false;
      second_digit = false;
      third_digit = false;
      number = "";
      cols.clear();

      left_is_special_character = false;
      right_is_special_character = false;
      up_is_special_character = false;
      down_is_special_character = false;
      up_left_is_special_character = false;
      up_right_is_special_character = false;
      down_left_is_special_character = false;
      down_right_is_special_character = false;

      left_character = '\0';
      right_character = '\0';
      up_character = '\0';
      down_character = '\0';
      up_left_character = '\0';
      down_left_character = '\0';
      up_right_character = '\0';
      down_right_character = '\0';
    }
  }

  return sum;
}

void Day3(std::istream& stream) {
  std::string current_line;
  std::string previous_line;
  std::string next_line;

  std::vector<int> row_index;
  std::vector<int> col_index;
  std::vector<int> first_adjacent_number;
  std::vector<int> second_adjacent_number;

  int part_one_sum = 0;
  int part_two_sum = 0;

  if (std::getline(stream, next_line)) {
    current_line = next_line;
  }

  int current_row_index = 0;
  while (std::getline(stream, next_line)) {
    // Do work.
    if (current_row_index == 0) {
      part_one_sum += SumLine(current_line, next_line, row_index, col_index,
                              first_adjacent_number, second_adjacent_number,
                              current_row_index);
    } else {
      part_one_sum += SumLine(current_line, previous_line, next_line, row_index,
                              col_index, first_adjacent_number,
                              second_adjacent_number, current_row_index);
    }

    // Update.
    previous_line = current_line;
    current_line = next_line;
    current_row_index++;
  }

  // Handle last line
  part_one_sum +=
      SumLine(current_line, previous_line, row_index, col_index,
              first_adjacent_number, second_adjacent_number, current_row_index);

  for (size_t i = 0; i < row_index.size(); i++) {
    part_two_sum += first_adjacent_number[i] * second_adjacent_number[i];
  }
  std::cout << "Part 1 sum: " << part_one_sum << std::endl;
  std::cout << "Part 2 sum: " << part_two_sum << std::endl;
}
