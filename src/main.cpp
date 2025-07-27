#include <iostream>

#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/rtweekend.h"

/// @brief Calculate the color seen along a ray.
/// This function determines the color of a pixel based on the ray's
/// intersection with a sphere.
/// @param r
/// @return
Color RayColor(const Ray &r, const HittableList &world) {
  HitRecord rec;

  if (world.Hit(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + Color(1, 1, 1));
  }

  Vec3 unit_direction = unit_vector(r.Direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main() {
  /*
     This is a simple ray tracer that outputs a P3 (ASCII) PPM image.
     The PPM format is a simple image format that can be easily read and
     written. the p3 menas colors are in ASCII, the 3 columns and 2 rows, then
     255 for max color, then RGB triplets
   */

  // Image
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  // Calculate the image height, and ensure that it's at least 1.
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * double(image_width) / image_height;
  auto camera_center = Point3(0, 0, 0);

  // World
  HittableList world;
  world.Add(Hittable{HittableType::HITTABLE_SPHERE, {{Point3(0, 0, -1), 0.5}}});
  world.Add(
      Hittable{HittableType::HITTABLE_SPHERE, {{Point3(0, -100.5, -1), 100}}});

  // Calculate the vectors across the horizontal and down the vertical viewport
  // edges.
  auto viewport_u = Vec3(viewport_width, 0, 0);
  auto viewport_v = Vec3(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  // Calculate the location of the upper left pixel.
  auto viewport_upper_left = camera_center - Vec3(0, 0, focal_length) -
                             viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc =
      viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // Render
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << " \r Scanlines remaining: " << (image_height - j) << ' '
              << std::flush;

    for (int i = 0; i < image_width; i++) {
      auto pixel_center =
          pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      auto ray_direction = pixel_center - camera_center;
      Ray r(camera_center, ray_direction);

      Color pixel_color = RayColor(r, world);
      WriteColor(std::cout, pixel_color);
    }
  }
  std::clog << "\r Done. \n";
}
