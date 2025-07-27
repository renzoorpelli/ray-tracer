#include "../include/hittable.h"
#include "../include/sphere.h"

bool hitObject(const Hittable &obj, const Ray &r, double ray_tmin, double ray_tmax, HitRecord &rec) {
  switch (obj.type) {
  case HittableType::HITTABLE_SPHERE:
    return hitSphere(obj.object.sphere, r, ray_tmin, ray_tmax, rec);
  default:
    return false;
  }
}