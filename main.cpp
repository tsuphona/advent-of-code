#include <tclap/CmdLine.h>

#include <fstream>
#include <iostream>
#include <string>

#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"

int main(int argc, char** argv) {
  try {
    // Define the command line object.
    TCLAP::CmdLine cmd("Run selected modules", ' ', "0.0.1");

    // Define a value argument and add it to command line.
    TCLAP::ValueArg<int> moduleArg("d", "day", "Day to run", true, 1, "int");
    cmd.add(moduleArg);

    TCLAP::ValueArg<std::string> inputArg("i", "input", "Path to input file",
                                          true, "", "str");
    cmd.add(inputArg);

    // Parse the command line arguments.
    cmd.parse(argc, argv);

    // Get the value parsed by each argument.
    int module = moduleArg.getValue();

    // Read file.
    std::string path = inputArg.getValue();

    std::ifstream file(path);

    // Check error.
    if (!file) {
      std::cerr << "Error opening file." << std::endl;
    }

    // Run modules.
    switch (module) {
      case 1:
        std::cout << "Running Advent of Code: Day1" << std::endl;
        Day1(file);
        break;

      case 2:
        std::cout << "Running Advent of Code: Day2" << std::endl;
        Day2(file);
        break;

      case 3:
        std::cout << "Running Advent of Code: Day3" << std::endl;
        Day3(file);
        break;

      case 4:
        std::cout << "Running Advent of Code: Day4" << std::endl;
        Day4(file);
        break;
    }

    file.close();  // Optional

  } catch (TCLAP::ArgException& e) {
    std::cerr << "Error: " << e.error() << " for arg " << e.argId()
              << std::endl;
    return 1;
  }

  return 0;
}
