//
// Created by robin on 2/20/17.
//

#include <cmath>
#include "vector.h"

vec2 s_vec2::operator+(const vec2 &v) {
    return {x + v.x, y + v.y, (float) ((w + v.w) == 2)};
}

vec2 s_vec2::operator+=(const vec2 &v) {
    x += v.x;
    y += v.y;
    w = (float) ((w + v.w) == 2);
    return *this;
}

vec2 s_vec2::operator*(mat2 m) {
    return m * (*this);
}

s_mat2::s_mat2() : s_mat2(1, 1, 1) {}

s_mat2::s_mat2(struct s_vec2 v) : s_mat2(v.x, v.y, 1) {}

s_mat2::s_mat2(struct s_vec2 v, float w) : s_mat2(v.x, v.y, w) {}

s_mat2::s_mat2(float x, float y, float w) : x1(x), x2(0), x3(0), y1(0), y2(y), y3(0), w1(0), w2(0), w3(w) {}

s_mat2::s_mat2(float x1, float x2, float x3,
               float y1, float y2, float y3,
               float w1, float w2, float w3) : x1(x1), x2(x2), x3(x3),
                                               y1(y1), y2(y2), y3(y3),
                                               w1(w1), w2(w2), w3(w3) {}

mat2 s_mat2::operator*(float f)
{
	return {
			x1*f, x2*f, x3*f,
			y1*f, y2*f, y3*f,
			w1*f, w2*f, w3*f
	};
}

vec2 s_mat2::operator*(vec2 v) {
    return  {
            v.x * x1 + v.y * x2 + v.w * x3,
            v.x * y1 + v.y * y2 + v.w * y3,
            v.x * w1 + v.y * w2 + v.w * w3
    };
}

mat2 s_mat2::operator*(mat2 m) {
    return {
            x1 * m.x1 + x2 * m.y1 + x3 * m.w1, x1 * m.x2 + x2 * m.y2 + x3 * m.w2, x1 * m.x3 + x2 * m.y3 + x3 * m.w3,
            y1 * m.x1 + y2 * m.y1 + y3 * m.w1, y1 * m.x2 + y2 * m.y2 + y3 * m.w2, y1 * m.x3 + y2 * m.y3 + y3 * m.w3,
            w1 * m.x1 + w2 * m.y1 + w3 * m.w1, w1 * m.x2 + w2 * m.y2 + w3 * m.w2, w1 * m.x3 + w2 * m.y3 + w3 * m.w3,
    };
}

mat2 s_mat2::operator+(mat2 m)
{
	return {
			x1 + m.x1, x2 + m.x2, x3 + m.x3,
			y1 + m.y1, y2 + m.y2, y3 + m.y3,
			w1 + m.w1, w2 + m.w2, w3 + m.w3
	};
}

mat2 s_mat2::operator-(mat2 m)
{
	return{
		x1 - m.x1, x2 - m.x2, x3 - m.x3,
		y1 - m.y1, y2 - m.y2, y3 - m.y3,
		w1 - m.w1, w2 - m.w2, w3 - m.w3
	};
}

mat2 scale(float f) {
    return mat2(f, f, 1);
}

mat2 scale(float x, float y) {
    return mat2(x, y, 1);
}

mat2 rotate(float f) {
    return {
            std::cos(f), -(std::sin(f)), 0,
            std::sin(f), std::cos(f), 0,
            0, 0, 1
    };
}

mat2 translate(float x, float y) {
    return {
            1, 0, x,
            0, 1, y,
            0, 0, 1
    };
}

mat2 translate(vec2 v) {
    return translate(v.x, v.y);
}
