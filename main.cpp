#include <iostream>
#include <math.h>

#ifdef __linux__
#include "SDL/SDL.h"
#elif _WIN32
#include <SDL\SDL.h>
#endif

#include "vector.h"

int pos_x = 100, pos_y = 200, size_x = 800, size_y = 600, count = 4;

SDL_Window *window;
SDL_Renderer *renderer;
rectangle rectangle1, rectangle2;

void render() {
    SDL_RenderClear(renderer);

    // Set color for first rectangle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    render_rectangle(*renderer, rectangle1);

    // Set color for second rectangle
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    render_rectangle(*renderer, rectangle2);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderPresent(renderer);
}


bool init_sdl() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << " Failed to open SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool create_window() {
    window = SDL_CreateWindow("Lecture 3", pos_x, pos_y, size_x, size_y, 0);

    if (!window) {
        std::cout << " Failed to open window: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool create_renderer() {
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cout << " Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void setup_renderer() {
    // Set size of renderer to the same as window
    SDL_RenderSetLogicalSize(renderer, size_x, size_y);

    // Set color of renderer to green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
}

// Render loop
void render_screen() {
    bool loop = true;

    while (loop) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                loop = false;
        }

        render();

        SDL_Delay(16);
    }
}

// Initializes our window, renderer and sdl itself.
bool init_everything() {
    if (!init_sdl() || !create_window() || !create_renderer())
        return false;
    setup_renderer();
    return true;
}

int main(int argc, char *args[]) {
    // Create vector array
    vec2 vectors1[] = {
            {-20, -20, 1},
            {20,  -20, 1},
            {20,  20,  1},
            {-20, 20,  1},
    };

	vec2 test = { -20, -20, 1 };
    // Apply V = V * S * R * T
    for (int i = 0; i < count; i++) {
		vec2 current = vectors1[i];
        vectors1[i] = vectors1[i] * scale(5.0f) * rotate((float) M_PI/4) * translate(400.0f, 300.0f);
    }
    // Add vectors to rectangle struct, with count + 1.
    // We need count + 1, because we need to connect the last vector with the first.
    rectangle1 = {vectors1, count+1};


    vec2 vectors2[] = {
            {-20, -20, 1},
            {20,  -20, 1},
            {20,  20,  1},
            {-20, 20,  1},
    };

    // Apply V = V * S * T (no rotation)
    for (int i = 0; i < count; i++) {
        vectors2[i] = vectors2[i] * scale(7.0f) * translate(400.0f, 300.0f);
    }

    rectangle2 = {vectors2, count+1};

    // Initialize our window.
    if (!init_everything()) {
        return -1;
    }
    // Start the render loop.
    render_screen();
	
	// Let SDL clean the pointers.
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
    return 0;
}