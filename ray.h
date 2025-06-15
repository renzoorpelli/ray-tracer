#ifndef RAY_H
#define RAY_H

#include "vec3.h"

/*
     P(t) = A + tB;
     P(t) = origin + t * direction;
*/
class ray
{
public:
    ray() {}

    ray(const point3 &origin, const vec3 &direction) : orig(origin), dir(direction) {}

    /// @brief the start point of the ray
    /// @return
    const point3 &origin() const
    {
        return orig;
    }

    /// @brief where the ray points to
    /// @return
    const vec3 &direction() const
    {
        return dir;
    }

    /// @brief computation to see what color is seen along the ray
    /// @param t scalar value
    /// @return
    point3 at(double t)
    {
        return orig + t * dir;
    }

private:
    point3 orig;
    vec3 dir;
};

#endif