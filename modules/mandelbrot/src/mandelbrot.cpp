#include "mandelbrot.hpp"

#include <SDL2/SDL.h>

#include <cmath>
#include <complex>
#include <iostream>
#include <numeric>
#include <string>

const int kWindowWidth = 800;
const int kWindowHeight = 600;
const double kXMin = -2.0;
const double kXMax = 1.0;
const double kYMin = -1.0;
const double kYMax = 1.0;
const int kResolution = 1000;
const int kMaxIterations = 80;

static int CalculateMandelbrot(std::complex<double> c) {
  std::complex<double> z(0, 0);
  for (int iteration = 0; iteration < kMaxIterations; iteration++) {
    z = std::pow(z, 2) + c;

    if (std::norm(z) > 2) {
      return iteration;
    }
  }
  return 0;
}

void Mandelbrot() {
  // Initialize SDL.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Failed to initialize SDL" << std::endl;
  }

  // Create a window.
  SDL_Window* window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, kWindowWidth,
                                        kWindowHeight, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Failed to create window" << std::endl;
    SDL_Quit();
  }

  // Create a renderer.
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Failed to create renderer" << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  int buffer_iterations[kResolution * kResolution];
  double step_size = (kXMax - kXMin) / static_cast<double>(kResolution);

  int k = 0;
  for (double x = kXMin; x < kXMax; x += step_size) {
    for (double y = kYMin; y < kYMax; y += step_size) {
      buffer_iterations[k] = CalculateMandelbrot(std::complex<double>(x, y));
      k++;
    }
  }

  // Main loop flag.
  bool running = true;

  // Event loop.
  SDL_Event e;
  while (running) {
    // Handle events on queue.
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit.
      if (e.type == SDL_QUIT) {
        running = false;
      }
    }

    // Clear the screen to black.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw stuff.
    int k = 0;
    for (double x = kXMin; x < kXMax; x += step_size) {
      for (double y = kYMin; y < kYMax; y += step_size) {
        double px = kWindowWidth * (x - kXMin) / (kXMax - kXMin);
        double py = kWindowHeight * (y - kYMax) / (kYMin - kYMax);
        int m = buffer_iterations[k];
        int color = 255 - static_cast<int>(m * 255 / kMaxIterations);

        // SDL_SetRenderDrawColor(renderer, color, color, color, 255);
        SDL_SetRenderDrawColor(renderer, 2 * m % 255, 3 * m % 255, 4 * m % 255,
                               255);
        SDL_RenderDrawPointF(renderer, px, py);

        k++;
      }
    }

    // Update screen.
    SDL_RenderPresent(renderer);
  }

  // Free resources and close SDL.
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
