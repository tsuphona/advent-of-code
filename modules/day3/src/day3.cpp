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

int SumLine(std::string& current_line, std::string& neighbor_line) {
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

        if (cols[j] == 0) {
          // Right.
          right_character = current_line[cols[j] + 1];
          right_is_special_character = IsSpecialCharacter(right_character);

          // Diagonal-right.
          diagonal_right_character = neighbor_line[cols[j] + 1];
          diagonal_right_is_special_character =
              IsSpecialCharacter(diagonal_right_character);

        } else if (cols[j] == (nbr_chars - 1)) {
          // Left.
          left_character = current_line[cols[j] - 1];
          left_is_special_character = IsSpecialCharacter(left_character);

          // Diagonal-left.
          diagonal_left_character = neighbor_line[cols[j] - 1];
          diagonal_left_is_special_character =
              IsSpecialCharacter(diagonal_left_character);

        } else {
          // Left.
          left_character = current_line[cols[j] - 1];
          left_is_special_character = IsSpecialCharacter(left_character);

          // Right.
          right_character = current_line[cols[j] + 1];
          right_is_special_character = IsSpecialCharacter(right_character);

          // Diagonal-left.
          diagonal_left_character = neighbor_line[cols[j] - 1];
          diagonal_left_is_special_character =
              IsSpecialCharacter(diagonal_left_character);

          // Diagonal-right.
          diagonal_right_character = neighbor_line[cols[j] + 1];
          diagonal_right_is_special_character =
              IsSpecialCharacter(diagonal_right_character);
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
            std::string& next_line) {
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

        // Down.
        down_character = next_line[cols[j]];
        down_is_special_character = IsSpecialCharacter(down_character);

        if (cols[j] == 0) {
          // Right.
          right_character = current_line[cols[j] + 1];
          right_is_special_character = IsSpecialCharacter(right_character);

          // Up-right.
          up_right_character = previous_line[cols[j] + 1];
          up_right_is_special_character =
              IsSpecialCharacter(up_right_character);

          // Down-right.
          down_right_character = next_line[cols[j] + 1];
          down_right_is_special_character =
              IsSpecialCharacter(down_right_character);

        } else if (cols[j] == (nbr_chars - 1)) {
          // Left.
          left_character = current_line[cols[j] - 1];
          left_is_special_character = IsSpecialCharacter(left_character);

          // Up-left.
          up_left_character = previous_line[cols[j] - 1];
          up_left_is_special_character = IsSpecialCharacter(up_left_character);

          // Down-left.
          down_left_character = next_line[cols[j] - 1];
          down_left_is_special_character =
              IsSpecialCharacter(down_left_character);

        } else {
          // Left.
          left_character = current_line[cols[j] - 1];
          left_is_special_character = IsSpecialCharacter(left_character);

          // Right.
          right_character = current_line[cols[j] + 1];
          right_is_special_character = IsSpecialCharacter(right_character);

          // Up-right.
          up_right_character = previous_line[cols[j] + 1];
          up_right_is_special_character =
              IsSpecialCharacter(up_right_character);

          // Down-right.
          down_right_character = next_line[cols[j] + 1];
          down_right_is_special_character =
              IsSpecialCharacter(down_right_character);

          // Up-left.
          up_left_character = previous_line[cols[j] - 1];
          up_left_is_special_character = IsSpecialCharacter(up_left_character);

          // Down-left.
          down_left_character = next_line[cols[j] - 1];
          down_left_is_special_character =
              IsSpecialCharacter(down_left_character);
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

  if (std::getline(stream, next_line)) {
    current_line = next_line;
  }

  int current_row_index = 0;
  while (std::getline(stream, next_line)) {
    // Do work.
    if (current_row_index == 0) {
      sum += SumLine(current_line, next_line);
    } else {
      sum += SumLine(current_line, previous_line, next_line);
    }

    // Update.
    previous_line = current_line;
    current_line = next_line;
    current_row_index++;
  }

  // Handle last line
  sum += SumLine(current_line, previous_line);

  std::cout << "Sum: " << sum << std::endl;
}
