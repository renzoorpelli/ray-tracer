#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "rtweekend.h"
#include "ray.h"

struct HitRecord {
public:
  Point3 p;
  Vec3 normal;
  double t;
  bool frontFace;
  void SetFaceNormal(const Ray &r, const Vec3 &outwardNormal) {
    // Set the hit record normal record
    // NOTE: paramether 'outward_normal' assume to have unit lenght
    frontFace = Dot(r.Direction(), outwardNormal) < 0;
    normal = frontFace ? outwardNormal : -outwardNormal;
  }
};

#endif
