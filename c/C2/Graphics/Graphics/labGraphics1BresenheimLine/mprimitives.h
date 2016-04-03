#ifndef MPRIMITIVES_H
#define MPRIMITIVES_H
#include <stdint.h>
#include <algorithm>
#include <cstdlib>
#include <cmath>

namespace m_primitives {

struct point_t {
    constexpr
    point_t(int x, int y)
        : x(x), y(y) {}

    int x;
    int y;
};

struct color_t {
    color_t()
        : r(0), g(0), b(0) {}

    constexpr
    color_t(uint8_t r, uint8_t g, uint8_t b)
        : r(r), g(g), b(b) {}

    color_t& operator= (const color_t& b) {
        this->r = b.r;
        this->g = b.g;
        this->b = b.b;
        return *this;
    }

    bool operator == (const color_t& b) {
        return (this->r == b.r &&
                this->g == b.g &&
                this->b == b.b);
    }

    bool operator != (const color_t& b) {
        return !operator==(b);
    }

    uint8_t r;
    uint8_t g;
    uint8_t b;
};

constexpr color_t black (0,   0,   0);
constexpr color_t white (255, 255, 255);
constexpr color_t red   (255, 0,   0);
constexpr color_t green (0,   255, 0);
constexpr color_t blue  (0,   0,   255);


/* Any primitive-drwitg function sets pixels, so they use user-defined
 * setPixel(x,y,color) function */
extern void setPixel(int x, int y, color_t color);

/* @brief Draw line with Bresenham's algorithm */
inline void drawLine(point_t p0, point_t p1, color_t color) {
    int x0 = p0.x,
        y0 = p0.y,
        x1 = p1.x,
        y1 = p1.y;

    int dx = (x1 - x0 >= 0 ? 1 : -1);
    int dy = (y1 - y0 >= 0 ? 1 : -1);

    int lenX = abs(x1 - x0);
    int lenY = abs(y1 - y0);

    int length = std::max(lenX, lenY);

    if(length == 0) {
        setPixel(x0, y0, color);
    }

    if(lenY <= lenX) {
        int x = x0;
        int y = y0;
        int d = -lenX;

        length++;
        while(length--) {
            setPixel(x, y, color);
            x += dx;
            d += 2 * lenY;
            if(d > 0) {
                d -= 2 * lenX;
                y += dy;
            }
        }
    } else {
        int x = x0;
        int y = y0;
        int d = -lenY;

        length++;
        while(length--) {
            setPixel(x, y, color);
            y += dy;
            d += 2 * lenX;
            if(d > 0) {
                d -= 2* lenY;
                x += dx;
            }
        }
    }
}


}
#endif // MPRIMITIVES_H
