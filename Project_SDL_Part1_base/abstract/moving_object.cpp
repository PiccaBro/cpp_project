#include "../application.h"

/*
  +=====================================================+
  |                       OBJECT                        |
  +=====================================================+
*/

moving_object::moving_object(const std::string &file_path,
                             SDL_Renderer *renderer)
    : rendered_object(file_path, renderer)
{
    speed = 0;
    x_speed = 0;
    y_speed = 0;
    dist = max_dist;
    hunted = false;
    interact = NULL;
}

// GETTERS
int moving_object::get_speed()
{
    return speed;
}
int moving_object::get_x_speed()
{
    return x_speed;
}
int moving_object::get_y_speed()
{
    return y_speed;
}
int moving_object::get_dist()
{
    return dist;
}
bool moving_object::is_hunted()
{
    return hunted;
}

// SETTERS
void moving_object::set_speed(int speed)
{
    this->speed = speed;
}
void moving_object::set_x_speed(int speed)
{
    x_speed = speed;
}
void moving_object::set_y_speed(int speed)
{
    y_speed = speed;
}
void moving_object::set_dist(int d)
{
    dist = d;
}
void moving_object::set_hunted(bool hunted)
{
    this->hunted = hunted;
}
