#include "../include/sphere.h"
#include "../include/hit_record.h"
#include <cmath>

bool hitSphere(const Sphere &sphere, const Ray &r, double ray_tmin, double ray_tmax,
               HitRecord &rec) {
  Vec3 oc = sphere.center - r.origin();
  auto a = r.direction().length_squared();
  auto h = dot(r.direction(), oc);
  auto c = oc.length_squared() - sphere.radius * sphere.radius;
  auto discriminant = h * h - a * c;

  if (discriminant < 0)
    return false;

  auto sqrt_discriminant = std::sqrt(discriminant);

  auto root = (-h - sqrt_discriminant) / a;
  if (root < ray_tmin || root > ray_tmax) {
    root = (-h + sqrt_discriminant) / a;
    if (root < ray_tmin || root > ray_tmax)
      return false;
  }
  rec.t = root;
  rec.p = r.at(rec.t);
  Vec3 outward_normal = (rec.p - sphere.center) / sphere.radius;
  rec.set_face_normal(r, outward_normal);
  rec.normal = (rec.p - sphere.center) / sphere.radius;
  return true;
}
