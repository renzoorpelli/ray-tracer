
#include "../include/camera.h"
#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include <cstdlib>

void OpenImage() {
  auto open_img_cmd = "open ./image.ppm";
  std::system(open_img_cmd);
}

int main() {
  // Render World
  HittableList world;

  world.Add(Hittable{HittableType::HITTABLE_SPHERE, {{Point3(0, 0, -1), 0.5}}});
  world.Add(
      Hittable{HittableType::HITTABLE_SPHERE, {{Point3(0, -100.5, -1), 100}}});

  Render(world);
  OpenImage();
}
