#ifndef HITTABLE_H
#define HITTABLE_H

#include "hit_record.h"
#include "sphere.h"
#include <variant>

enum class HittableType {
  HITTABLE_SPHERE,
  // add more HITTABLE_*
};

struct Hittable {
  HittableType type;
  union {
    Sphere sphere;
    // add more Hittable objects to the union
  } object;
};

bool hitObject(const Hittable &obj, const Ray &r, double ray_tmin,
               double ray_tmax, HitRecord &rec);

#endif
