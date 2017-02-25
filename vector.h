//
// Created by robin on 2/20/17.
//

#ifndef LEC_3_VECTOR_H
#define LEC_3_VECTOR_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

struct s_vec2;
struct s_mat2;
typedef struct s_vec2 vec2;
typedef struct s_mat2 mat2;

/**
 * The Matrix structure.
 */
struct s_mat2 {
    float x1, x2, x3,
            y1, y2, y3,
            w1, w2, w3;

    // Constructors
    s_mat2();

    s_mat2(vec2);

    s_mat2(vec2, float);

    s_mat2(float, float, float);

    s_mat2(float x1, float x2, float x3,
           float y1, float y2, float y3,
           float w1, float w2, float w3);

	mat2 operator*(float);
    vec2 operator*(vec2);
    mat2 operator*(mat2);

	mat2 operator+(mat2);
	mat2 operator-(mat2);
};

/**
 * The Vector2D structure.
 */
struct s_vec2 {
    float x, y, w;

    vec2 operator+(const vec2 &v);

    vec2 operator+=(const vec2 &v);

    vec2 operator*(mat2);
};

// ================ HELPER FUNCTIONS ================
mat2 scale(float);

mat2 scale(float, float);

mat2 rotate(float);

mat2 translate(float, float);

mat2 translate(vec2);
// ==================================================

struct rectangle {
    vec2 *v_points;
    // Point count is the vector count + 1,
    // since we need to connect our first and last vector.
    int point_count;

    const SDL_Point *to_point_array() const {
        SDL_Point *points = new SDL_Point[point_count];
        for (int i = 0; i < point_count - 1; i++) {
            points[i] = {(int) v_points[i].x, (int) v_points[i].y};
        }
        points[point_count - 1] = {(int) v_points[0].x, (int) v_points[0].y};
        return points;
    }
};

inline void render_rectangle(SDL_Renderer &renderer, const rectangle &r) {
    const SDL_Point *points = r.to_point_array();
    SDL_RenderDrawLines(&renderer, points, r.point_count);
}

#endif //LEC_3_VECTOR_H
