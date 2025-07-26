# Ray Tracer

A simple bare-metal ray tracer written in C++.

---

## Useful Commands

### Build with CMake

To build the project in release mode, run:
```
cmake --build build --config release
```

### Generate PPM Image

After building, run the binary to generate a PPM image:
```
./{binary_name} > image.ppm
```
Replace `{binary_name}` with the actual name of your compiled binary.

---

## Glossary

- **viewport**: Rectangular area on a display device where a 2D/3D scene is rendered and displayed.
- **camera**: Point where all rays originate (also called "eye").
- **ray**: Line with an origin and direction.
- **aspect ratio**: Ratio of width to height of the image (e.g., 16:9).
- **pixel spacing**: Determines how far apart the pixels are in 3D space.
- **camera origin**: Point where all rays start (typically (0, 0, 0)).

---

## Math Reference

- **r**: Radius of the sphere.
- **C**: Coordinates of the center of the sphere (vector C: (Cx, Cy, Cz)).
- **|v|**: Magnitude or length of the vector.  
  \|v\| = √(x² + y² + z²)


## Key concepts
- Hittable = things you can hit (spheres, planes)
- HitRecord = result data from a hit
- HittableList = collection of Hittable objects
