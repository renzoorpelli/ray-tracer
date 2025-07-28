#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "hittable_list.h"
#include "ray.h"
#include "color.h"

void Initialize();
Color RayColor(const Ray &r, const HittableList &world);
void Render(const HittableList &world);

#endif