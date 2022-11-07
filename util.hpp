#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <cmath>

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline Vec3 random_vec3() {
    return Vec3(random_double(), random_double(), random_double());
}

inline Vec3 random_vec3(double min, double max) {
    return Vec3(random_double(min,max), random_double(min,max), random_double(min,max));
}

inline Vec3 random_in_unit_sphere() {
    while (true) {
        Vec3 p = random_vec3(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline Vec3 random_unit_in_unit_sphere() {
    return unit_vector(random_in_unit_sphere());
}

inline Vec3 refract_ray(const Vec3& in_direction, const Vec3& normal, double ratio) {
    auto cos_theta = dot(-in_direction, normal);
    Vec3 out_perp = ratio * (in_direction + cos_theta*normal);
    Vec3 out_parallel = -sqrt(fabs(1.0 - out_perp.length_squared())) * normal;
    return out_perp + out_parallel;
}

class Material;

struct Hit {
    bool occurred;
    double distance;
    Vec3 normal;
    std::shared_ptr<Material> material;
};

#endif