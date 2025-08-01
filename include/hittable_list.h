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

    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = interval.max;

    for (const auto &item : items) {
      if (HitObject(item, r, Interval(interval.min, closest_so_far), temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }
    return hit_anything;
  }

  void Add(Hittable item) { items.push_back(item); }

  void Clear() { items.clear(); }
};

#endif
