#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "vec3.h"
#include "hit_record.h"

struct Sphere {
  Point3 center;
  double radius;

  Sphere(const Point3 &c, double r) : center(c), radius(r) {}

  bool hit(const Ray &r, double ray_tmin, double ray_tmax,
           HitRecord &rec) const;
};

#endif