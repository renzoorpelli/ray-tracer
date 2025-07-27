#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>

struct HittableList {
  std::vector<Hittable> items;

  bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    if (items.empty())
      return false;

    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto &item : items) {
      if (hitObject(item, r, t_min, closest_so_far, temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }
    return hit_anything;
  }

  void add(Hittable item) { items.push_back(item); }

  void clear() { items.clear(); }
};

#endif
