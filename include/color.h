#ifndef COLOR_H
#define COLOR_H

#define BYTE_RANGE 255.999

#include "vec3.h"
#include <algorithm>
#include <iostream>
using Color = Vec3;

/// @brief Write a single pixel color out to the standard output stream
/// @param out
/// @param pixel_color
inline void WriteColor(std::ostream &out, const Color &pixel_color)
{
  /// w/linear gamma transformation
  auto r = LinearToGamma(pixel_color.x());
  auto g = LinearToGamma(pixel_color.y());
  auto b = LinearToGamma(pixel_color.z());

  // Translates [0,1] components values into the byte range [0, 255]
  int rbyte = int(BYTE_RANGE * Clamp(r, 0.000, 0.999));
  int gbyte = int(BYTE_RANGE * Clamp(g, 0.000, 0.999));
  int bbyte = int(BYTE_RANGE * Clamp(b, 0.000, 0.999));

  // Write out the pixel color components
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
