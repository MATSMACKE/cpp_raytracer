#ifndef IMAGE_H
#define IMAGE_H

#include "color.hpp"

#include <vector>

class Image {
    public:
        Image(unsigned int width, unsigned int height) : w(width), h(height) {
            pixels = std::vector<Color>(width*height);

            std::fill(pixels.begin(), pixels.end(), Color(0, 0, 0));
        }

        void set_color(const Color& c, unsigned int x, unsigned int y) {
            pixels.at(get_px_index(x, y)) = c;
        }

        void write_image(std::ostream & out) {
            out << "P3\n" << w << ' ' << h << "\n255\n";

            for (auto pixel : pixels) {
                out << pixel << std::endl;
            }
        }

        unsigned int width() {return w;}
        unsigned int height() {return h;}

    private:
        unsigned int w;
        unsigned int h;
        std::vector<Color> pixels;

        /// @brief Get the index of a pixel at location (x, y)
        unsigned int get_px_index(unsigned int x, unsigned int y) {
            return w * y + x;
        }
};

#endif