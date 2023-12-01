#include <tclap/CmdLine.h>

#include <iostream>
#include <string>

#include "mandelbrot.hpp"

int main(int argc, char** argv) {
  try {
    // Define the command line object.
    TCLAP::CmdLine cmd("Run selected modules", ' ', "0.0.1");

    // Define a value argument and add it to command line.
    TCLAP::ValueArg<int> moduleArg("m", "module", "Module to run", true, 0,
                                   "int");
    cmd.add(moduleArg);

    // Parse the command line arguments.
    cmd.parse(argc, argv);

    // Get the value parsed by each argument.
    int module = moduleArg.getValue();

    // Run modules.
    switch (module) {
      case 0:
        std::cout << "Running module: connect_the_dots" << module << std::endl;
        break;
      case 1:
        std::cout << "Running module: mandelbrot" << module << std::endl;
        Mandelbrot();
        break;
    }

  } catch (TCLAP::ArgException& e) {
    std::cerr << "Error: " << e.error() << " for arg " << e.argId()
              << std::endl;
    return 1;
  }

  return 0;
}
