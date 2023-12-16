#include <algorithm>
#include <iostream>
#include <vector>

static std::vector<long int> ExtractNumbersFromLine(std::string& in_line) {
  std::vector<long int> out_vec;
  // Maybe make separator more generic.
  int colon_symbol_pos = in_line.find(':', 0);
  int space_symbol_pos = in_line.find(' ', 0);
  int line_size = in_line.size();
  int start_pos = 0;
  std::string substring;
  std::string remainder_substring;
  long int num;

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
      num = std::stol(substring);
      out_vec.push_back(num);

      // Update.
      remainder_substring = remainder_substring.substr(substring.size() + 1);
      space_symbol_pos = remainder_substring.find(' ', 0);

      // Handle last element.
      if (space_symbol_pos == std::string::npos) {
        num = std::stol(remainder_substring);
        out_vec.push_back(num);
      }
    }
  }

  return out_vec;
}

static long int GetDestinationNumber(long int source_number,
                                     std::vector<std::vector<long int>> map) {
  long int destination_number = -1;

  for (size_t i = 0; i < map.size(); i++) {
    if ((source_number >= map[i][1]) &&
        (source_number <= map[i][1] + map[i][2] - 1)) {
      destination_number = map[i][0] + (source_number - map[i][1]);
      break;
    }
  }

  destination_number =
      destination_number < 0 ? source_number : destination_number;

  return destination_number;
}

void Day5(std::istream& stream) {
  std::string line;
  int line_idx = 0;
  std::vector<long int>::iterator lowest_location;

  // Seed variables.
  std::vector<long int> seed_vec;

  // Seed-to-soil map variables.
  bool seed_to_soil_section = false;
  std::vector<std::vector<long int>> seed_to_soil_vec;

  // Soil-to-fertilizer map variables.
  bool soil_to_fertilizer_section = false;
  std::vector<std::vector<long int>> soil_to_fertilizer_vec;

  // Fertilizer-to-water map variables.
  bool fertilizer_to_water_section = false;
  std::vector<std::vector<long int>> fertilizer_to_water_vec;

  // Water-to-light map variables.
  bool water_to_light_section = false;
  std::vector<std::vector<long int>> water_to_light_vec;

  // Light-to-temperature map variables.
  bool light_to_temperature_section = false;
  std::vector<std::vector<long int>> light_to_temperature_vec;

  // Temperature-to-humidity map variables.
  bool temperature_to_humidity_section = false;
  std::vector<std::vector<long int>> temperature_to_humidity_vec;

  // Humidity-to-location map variables.
  bool humidity_to_location_section = false;
  std::vector<std::vector<long int>> humidity_to_location_vec;

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
  std::vector<long int> location_vec;

  for (size_t i = 0; i < nbr_seeds; i++) {
    long int seed_number = seed_vec[i];
    long int soil_number;
    long int fertilizer_number;
    long int water_number;
    long int light_number;
    long int temperature_number;
    long int humidity_number;
    long int location_number;

    // Seed to soil.
    soil_number = GetDestinationNumber(seed_number, seed_to_soil_vec);

    // Soil to fertilizer.
    fertilizer_number =
        GetDestinationNumber(soil_number, soil_to_fertilizer_vec);

    // Fertilizer to water.
    water_number =
        GetDestinationNumber(fertilizer_number, fertilizer_to_water_vec);

    // Water to light.
    light_number = GetDestinationNumber(water_number, water_to_light_vec);

    // Light to temperature.
    temperature_number =
        GetDestinationNumber(light_number, light_to_temperature_vec);

    // Temperature to humidity.
    humidity_number =
        GetDestinationNumber(temperature_number, temperature_to_humidity_vec);

    // Humidity to location.
    location_number =
        GetDestinationNumber(humidity_number, humidity_to_location_vec);

    location_vec.push_back(location_number);
  }

  lowest_location =
      std::min_element(std::begin(location_vec), std::end(location_vec));

  // Present result.
  std::cout << "Part one lowest location: " << *lowest_location << std::endl;
}
