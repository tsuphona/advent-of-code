#include <cmath>
#include <deque>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

static int ExtractCardNumber(std::string& line) {
  int card_number_int;
  std::string card_number_str = line.substr(5, line.find(':', 5) - 5);
  card_number_int = std::stoi(card_number_str);
  return card_number_int;
}

static bool IsDigit(const char& c) {
  bool is_digit = false;
  if (static_cast<int>(c) > 47 && static_cast<int>(c) < 58) {
    is_digit = true;
  }
  return is_digit;
}

static std::vector<int> ExtractWinningNumbers(std::string& line) {
  std::vector<int> winning_numbers;
  bool first_digit = false;
  bool second_digit = false;
  std::string number = "";
  std::string winning_part;

  int colon_symbol_pos = line.find(':', 0);
  int pipe_symbol_pos = line.find('|', 0);
  winning_part = line.substr(colon_symbol_pos + 2,
                             pipe_symbol_pos - (colon_symbol_pos + 2) - 1);

  for (size_t i = 0; i < winning_part.size(); i++) {
    if (IsDigit(winning_part[i]) && !first_digit && !second_digit) {
      first_digit = true;
      number += winning_part[i];

      if (i != winning_part.size() - 1) {
        continue;
      }
    } else if (IsDigit(winning_part[i]) && first_digit && !second_digit) {
      second_digit = true;
      number += winning_part[i];

      if (i != winning_part.size() - 1) {
        continue;
      }
    }

    if ((!IsDigit(winning_part[i]) || (i == winning_part.size() - 1)) &&
        (first_digit || second_digit)) {
      int num = std::stoi(number);
      winning_numbers.push_back(num);

      // Reset everything.
      first_digit = false;
      second_digit = false;
      number = "";
    }
  }

  return winning_numbers;
}

static std::vector<int> ExtractPlayerNumbers(std::string& line) {
  std::vector<int> player_numbers;
  bool first_digit = false;
  bool second_digit = false;
  std::string number = "";
  std::string player_part;

  int pipe_symbol_pos = line.find('|', 0);
  player_part = line.substr(pipe_symbol_pos + 2);

  for (size_t i = 0; i < player_part.size(); i++) {
    if (IsDigit(player_part[i]) && !first_digit && !second_digit) {
      first_digit = true;
      number += player_part[i];

      if (i != player_part.size() - 1) {
        continue;
      }
    } else if (IsDigit(player_part[i]) && first_digit && !second_digit) {
      second_digit = true;
      number += player_part[i];

      if (i != player_part.size() - 1) {
        continue;
      }
    }

    if ((!IsDigit(player_part[i]) || (i == player_part.size() - 1)) &&
        (first_digit || second_digit)) {
      int num = std::stoi(number);
      player_numbers.push_back(num);

      // Reset everything.
      first_digit = false;
      second_digit = false;
      number = "";
    }
  }

  return player_numbers;
}

static int GetPoints(const std::vector<int>& winning_numbers,
                     const std::vector<int>& player_numbers) {
  int match = 0;

  for (size_t i = 0; i < winning_numbers.size(); i++) {
    for (size_t j = 0; j < player_numbers.size(); j++) {
      if (winning_numbers[i] == player_numbers[j]) {
        match++;
      }
    }
  }

  return std::pow(2, match - 1);
}

static int GetNumberMatches(const std::vector<int>& winning_numbers,
                            const std::vector<int>& player_numbers) {
  int match = 0;

  for (size_t i = 0; i < winning_numbers.size(); i++) {
    for (size_t j = 0; j < player_numbers.size(); j++) {
      if (winning_numbers[i] == player_numbers[j]) {
        match++;
      }
    }
  }

  return match;
}

static void ProcessCopies(std::vector<int>& copies, std::vector<int>& matches) {
  int card_number;
  int nbr_cards = copies.size();
  std::deque<int> card_list(nbr_cards);
  std::iota(std::begin(card_list), std::end(card_list), 1);

  while (!card_list.empty()) {
    card_number = card_list.front();
    int nbr_matches = matches[card_number - 1];
    std::deque<int> winning_copies(nbr_matches);
    std::iota(std::begin(winning_copies), std::end(winning_copies),
              card_number + 1);
    card_list.insert(std::end(card_list), std::begin(winning_copies),
                     std::end(winning_copies));
    copies[card_number - 1] += 1;
    card_list.pop_front();
  }
}

void Day4(std::istream& stream) {
  std::string line;
  int card_number;
  std::vector<int> winning_numbers;
  std::vector<int> player_numbers;
  int part_one_sum = 0;
  int part_two_sum = 0;
  std::vector<int> copies;
  std::vector<int> nbr_matches;

  size_t card = 0;

  while (std::getline(stream, line)) {
    card_number = ExtractCardNumber(line);
    winning_numbers = ExtractWinningNumbers(line);
    player_numbers = ExtractPlayerNumbers(line);
    part_one_sum += GetPoints(winning_numbers, player_numbers);

    copies.push_back(0);
    nbr_matches.push_back(GetNumberMatches(winning_numbers, player_numbers));
  }

  ProcessCopies(copies, nbr_matches);
  part_two_sum = std::reduce(copies.begin(), copies.end());

  std::cout << "Part one sum: " << part_one_sum << std::endl;
  std::cout << "Part two sum: " << part_two_sum << std::endl;
}
