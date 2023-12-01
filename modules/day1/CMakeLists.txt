add_library(day1 src/day1.cpp)

target_include_directories(day1 PUBLIC include)

# Only add tests if this is the main app Prevents tests from being added in
# projects that include this one as a subproject
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # Enable testing for this directory and below
  enable_testing()

  # Add a test executable
  add_executable(test_day1 tests/test_day1.cpp)

  # Link the test executable with Google Test and the module's library
  target_link_libraries(test_day1 gtest gtest_main day1)

  # Add the test to CTest
  add_test(NAME test_day1 COMMAND test_day1)
endif()
