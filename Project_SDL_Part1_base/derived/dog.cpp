#include "../application.h"

/*
  +=====================================================+
  |                         DOG                         |
  +=====================================================+
*/

dog::dog(const std::string &file, SDL_Surface *window_surface)
    : animal(file, window_surface)
{
    set_rect(42, 62);
    set_type(DOG);
    set_x_speed(5);
    set_y_speed(5);
}

void dog::move()
{
    int x = get_x();
    int y = get_y();
    int speed_x = get_x_speed();
    int speed_y = get_y_speed();
    if ((y < frame_boundary && speed_y < 0)
        || (y > frame_height - frame_boundary && speed_y > 0))
        set_y_speed(speed_y * (-1));
    set_y(y + speed_y);
    if ((x < frame_boundary && speed_x < 0)
        || (x > frame_width - frame_boundary && speed_x > 0))
        set_x_speed(speed_x * (-1));
    set_x(x + speed_x);
}
