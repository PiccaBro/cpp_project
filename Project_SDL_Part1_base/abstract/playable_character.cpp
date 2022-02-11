#include "../application.h"

void playable_character::move()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            exit(0);
        if (event.type != SDL_KEYDOWN)
            continue;
        switch (event.key.keysym.sym)
        {
        case SDLK_q:
        case SDLK_LEFT:
            set_flip(SDL_FLIP_NONE);
            set_x(get_x() - get_x_speed());
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            set_flip(SDL_FLIP_HORIZONTAL);
            set_x(get_x() + get_x_speed());
            break;
        case SDLK_z:
        case SDLK_UP:
            set_y(get_y() - get_y_speed());
            break;
        case SDLK_s:
        case SDLK_DOWN:
            set_y(get_y() + get_y_speed());
            break;
        default:
            break;
        }
    }
}