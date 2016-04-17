#include <iostream>
#include <unistd.h>
#include "primitives.hpp"
#include "inputhandler.hpp"

#include <SDL2/SDL.h>

using namespace std;

#define WINDOW_W 600
#define WINDOW_H 400

SDL_Renderer* renderer     = nullptr;
SDL_Window*   window       = nullptr;
volatile bool quit         = false;

inline void
PollEvents(InputHandler& input) {
    static SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            input.press(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            input.release(event.key.keysym.sym);
            break;
        }
    }
}

inline void
SetRenderColor(color_t color) {
    static color_t render_color = black;
    if(render_color != color) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        render_color = color;
    }
}

inline void
clear() {
    SetRenderColor(black);
    SDL_RenderClear(renderer);
}

inline void
display() {
    SDL_RenderPresent(renderer);
}

void
setPixel(int x, int y, color_t color) {
    SetRenderColor(color);
    SDL_RenderDrawPoint(renderer, x, y);
}


int
main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WINDOW_W, WINDOW_H, 0, &window, &renderer);
    SetRenderColor(black);
    SDL_RenderClear(renderer);

    InputHandler input;
    point2_t line_start = {400, 50},
            line_end   = {500, 350};

    Line line1(point2_t(110, 10), point2_t(200, 10), red);
    Line line2(point2_t(110, 20), point2_t(200, 20), green);

    auto HandleInput = [&]() -> void {
        if(input.is_pressed(SDLK_RIGHT)) {
            line1.start().x += 3;
            line1.end().x   += 3;
            line2.start().x += 3;
            line2.end().x   += 3;

        }

        if(input.is_pressed(SDLK_LEFT)) {
            line1.start().x -= 3;
            line1.end().x   -= 3;
            line2.start().x -= 3;
            line2.end().x   -= 3;
        }

        if(input.is_pressed(SDLK_DOWN)) {
            line1.start().y += 3;
            line1.end().y   += 3;
            line2.start().y += 3;
            line2.end().y   += 3;
        }

        if(input.is_pressed(SDLK_UP)) {
            line1.start().y -= 3;
            line1.end().y   -= 3;
            line2.start().y -= 3;
            line2.end().y   -= 3;
        }

        if(input.is_pressed(SDLK_e)) {
            line1.rotate(5);
            line2.rotate(5);
        }

    };

    while(!quit) {
        PollEvents(input);
        HandleInput();

        clear();

        line1.draw();
        line2.draw();

        display();

        usleep(1000000/60);
    }

}
