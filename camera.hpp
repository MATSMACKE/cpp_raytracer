#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <iostream>

#include "color.hpp"
#include "scene.hpp"
#include "image.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "util.hpp"

class Camera {
    public:
        Camera(double width, double height, double fov, int samples) : width(width), height(height), fov(fov), samples(samples) {}

        Image render_scene(const Scene & scene, double width, double height) {
            Image img = Image(width, height);

            for (int y = 0; y < height; y++) {
                // std::cerr << "Line " << y << std::endl;
                for (int x = 0; x < width; x++) {
                    img.set_color(render_pixel(scene, x, y), x, y);
                }
            }

            return img;
        }

        Color render_pixel(const Scene & scene, int x, int y) {
            Vec3 pixel_color = Vec3(0, 0, 0);

            for (int i = 0; i < samples; i++) {
                float camera_direction_x = (2*(x + random_double())/(float)width - 1)*tan(fov/2.);
                float camera_direction_y = (2*(y + random_double())/(float)height - 1)*tan(fov/2.)*height/width;

                Ray ray (Vec3(0, 0, -10), unit_vector(Vec3(camera_direction_x, camera_direction_y, 1)));

                bool intersect;
                double distance;

                Vec3 value = scene.cast_ray(&ray);

                pixel_color += value;
            }


            
            Vec3 shaded = pixel_color.map([=](double val) {return 255 * sqrt(val / samples);});

            return Color(shaded.x(), shaded.y(), shaded.z());
        

        }

        void set_fov(double val) {
            fov = val;
        }

    private:
        double fov;
        double width;
        double height;
        int samples;
};

#endif