add_library(mandelbrot src/mandelbrot.cpp)

target_include_directories(mandelbrot PRIVATE include)

target_link_libraries(mandelbrot PRIVATE SDL2::SDL2)
