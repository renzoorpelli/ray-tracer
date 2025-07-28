#include "../include/hittable.h"
#include "../include/sphere.h"

bool HitObject(const Hittable &obj, const Ray &r, Interval interval,
               HitRecord &rec) {
  switch (obj.type) {
  case HittableType::HITTABLE_SPHERE:
    return HitSphere(obj.object.sphere, r, interval, rec);
  default:
    return false;
  }
}
