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
    SDL_Point target;
    dist = max_dist;
    hunted = false;
    interact = NULL;
    choosen = false;
    ordered = false;
    go_back = false;
}

// GETTERS
void moving_object::get_speed(int *speed)
{
    *speed = this->speed;
}
void moving_object::get_xy_speed(int *speed_x, int *speed_y)
{
    *speed_x = x_speed;
    *speed_y = y_speed;
}

void moving_object::get_target(SDL_Point *target)
{
    *target = this->target;
}

int moving_object::get_dist()
{
    return dist;
}
bool moving_object::is_hunted()
{
    return hunted;
}

bool moving_object::is_choosen()
{
    return choosen;
}

bool moving_object::is_ordered()
{
    return ordered;
}

bool moving_object::is_going_back()
{
    return go_back;
}

// SETTERS
void moving_object::set_speed(int speed)
{
    this->speed = speed;
}
void moving_object::set_xy_speed(int speed_x, int speed_y)
{
    x_speed = speed_x;
    y_speed = speed_y;
}

void moving_object::set_dist(int d)
{
    dist = d;
}
void moving_object::set_hunted(bool hunted)
{
    this->hunted = hunted;
}

void moving_object::set_choosen(bool choosen)
{
    this->choosen = choosen;
}

void moving_object::set_target(int x, int y)
{
    target.x = x;
    target.y = y;
    ordered = x > 0;
}

void moving_object::set_go_back(int x, int y)
{
    target.x = x;
    target.y = y;
    go_back = x > 0;
}
