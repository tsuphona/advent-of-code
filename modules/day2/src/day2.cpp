#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static int GameNumber(std::string& line) {
  std::string game_number_str = line.substr(5, line.find(':', 0) - 5);
  int game_number_int = std::stoi(game_number_str);
  return game_number_int;
}

static std::vector<std::vector<int>> SetsPerGame(std::string& line) {
  auto n = std::ranges::count(line, ';');
  int nbr_sets = n + 1;
  int nbr_colors;
  std::vector<std::vector<int>> vec;

  std::string s = line.substr(line.find(':', 0) + 2);
  int set_start = 0;

  for (size_t i = 0; i < nbr_sets; i++) {
    std::string set = s.substr(set_start, s.find(';', set_start) - set_start);
    auto m = std::ranges::count(set, ',');
    nbr_colors = m + 1;
    std::vector<int> row{0, 0, 0};
    int color_start = 0;
    for (size_t j = 0; j < nbr_colors; j++) {
      std::string color =
          set.substr(color_start, set.find(',', color_start) - color_start);

      std::string nbr_balls_str = color.substr(0, color.find(' ', 0));
      std::string c = color.substr(color.find(' ', 0) + 1);

      int nbr_balls_int = std::stoi(nbr_balls_str);

      if (c == "red") {
        row[0] = nbr_balls_int;
      } else if (c == "green") {
        row[1] = nbr_balls_int;
      } else if (c == "blue") {
        row[2] = nbr_balls_int;
      }

      color_start += color.size() + 2;
    }

    vec.push_back(row);
    set_start += set.size() + 2;
  }

  return vec;
}

void Day2(std::istream& stream) {
  // Read line by line.
  std::string line;
  int part_one_sum = 0;
  int part_two_sum = 0;

  while (std::getline(stream, line)) {
    int min_red = 1;
    int min_green = 1;
    int min_blue = 1;
    int factor;
    int game_number = GameNumber(line);

    bool is_valid_game = true;

    std::vector<int> ref{12, 13, 14};
    std::vector<std::vector<int>> vec = SetsPerGame(line);

    for (size_t set = 0; set < vec.size(); set++) {
      if (vec[set][0] > ref[0] || vec[set][1] > ref[1] ||
          vec[set][2] > ref[2]) {
        is_valid_game = false;
      }

      if (vec[set][0] > min_red) {
        min_red = vec[set][0];
      }
      if (vec[set][1] > min_green) {
        min_green = vec[set][1];
      }
      if (vec[set][2] > min_blue) {
        min_blue = vec[set][2];
      }
    }

    factor = min_red * min_green * min_blue;

    if (is_valid_game) {
      part_one_sum += game_number;
    }
    part_two_sum += factor;
  }
  std::cout << "Part 1 Sum: " << part_one_sum << std::endl;
  std::cout << "Part 2 Sum: " << part_two_sum << std::endl;
}
