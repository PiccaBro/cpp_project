#include "../application.h"

void playable_character::move()
{
    SDL_Event event;
    int x, y, speed_x, speed_y;
    get_xy(&x, &y);
    get_xy_speed(&speed_x, &speed_y);

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
            set_xy(x - speed_x, y, true);
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            set_flip(SDL_FLIP_HORIZONTAL);
            set_xy(x + speed_x, y, true);
            break;
        case SDLK_z:
        case SDLK_UP:
            set_xy(x, y - speed_y, true);
            break;
        case SDLK_s:
        case SDLK_DOWN:
            set_xy(x, y + speed_y, true);
            break;
        default:
            break;
        }
    }
}