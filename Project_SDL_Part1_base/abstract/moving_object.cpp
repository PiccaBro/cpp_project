#include "../application.h"

/*
  +=====================================================+
  |                       OBJECT                        |
  +=====================================================+
*/

moving_object::moving_object(const std::string &file_path,
                             SDL_Surface *window_surface_ptr)
    : rendered_object(file_path, window_surface_ptr)
{
    x_speed = 0;
    y_speed = 0;
}

// GETTERS
int moving_object::get_x_speed()
{
    return x_speed;
}
int moving_object::get_y_speed()
{
    return y_speed;
}

// SETTERS
void moving_object::set_x_speed(int speed)
{
    x_speed = speed;
}
void moving_object::set_y_speed(int speed)
{
    y_speed = speed;
}
