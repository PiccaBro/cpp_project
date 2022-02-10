#include "../application.h"

void playable_character::move()
{
    int x_speed = get_x_speed();
    int y_speed = get_y_speed();
    int x = get_x();
    int y = get_y();

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
            if (x > frame_boundary)
                set_x(get_x() - x_speed);
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            set_flip(SDL_FLIP_HORIZONTAL);
            if (x < frame_width - frame_boundary)
                set_x(get_x() + x_speed);
            break;
        case SDLK_z:
        case SDLK_UP:
            if (y > frame_boundary)
                set_y(get_y() - y_speed);
            break;
        case SDLK_s:
        case SDLK_DOWN:
            if (y < frame_height - frame_boundary)
                set_y(get_y() + y_speed);
            break;
        default:
            break;
        }
    }
}