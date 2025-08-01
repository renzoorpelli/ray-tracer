#include "../include/sphere.h"
#include "../include/hit_record.h"
#include <cmath>

bool HitSphere(const Sphere &sphere, const Ray &r, Interval interval,
               HitRecord &rec) {
  Vec3 oc = sphere.center - r.Origin();
  auto a = r.Direction().LengthSquared();
  auto h = Dot(r.Direction(), oc);
  auto c = oc.LengthSquared() - sphere.radius * sphere.radius;
  auto discriminant = h * h - a * c;

  if (discriminant < 0)
    return false;

  auto sqrt_discriminant = std::sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (h - sqrt_discriminant) / a;
  if (!interval.Surrounds(root)) {
    root = (h + sqrt_discriminant) / a;
    if (!interval.Surrounds(root))
      return false;
  }
  rec.t = root;
  rec.p = r.At(rec.t);
  Vec3 outward_normal = (rec.p - sphere.center) / sphere.radius;
  rec.SetFaceNormal(r, outward_normal);
  rec.normal = (rec.p - sphere.center) / sphere.radius;
  return true;
}
