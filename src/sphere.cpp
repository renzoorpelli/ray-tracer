#include "../include/sphere.h"
#include "../include/hit_record.h"

bool Sphere::hit(const Ray &r, double ray_tmin, double ray_tmax,
                 HitRecord &rec) const {
  Vec3 oc = center - r.origin();
  auto a = r.direction().length_squared();
  auto h = dot(r.direction(), oc);
  auto c = oc.length_squared() - radius * radius;
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
  Vec3 outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);
  rec.normal = (rec.p - center) / radius;
  return true;
}
