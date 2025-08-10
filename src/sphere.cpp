#include "../include/sphere.h"
#include "../include/hit_record.h"
#include <cmath>

bool HitSphere(const Sphere &sphere, const Ray &r, Interval interval,HitRecord &rec) {
  Vec3 oc = sphere.center - r.Origin();
  auto a = r.Direction().LengthSquared();
  auto h = Dot(r.Direction(), oc);
  auto c = oc.LengthSquared() - sphere.radius * sphere.radius;
  auto discriminant = h * h - a * c;

  if (discriminant < 0)
    return false;

  auto sqrtDiscriminant = std::sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (h - sqrtDiscriminant) / a;
  if (!interval.Surrounds(root)) {
    root = (h + sqrtDiscriminant) / a;
    if (!interval.Surrounds(root))
      return false;
  }
  rec.t = root;
  rec.p = r.At(rec.t);
  Vec3 outwardNormal = (rec.p - sphere.center) / sphere.radius;
  rec.SetFaceNormal(r, outwardNormal);
  rec.normal = (rec.p - sphere.center) / sphere.radius;
  return true;
}
