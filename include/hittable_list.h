#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "interval.h"
#include "ray.h"
#include <vector>

struct HittableList {
  std::vector<Hittable> items;

  bool Hit(const Ray &r, Interval interval, HitRecord &rec) const {
    if (items.empty())
      return false;

    HitRecord tempRec;
    bool hitAnything = false;
    auto closestSoFar = interval.max;

    for (const auto &item : items) {
      if (HitObject(item, r, Interval(interval.min, closestSoFar), tempRec)) {
        hitAnything = true;
        closestSoFar = tempRec.t;
        rec = tempRec;
      }
    }
    return hitAnything;
  }

  void Add(Hittable item) { items.push_back(item); }

  void Clear() { items.clear(); }
};

#endif
