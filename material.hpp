#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>

#include "ray.hpp"
#include "util.hpp"
#include "color.hpp"

class Material {
    public:
        virtual void scatter(const Hit & hit, Ray * ray, Vec3 * attenuation) const = 0;
};

class Lambert : public Material {
    public:
        Lambert(double lightness) : albedo(Vec3(lightness, lightness, lightness)) {}
        Lambert(Vec3 albedo) : albedo(albedo) {}
        Lambert(Color albedo) : albedo(Vec3(albedo.r() / 255.0, albedo.g() / 255.0, albedo.b() / 255.0)) {}

        void scatter(const Hit & hit, Ray * ray, Vec3 * attenuation) const override {
            Vec3 point = ray->origin + hit.distance * ray->direction;
            Vec3 target = point + hit.normal + random_unit_in_unit_sphere();

            *ray = Ray(point, unit_vector(target - point));
            *attenuation *= albedo;
        }

    private:
        Vec3 albedo;
};

class Metal : public Material {
    public:
        Metal() : albedo(Vec3(1, 1, 1)), fuzz(0) {}
        Metal(double fuzz) : albedo(Vec3(1, 1, 1)), fuzz(fuzz) {}
        Metal(Color albedo, double fuzz) : albedo(Vec3(albedo.r() / 255.0, albedo.g() / 255.0, albedo.b() / 255.0)), fuzz(fuzz) {}

        void scatter(const Hit & hit, Ray * ray, Vec3 * attenuation) const override {
            Vec3 point = ray->origin + hit.distance * ray->direction;
            Vec3 target = point + reflect(ray->direction, hit.normal) + fuzz * random_in_unit_sphere();

            *ray = Ray(point, unit_vector(target - point));
            *attenuation *= albedo;
        }

    private:
        Vec3 albedo;
        double fuzz;
};

class Dialectric : public Material {
    public:
        Dialectric() : refract(1), albedo(Vec3(1, 1, 1)) {}
        Dialectric(double refract) : refract(refract), albedo(Vec3(1, 1, 1)) {}
        Dialectric(double refract, Vec3 albedo) : refract(refract), albedo(albedo) {}
        Dialectric(double refract, Color albedo) : refract(refract), albedo(Vec3(albedo.r() / 255.0, albedo.g() / 255.0, albedo.b() / 255.0)) {}
        Dialectric(double refract, Color albedo, double reflection) : refract(refract), albedo(Vec3(albedo.r() / 255.0, albedo.g() / 255.0, albedo.b() / 255.0)), reflection(reflection) {}

        void scatter(const Hit & hit, Ray * ray, Vec3 * attenuation) const override {
            Vec3 point = ray->origin + hit.distance * ray->direction;

            bool front_face = dot(hit.normal, ray->direction) < 0;
            Vec3 normal = front_face ? hit.normal : -hit.normal;
            double ratio = front_face ? 1.0/refract : refract;
            
            *attenuation *= albedo;

            double refraction_ratio = front_face ? (1.0/refract) : refract;

            double cos_theta = fmin(dot(-ray->direction, normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            Vec3 direction;

            if (cannot_refract || reflection * reflectance(cos_theta, refraction_ratio) > random_double())
                direction = reflect(ray->direction, normal);
            else
                direction = refract_ray(ray->direction, normal, refraction_ratio);

            *ray = Ray(point + direction * 0.01, direction);
        }

    private:
        double refract;
        Vec3 albedo;
        double reflection;

        static double reflectance(double cosine, double ref_idx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1-ref_idx) / (1+ref_idx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1 - cosine),5);
        }
};

#endif