#ifndef SPHERE_H
#define SPHERE_H

#include "hit_record.h"
#include "interval.h"

struct Sphere {
  Point3 center;
  double radius;
};

bool HitSphere(const Sphere &sphere, const Ray &r, Interval interval,
               HitRecord &rec);

#endif
