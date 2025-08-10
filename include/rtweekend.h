
#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double DegreesToRadians(double degrees) { return degrees * pi / 180.0; }

inline double RandomDouble() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  
  return distribution(generator);
}

inline double RandomDouble(double min, double max) {
  // Returns a random real in [min,max).
  return min + (max - min) * RandomDouble();
}

// Common Headers
#include "vec3.h"
#include "color.h"

#endif
