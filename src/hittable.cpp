#include "../include/hittable.h"
#include "../include/sphere.h"

bool HitObject(const Hittable &obj, const Ray &r, double ray_tmin,
               double ray_tmax, HitRecord &rec) {
  switch (obj.type) {
  case HittableType::HITTABLE_SPHERE:
    return HitSphere(obj.object.sphere, r, ray_tmin, ray_tmax, rec);
  default:
    return false;
  }
}
