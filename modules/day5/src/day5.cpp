#include <iostream>
#include <vector>

static std::vector<int> ExtractNumbersFromLine(std::string& in_line) {
  std::vector<int> out_vec;
  // Maybe make separator more generic.
  int colon_symbol_pos = in_line.find(':', 0);
  int space_symbol_pos = in_line.find(' ', 0);
  int line_size = in_line.size();
  int start_pos = 0;
  std::string substring;
  std::string remainder_substring;
  int num;

  // Handle header lines and empty separation lines.
  if (!in_line.empty() && (colon_symbol_pos != line_size - 1)) {
    // Seeds line.
    if (space_symbol_pos == colon_symbol_pos + 1) {
      remainder_substring = in_line.substr(space_symbol_pos + 1);
    } else {
      remainder_substring = in_line;
    }

    space_symbol_pos = remainder_substring.find(' ', 0);
    while (space_symbol_pos != std::string::npos) {
      // Process.
      substring = remainder_substring.substr(0, space_symbol_pos);
      num = std::stoi(substring);
      out_vec.push_back(num);

      // Update.
      remainder_substring = remainder_substring.substr(substring.size() + 1);
      space_symbol_pos = remainder_substring.find(' ', 0);

      // Handle last element.
      if (space_symbol_pos == std::string::npos) {
        num = std::stoi(remainder_substring);
        out_vec.push_back(num);
      }
    }
  }

  return out_vec;
}

void Day5(std::istream& stream) {
  std::string line;
  int line_idx = 0;

  // Seed variables.
  std::vector<int> seed_vec;

  // Seed-to-soil map variables.
  bool seed_to_soil_section = false;
  std::vector<std::vector<int>> seed_to_soil_vec;

  // Soil-to-fertilizer map variables.
  bool soil_to_fertilizer_section = false;
  std::vector<std::vector<int>> soil_to_fertilizer_vec;

  // Fertilizer-to-water map variables.
  bool fertilizer_to_water_section = false;
  std::vector<std::vector<int>> fertilizer_to_water_vec;

  // Water-to-light map variables.
  bool water_to_light_section = false;
  std::vector<std::vector<int>> water_to_light_vec;

  // Light-to-temperature map variables.
  bool light_to_temperature_section = false;
  std::vector<std::vector<int>> light_to_temperature_vec;

  // Temperature-to-humidity map variables.
  bool temperature_to_humidity_section = false;
  std::vector<std::vector<int>> temperature_to_humidity_vec;

  // Humidity-to-location map variables.
  bool humidity_to_location_section = false;
  std::vector<std::vector<int>> humidity_to_location_vec;

  while (std::getline(stream, line)) {
    // Determine section.
    if (line_idx == 0) {
      seed_vec = ExtractNumbersFromLine(line);
    } else if (line == "seed-to-soil map:") {
      seed_to_soil_section = true;
      continue;
    } else if (line == "soil-to-fertilizer map:") {
      soil_to_fertilizer_section = true;
      continue;
    } else if (line == "fertilizer-to-water map:") {
      fertilizer_to_water_section = true;
      continue;
    } else if (line == "water-to-light map:") {
      water_to_light_section = true;
      continue;
    } else if (line == "light-to-temperature map:") {
      light_to_temperature_section = true;
      continue;
    } else if (line == "temperature-to-humidity map:") {
      temperature_to_humidity_section = true;
      continue;
    } else if (line == "humidity-to-location map:") {
      humidity_to_location_section = true;
      continue;
    } else if (line.empty()) {
      seed_to_soil_section = false;
      soil_to_fertilizer_section = false;
      fertilizer_to_water_section = false;
      water_to_light_section = false;
      light_to_temperature_section = false;
      temperature_to_humidity_section = false;
      humidity_to_location_section = false;
      continue;
    }

    // Fill section values.
    if (seed_to_soil_section) {
      seed_to_soil_vec.push_back(ExtractNumbersFromLine(line));
    } else if (soil_to_fertilizer_section) {
      soil_to_fertilizer_vec.push_back(ExtractNumbersFromLine(line));
    } else if (fertilizer_to_water_section) {
      fertilizer_to_water_vec.push_back(ExtractNumbersFromLine(line));
    } else if (water_to_light_section) {
      water_to_light_vec.push_back(ExtractNumbersFromLine(line));
    } else if (light_to_temperature_section) {
      light_to_temperature_vec.push_back(ExtractNumbersFromLine(line));
    } else if (temperature_to_humidity_section) {
      temperature_to_humidity_vec.push_back(ExtractNumbersFromLine(line));
    } else if (humidity_to_location_section) {
      humidity_to_location_vec.push_back(ExtractNumbersFromLine(line));
    }

    // Update.
    line_idx++;
  }

  // Process.
  int nbr_seeds = seed_vec.size();

  for (size_t i = 0; i < nbr_seeds; i++) {
    int seed_number = seed_vec[i];
    int soil_number = -1;
    int fertilizer_number = -1;
    int water_number = -1;
    int light_number = -1;
    int temperature_number = -1;
    int humidity_number = -1;
    int location_number = -1;

    // Seed to soil.
    for (size_t j = 0; j < seed_to_soil_vec.size(); j++) {
      if ((seed_number >= seed_to_soil_vec[j][1]) &&
          (seed_number < seed_to_soil_vec[j][1] + seed_to_soil_vec[j][2] - 1)) {
        soil_number =
            seed_to_soil_vec[j][0] + (seed_number - seed_to_soil_vec[j][1]);
        break;
      }
    }

    soil_number = soil_number < 0 ? seed_number : soil_number;
    fertilizer_number = fertilizer_number < 0 ? soil_number : fertilizer_number;
    water_number = water_number < 0 ? fertilizer_number : water_number;
    light_number = light_number < 0 ? water_number : light_number;
    temperature_number =
        temperature_number < 0 ? light_number : temperature_number;
    humidity_number < 0 ? temperature_number : humidity_number;
    location_number < 0 ? humidity_number : location_number;

    std::cout << seed_number << " " << soil_number << std::endl;
  }

  // for (size_t i = 0; i < seed_vec.size(); i++) {
  //   std::cout << seed_vec[i] << std::endl;
  // }

  // std::vector<std::vector<int>> temp = seed_to_soil_vec;
  // std::cout << seed_to_soil_vec.size() << std::endl;
  // std::cout << seed_to_soil_vec[0].size() << std::endl;
  // for (size_t i = 0; i < temp.size(); i++) {
  //   for (size_t j = 0; j < temp[i].size(); j++) {
  //     std::cout << temp[i][j] << ", ";
  //   }
  //   std::cout << std::endl;
  // }
}
