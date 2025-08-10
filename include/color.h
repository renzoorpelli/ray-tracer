#ifndef COLOR_H
#define COLOR_H

#define BYTE_RANGE 255.999

#include "vec3.h"
#include <algorithm>
#include <iostream>
using Color = Vec3;

/// @brief Write a single pixel color out to the standard output stream
/// @param out
/// @param pixelColor
inline void WriteColor(std::ostream &out, const Color &pixelColor)
{
  /// w/linear gamma transformation
  auto r = LinearToGamma(pixelColor.x());
  auto g = LinearToGamma(pixelColor.y());
  auto b = LinearToGamma(pixelColor.z());

  // Translates [0,1] components values into the byte range [0, 255]
  int rbyte = int(BYTE_RANGE * std::clamp(r, 0.000, 0.999));
  int gbyte = int(BYTE_RANGE * std::clamp(g, 0.000, 0.999));
  int bbyte = int(BYTE_RANGE * std::clamp(b, 0.000, 0.999));

  // Write out the pixel color components
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
