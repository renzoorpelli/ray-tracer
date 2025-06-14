#include <iostream>

#include "color.h"
#include "vec3.h"

struct Dish
{
    std::string name;
    std::vector<std::string> ingredients;
};

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    // P3
    /*
        the p3 menas colors are in ASCII, the 3 columns and 2 rows,
        then 255 for max color, then RGB triplets
    */
    // image
    constexpr int image_width = 256, image_height = 256;

    // render
    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << " \rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; i++)
        {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.0;

            auto pixel_color = color(r, g, b);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\r Done. \n";
}