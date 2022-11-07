#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include <iostream>

class Color {
    public: 
        Color() : raw{0, 0, 0} {}
        Color(int r, int g, int b) : raw{r, g, b} {
            for (int & val : raw) {
                val = std::clamp(val, 0, 255);
            }
        }

        int r() const {return raw[0];}
        int g() const {return raw[1];}
        int b() const {return raw[2];}

    private:
        int raw[3];
};

inline std::ostream& operator<<(std::ostream& out, const Color & c) {
    return out << static_cast<int>(c.r()) << " " << static_cast<int>(c.g()) << " " << static_cast<int>(c.b());
}

#endif