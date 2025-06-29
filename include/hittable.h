#ifndef HITTABLE_H
#define HITTABLE_H

#include <variant>
#include <cmath>
#include "ray.h"
#include "vec3.h"

struct HitRecord {
    Point3 p;
    Vec3 normal;
    double t;
};

struct Sphere {
    Point3 center;
    double radius;

    Sphere(const Point3& c, double r) : center(c), radius(r) {}

    bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const {
        Vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius * radius;
        auto discriminant = h * h - a * c;

        if (discriminant < 0)
            return false;

        auto sqrt_discriminant = std::sqrt(discriminant);

        auto root = (-h - sqrt_discriminant) / a;
        if (root < ray_tmin || root > ray_tmax) {
            root = (-h + sqrt_discriminant) / a;
            if (root < ray_tmin || root > ray_tmax)
                return false;
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;
        return true;
    }
};

using HittableVariant = std::variant<Sphere>;

struct Hittable {
    HittableVariant shape;

    template<typename Shape>
    Hittable(Shape&& s) : shape(std::forward<Shape>(s)) {}

    bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const {
        return std::visit([&](auto&& obj) {
            return obj.hit(r, ray_tmin, ray_tmax, rec);
        }, shape);
    }
};

#endif