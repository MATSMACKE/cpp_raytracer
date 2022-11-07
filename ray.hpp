#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

struct Ray {
    Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction) {}

    Vec3 origin;
    Vec3 direction;
};

#endif