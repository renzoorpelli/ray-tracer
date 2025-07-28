#include "../include/color.h"
#include "../include/hittable_list.h"
#include "../include/ray.h"
#include "../include/rtweekend.h"
#include "../include/vec3.h"
#include <iostream>

// Image
const double aspect_ratio = 16.0 / 9.0;
const int image_width = 400;

// Calculate the image height, and ensure that it's at least 1.
int image_height = int(image_width / aspect_ratio);

// Camera
const auto focal_length = 1.0;
const auto viewport_height = 2.0;
const auto viewport_width =
    viewport_height * double(image_width) / image_height;
auto camera_center = Point3(0, 0, 0);

// Calculate the vectors across the horizontal and down the vertical viewport
// edges.
auto viewport_u = Vec3(viewport_width, 0, 0);
auto viewport_v = Vec3(0, -viewport_height, 0);

// Calculate the horizontal and vertical delta vectors from pixel to pixel.
auto pixel_delta_u = viewport_u / image_width;
auto pixel_delta_v = viewport_v / image_height;

// Calculate the location of the upper left pixel.
auto viewport_upper_left =
    camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

void Initialize() {

  image_height = (image_height < 1) ? 1 : image_height;

  camera_center = Point3(0, 0, 0);

  // Determine viewport dimensions.
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (double(image_width) / image_height);

  // Calculate the vectors across the horizontal and down the vertical viewport
  // edges.
  auto viewport_u = Vec3(viewport_width, 0, 0);
  auto viewport_v = Vec3(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  pixel_delta_u = viewport_u / image_width;
  pixel_delta_v = viewport_v / image_height;

  // Calculate the location of the upper left pixel.
  auto viewport_upper_left = camera_center - Vec3(0, 0, focal_length) -
                             viewport_u / 2 - viewport_v / 2;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

/// @brief Calculate the color seen along a ray.
/// This function determines the color of a pixel based on the ray's
/// intersection with a sphere.
/// @param r
/// @return
Color RayColor(const Ray &r, const HittableList &world) {
  HitRecord rec;

  if (world.Hit(r, Interval(0, infinity), rec)) {
    return 0.5 * (rec.normal + Color(1, 1, 1));
  }

  Vec3 unit_direction = UnitVector(r.Direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

void Render(const HittableList &world) {
  Initialize();

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
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

  std::clog << "\rDone.                 \n";
}
