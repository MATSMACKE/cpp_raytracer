#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <functional>

class Vec3 {
    public:
        Vec3() : raw{0, 0, 0} {}
        Vec3(double x, double y, double z) : raw{x, y, z} {}

        double x() const {return raw[0];}
        double y() const {return raw[1];}
        double z() const {return raw[2];}

        Vec3 operator-() const {return Vec3(-raw[0], -raw[1], -raw[2]);}
        
        Vec3& operator+=(const Vec3 &v) {
            raw[0] += v.raw[0];
            raw[1] += v.raw[1];
            raw[2] += v.raw[2];
            return *this;
        }

        Vec3& operator*=(const double t) {
            raw[0] *= t;
            raw[1] *= t;
            raw[2] *= t;
            return *this;
        }

        Vec3& operator*=(const Vec3 v) {
            raw[0] *= v.x();
            raw[1] *= v.y();
            raw[2] *= v.z();
            return *this;
        }

        Vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return raw[0]*raw[0] + raw[1]*raw[1] + raw[2]*raw[2];
        }
        
        bool near_zero() const {
            // Return true if the vector is close to zero in all dimensions.
            const auto s = 1e-8;
            return (fabs(raw[0]) < s) && (fabs(raw[1]) < s) && (fabs(raw[2]) < s);
        }

        Vec3 map(std::function<double(double)> fn) {
            for (int i = 0; i < 3; i++) {
                raw[i] = fn(raw[i]);
            }
            return *this;
        }
    private:
        double raw[3];
};

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << '(' << v.x() << ' ' << v.y() << ' ' << v.z() << ')';
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.x(), t*v.y(), t*v.z());
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v) {
    return u.x() * v.x()
         + u.y() * v.y()
         + u.z() * v.z();
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * dot(v, n) * n;
}

using Point3 = Vec3;

#endif