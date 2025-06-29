#ifndef RAY_H
#define RAY_H

#include "vec3.h"

/*
     P(t) = A + tB;
     P(t) = origin + t * direction;
*/
class Ray
{
public:
    Ray() {}

    Ray(const Point3 &origin, const Vec3 &direction) : orig(origin), dir(direction) {}

    /// @brief the start point of the ray
    /// @return
    const Point3 &origin() const
    {
        return orig;
    }

    /// @brief where the ray points to
    /// @return
    const Vec3 &direction() const
    {
        return dir;
    }

    /// @brief computation to see what color is seen along the ray
    /// @param t scalar value
    /// @return
    Point3 at(double t) const
    {
        return orig + t * dir;
    }

private:
    Point3 orig;
    Vec3 dir;
};

#endif