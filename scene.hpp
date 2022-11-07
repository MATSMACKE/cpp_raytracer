#ifndef SCENE_H
#define SCENE_H

#define MAX_BOUNCES 12

#include <vector>
#include <iostream>
#include <cmath>

#include "object.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "util.hpp"

class Scene {
    public:
        void add_object(Object * obj) {
            objects.push_back(obj);
        }

        Hit get_hit(const Ray & ray) const {
            Hit closest_hit;
            closest_hit.occurred = false;
            closest_hit.distance = INFINITY;

            for (auto object : objects) {
                Hit hit = object->intersect(ray);
                if (hit.occurred && hit.distance < closest_hit.distance && hit.distance > 0) {
                    closest_hit = hit;
                }
            }

            return closest_hit;
        }

        Vec3 cast_ray(Ray * ray) const {
            Vec3 light (-0.5, -0.4, -0.2);

            Vec3 attenuation = Vec3(1, 1, 1);

            bool use_ray = true; // Whether to use the ray immediately

            for (int i = 0; i < MAX_BOUNCES; i++) {
                Hit hit = get_hit(*ray);

                if (hit.occurred && hit.distance > 0.001) { 
                    hit.material->scatter(hit, ray, &attenuation);     
                } else if (i != 0) {
                    return attenuation * dot(ray->direction, light);
                } else {
                    return Vec3(0, 0, 0);
                }
            }
            return Vec3(0, 0, 0);
        }

        int num_objects() {
            return objects.size();
        }

        ~Scene() {
            for (auto obj : objects) {
                delete obj;
            }
        }

    private:
        std::vector<Object*> objects;
};

#endif