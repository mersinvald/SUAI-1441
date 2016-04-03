#include <iostream>
#include <unistd.h>
#include "mprimitives.h"
#include "inputhandler.hpp"

#include <SDL2/SDL.h>

using namespace m_primitives;
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
m_primitives::setPixel(int x, int y, color_t color) {
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
    point_t line_start = {400, 50},
            line_end   = {500, 350};

    auto HandleInput = [&]() -> void {
        if(input.is_pressed(SDLK_RIGHT)) {
            line_start.x += 1;
            line_end.x   += 1;
        }

        if(input.is_pressed(SDLK_LEFT)) {
            line_start.x -= 1;
            line_end.x   -= 1;
        }

        if(input.is_pressed(SDLK_DOWN)) {
            line_start.y += 1;
            line_end.y   += 1;
        }

        if(input.is_pressed(SDLK_UP)) {
            line_start.y -= 1;
            line_end.y   -= 1;
        }
    };

    std::vector< std::pair<point_t, point_t> > lines;
    lines.push_back(make_pair(point_t(110, 100), point_t(100, 150)));
    lines.push_back(make_pair(point_t(110, 100), point_t(120, 150)));
    lines.push_back(make_pair(point_t(95,  150), point_t(125, 150)));
    lines.push_back(make_pair(point_t(95,  150), point_t(97,  155)));
    lines.push_back(make_pair(point_t(125, 150), point_t(123, 155)));

    lines.push_back(make_pair(point_t(150, 100), point_t(140, 150)));
    lines.push_back(make_pair(point_t(150, 100), point_t(160, 150)));
    lines.push_back(make_pair(point_t(145, 130), point_t(155, 130)));

    lines.push_back(make_pair(point_t(180, 100), point_t(180, 150)));
    lines.push_back(make_pair(point_t(190, 100), point_t(190, 150)));
    lines.push_back(make_pair(point_t(200, 100), point_t(200, 150)));
    lines.push_back(make_pair(point_t(180, 150), point_t(200, 150)));

    lines.push_back(make_pair(point_t(230, 100), point_t(220, 150)));
    lines.push_back(make_pair(point_t(230, 100), point_t(240, 150)));
    lines.push_back(make_pair(point_t(225, 130), point_t(235, 130)));

    while(!quit) {
        PollEvents(input);
        HandleInput();

        clear();

        for(uint i = 0; i < lines.size(); i++) {
            drawLine(lines[i].first, lines[i].second, green);
        }


//        drawLine(line_start, line_end, green);
//        SetRenderColor(red);
//        SDL_RenderDrawLine(renderer,
//                           line_start.x - 300, line_start.y,
//                           line_end.x - 300, line_end.y);

        display();

        usleep(1000000/60);
    }

}
