#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "rtweekend.h"

struct HitRecord {
public:
  Point3 p;
  Vec3 normal;
  double t;
  bool front_face;
  void SetFaceNormal(const Ray &r, const Vec3 &outward_normal) {
    // Set the hit record normal record
    // NOTE: paramether 'outward_normal' assume to have unit lenght
    front_face = dot(r.Direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

#endif
