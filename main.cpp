#define PI 3.141592653589793

#include <iostream>
#include <cmath>
#include <memory>

#include "camera.hpp"
#include "image.hpp"
#include "color.hpp"
#include "material.hpp"
#include "object.hpp"
#include "ray.hpp"
#include "scene.hpp"

int main() {
    int width =  400;
    int height = 400;

    Scene scene;

    std::shared_ptr<Material> blue = std::make_shared<Lambert>(Color(50, 150, 220));
    std::shared_ptr<Material> white = std::make_shared<Lambert>(Color(255, 255, 255));
    std::shared_ptr<Material> red = std::make_shared<Lambert>(Color(240, 30, 30));
    std::shared_ptr<Material> brown = std::make_shared<Lambert>(Color(80, 100, 50));
    std::shared_ptr<Material> green = std::make_shared<Lambert>(Color(150, 230, 80));
    std::shared_ptr<Material> mirror = std::make_shared<Metal>(0);
    std::shared_ptr<Material> matte_gold = std::make_shared<Metal>(Color(255, 210, 100), 0.6);
    std::shared_ptr<Material> glass = std::make_shared<Dialectric>(1.5, Color(240, 160, 255), 1);

    scene.add_object(new Sphere(Vec3(-12, 7.5, 25), 3, glass));
    scene.add_object(new Sphere(Vec3(-1, -2, 6), 1, red));
    scene.add_object(new Sphere(Vec3(2, -2, 10), 3, mirror));
    scene.add_object(new Sphere(Vec3(-4, -2, 10), 3, brown));
    scene.add_object(new Sphere(Vec3(-4, 3.5, 35), 7, blue));
    scene.add_object(new Sphere(Vec3(0, 0, 20), 10, green));
    scene.add_object(new Sphere(Vec3(20, 0, 30), 10, matte_gold));
    scene.add_object(new Sphere(Vec3(-40, -10, 60), 20, mirror));
    scene.add_object(new Sphere(Vec3(0, 10010, 20), 10000, white));

    Camera cam(width, height, PI / 2, 1000);

    Image img = cam.render_scene(scene, width, height);

    img.write_image(std::cout);
}