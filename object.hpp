#ifndef OBJECT_H
#define OBJECT_H

#include <memory>

#include "vec3.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "util.hpp"

class Object {
    public:
        virtual Hit intersect(const Ray & ray) const = 0;
        virtual std::shared_ptr<Material> get_material() const = 0;
        virtual ~Object() = default;
};

class Sphere : public Object {
    public:
        Sphere(Vec3 origin, double radius, std::shared_ptr<Material> material) : origin(origin), radius(radius), material(material) {}

        Hit intersect(const Ray & ray) const override;
        std::shared_ptr<Material> get_material() const override;

    private:
        Vec3 origin;
        double radius;
        std::shared_ptr<Material> material;
};

Hit Sphere::intersect(const Ray & ray) const {
    // Vec3 from ray origin to circle origin
    Vec3 oc = ray.origin - origin;

    // All the below as in the quadratic equation
    double a = ray.direction.length_squared();
    double half_b = dot(oc, ray.direction);
    double c = oc.length_squared() - radius*radius;
    double quarter_discriminant = half_b*half_b - a*c;

    Hit hit;
    hit.occurred = quarter_discriminant > 0;
    if (hit.occurred) {
        double distance = (-half_b - sqrt(quarter_discriminant))/a;
        // if (distance < 0) {
        //     distance = (-half_b + sqrt(quarter_discriminant))/a;
        // }
        hit.distance = distance;
        hit.normal = unit_vector(ray.origin + hit.distance * ray.direction - origin);
        hit.material = material;
    }
    
    return hit;
}

std::shared_ptr<Material> Sphere::get_material() const {
    return material;
}

#endif