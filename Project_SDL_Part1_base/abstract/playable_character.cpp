#include "../application.h"

void playable_character::move()
{
    set_speed(5);
    int speed = get_speed();
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == 'q')
                set_x(get_x() - speed);
            if (event.key.keysym.sym == 'd')
                set_x(get_x() + speed);
            if (event.key.keysym.sym == 'z')
                set_y(get_y() - speed);
            if (event.key.keysym.sym == 's')
                set_y(get_y() + speed);
            break;
        default:
            break;
        }
    }
}