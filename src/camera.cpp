#include "../include/color.h"
#include "../include/hittable_list.h"
#include "../include/ray.h"
#include "../include/rtweekend.h"
#include "../include/vec3.h"
#include "../include/interval.h"
#include <fstream>
#include <iostream>

// Image
const double aspect_ratio = 16.0 / 9.0; // Rendered img widht over height.
const int image_width = 400;            // Rendered img width in pxl count.
const int samples_per_pixel = 10;       // COunt of random samples for each pxl.

int image_height = int(image_width / aspect_ratio); // Rendered image height
double pixel_samples_scale; // Color scale factor for a sum of pixel samples
Point3 center;              // Camera center
Point3 pixel00_loc;         // Location of pixel (0,0)
Vec3 pixel_delta_u;         // Offset to pixel to right
Vec3 pixel_delta_v;         // Offset to pixel below

// Camera
const auto focal_length = 1.0;
const auto viewport_height = 2.0;
const auto viewport_width =
    viewport_height * double(image_width) / image_height;

Vec3 SampleSquare() {
  // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit
  // square.
  return Vec3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0);
}

void Initialize() {

  image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  pixel_samples_scale = 1.0 / samples_per_pixel;

  center = Point3(0, 0, 0);

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
  auto viewport_upper_left =
      center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Ray GetRay(int i, int j) {

  // Construct a camera ray originating from the origin and directed at randomly
  // sampled point around the pixel location i, j.

  auto offset = SampleSquare();
  auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) +
                      ((j + offset.y()) * pixel_delta_v);

  auto ray_origin = center;
  auto ray_direction = pixel_sample - ray_origin;

  return Ray(ray_origin, ray_direction);
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

  std::ofstream file("image.ppm");
  file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
              << std::flush;
    for (int i = 0; i < image_width; i++) {
      // auto pixel_center =
      //     pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      // auto ray_direction = pixel_center - center;
      // Ray r(center, ray_direction);

      // Color pixel_color = RayColor(r, world);
      // WriteColor(file, pixel_color);

      Color pixel_color(0, 0, 0);
      for (int sample = 0; sample < samples_per_pixel; sample++) {
        Ray r = GetRay(i, j);
        pixel_color += RayColor(r, world);
      }
      WriteColor(file, pixel_samples_scale * pixel_color);
    }
  }

  file.close();
  std::clog << "\rDone.                 \n";
}
