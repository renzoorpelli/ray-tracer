#ifndef COLOR.H
#define COLOR .H

#define BYTE_RANGE 255.999

#include "vec3.h"
#include <iostream>

using color = vec3;

/// @brief Write a single pixel color out to the standard output stream
/// @param out
/// @param pixel_color
void write_color(std::ostream &out, const color &pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translates [0,1] components values into the byte range [0, 255]
    int rbyte = int(BYTE_RANGE * r);
    int gbyte = int(BYTE_RANGE * g);
    int bbyte = int(BYTE_RANGE * b);

    // Write out the pixel color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif