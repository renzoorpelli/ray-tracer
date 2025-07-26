#ifndef HITTABLE_H
#define HITTABLE_H

#include "hit_record.h"
#include "ray.h"
#include "sphere.h"
#include <variant>

using HittableVariant = std::variant<Sphere>;

struct Hittable {
  HittableVariant shape;

  template <typename Shape>
  Hittable(Shape &&s) : shape(std::forward<Shape>(s)) {}

  bool hit(const Ray &r, double ray_tmin, double ray_tmax,
           HitRecord &rec) const noexcept {
    return std::visit(
        [&](auto &&obj) { return obj.hit(r, ray_tmin, ray_tmax, rec); }, shape);
  }
};

#endif
