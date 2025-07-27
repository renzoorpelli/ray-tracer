#ifndef SPHERE_H
#define SPHERE_H

#include "hit_record.h"

struct Sphere {
  Point3 center;
  double radius;
};

bool HitSphere(const Sphere &sphere, const Ray &r, double ray_tmin,
               double ray_tmax, HitRecord &rec);

#endif
