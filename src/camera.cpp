#include "../include/color.h"
#include "../include/hittable_list.h"
#include "../include/interval.h"
#include "../include/ray.h"
#include "../include/rtweekend.h"
#include "../include/vec3.h"
#include <fstream>
#include <iostream>

// Image
const double aspectRatio = 16.0 / 9.0; // Rendered img widht over height.
const int imageWidth = 400;            // Rendered img width in pxl count.
const int samplesPerPixel = 100;      // COunt of random samples for each pxl.
const auto maxDepth = 50;               // Maximum number of ray bounes into the scene.

int imageHeight = int(imageWidth / aspectRatio); // Rendered image height
double pixelSamplesScale;                         // Color scale factor for a sum of pixel samples
Point3 center;                                      // Camera center
Point3 initialPixel;                                 // Location of pixel (0,0)
Vec3 pixelDeltaU;                                 // Offset to pixel to right
Vec3 pixelDeltaV;                                 // Offset to pixel below

// Camera
const auto focalLength = 1.0;
const auto viewportHeight = 2.0;
const auto viewportWidth =
    viewportHeight * double(imageWidth) / imageHeight;

Vec3 SampleSquare()
{
  // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit
  // square.
  return Vec3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0);
}

void Initialize()
{

  imageHeight = int(imageWidth / aspectRatio);
  imageHeight = (imageHeight < 1) ? 1 : imageHeight;

  pixelSamplesScale = 1.0 / samplesPerPixel;

  center = Point3(0, 0, 0);

  // Determine viewport dimensions.
  auto focalLength = 1.0;
  auto viewportHeight = 2.0;
  auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

  // Calculate the vectors across the horizontal and down the vertical viewport
  // edges.
  auto viewportU = Vec3(viewportWidth, 0, 0);
  auto viewportV = Vec3(0, -viewportHeight, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  pixelDeltaU = viewportU / imageWidth;
  pixelDeltaV = viewportV / imageHeight;

  // Calculate the location of the upper left pixel.
  auto viewportUpperLeft =
      center - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
  initialPixel = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
}

Ray GetRay(int i, int j)
{

  // Construct a camera ray originating from the origin and directed at randomly
  // sampled point around the pixel location i, j.

  auto offset = SampleSquare();
  auto pixelSample = initialPixel + ((i + offset.x()) * pixelDeltaU) +
                      ((j + offset.y()) * pixelDeltaV);

  auto rayOrigin = center;
  auto rayDirection = pixelSample - rayOrigin;

  return Ray(rayOrigin, rayDirection);
}

/// @brief Calculate the color seen along a ray.
/// This function determines the color of a pixel based on the ray's
/// intersection with a sphere.
/// @param r
/// @return
Color RayColor(const Ray &r, int depth, const HittableList &world)
{
  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0)
    return Color(0, 0, 0);

  HitRecord rec;

  // prevent shadow acne = t = 0.00001
  if (world.Hit(r, Interval(0.001, infinity), rec))
  {
    // lambertian reflection
    auto scatterDirection = rec.normal +  RandomOnHemisphere  (rec.normal);
    return 0.1 * RayColor(Ray(rec.p, scatterDirection), depth - 1, world);
  }

  Vec3 unitDirection = UnitVector(r.Direction());
  auto a = 0.5 * (unitDirection.y() + 1.0);
  return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

void Render(const HittableList &world)
{
  Initialize();

  std::ofstream file("image.ppm");
  file << "P3\n"
       << imageWidth << ' ' << imageHeight << "\n255\n";

  for (int j = 0; j < imageHeight; j++)
  {
    std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' '
              << std::flush;
    for (int i = 0; i < imageWidth; i++)
    {
      Color pixelColor(0, 0, 0);
      for (int sample = 0; sample < samplesPerPixel; sample++)
      {
        Ray r = GetRay(i, j);
        pixelColor += RayColor(r, maxDepth, world);
      }
      WriteColor(file, pixelSamplesScale * pixelColor);
    }
  }

  file.close();
  std::clog << "\rDone.                 \n";
}
