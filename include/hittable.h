#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "vec3.h"


/// @brief Structure to hold information about a hit record.
class hit_record
{
public:
    /// @brief The point of intersection.
    point3 p; 
    /// @brief the normal at the point of intersection.
    vec3 normal;
    /// @brief distance along the ray to the point of intersection.
    double t;
};


/// @brief Abstract base class for hittable objects (can be intersected by a ray should implement hit(...) function).
class hittable
{
public:
    virtual ~hittable() = default;

    /// @brief 
    /// @param r 
    /// @param ray_tmin 
    /// @param ray_tmax 
    /// @param rec 
    /// @return 
    virtual bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const = 0;
};
#endif
