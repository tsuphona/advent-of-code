# Specify the minimun version for Cmake.
cmake_minimum_required(VERSION 3.26)

# Specify project name.
project(aoc VERSION 0.0.1)

# Specify C++ standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDRAD_REQUIRED)

# Add subdirectories.
add_subdirectory(modules/day1)
add_subdirectory(modules/day2)
add_subdirectory(modules/day3)
add_subdirectory(modules/day4)

# ---------- Google test stuff ----------
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG b10fad38c4026a29ea6561ab15fc4818170d1c10 # release-1.14.0
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE)

# For Google Test, prevent overriding the parent project's compiler/linker
# settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# ---------- Main and TCLAP stuff ----------
add_executable(aoc main.cpp)
enable_testing()
target_include_directories(
  aoc
  PRIVATE external/tclap/include
  PRIVATE modules/day1/include
  PRIVATE modules/day2/include
  PRIVATE modules/day3/include
  PRIVATE modules/day4/include)

target_link_libraries(
  aoc
  PRIVATE day1
  PRIVATE day2
  PRIVATE day3
  PRIVATE day4)
