#include "application.h"

/*
  +=====================================================+
  |                       ANIMAL                        |
  +=====================================================+
*/

animal::animal(const std::string &file_path, SDL_Surface *window_surface_ptr)
{
    image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    window_surface_ptr_ = window_surface_ptr;

    // initial position of the animal
    rect.x = (rand() % (frame_width - (2 * frame_boundary))) + frame_boundary;
    rect.y = (rand() % (frame_height - (2 * frame_boundary))) + frame_boundary;

    speed = 5;
    x_speed = (rand() % speed) * ((rand() % 2 == 0) ? -1 : 1);
    y_speed =
        sqrt(pow(speed, 2) - pow(x_speed, 2)) * ((rand() % 2 == 0) ? -1 : 1);
}

animal::~animal()
{
    SDL_FreeSurface(image_ptr_);
    SDL_FreeSurface(window_surface_ptr_);
}

void animal::draw()
{
    SDL_Rect r = rect;
    r.x += rect.w / 2;
    r.y += rect.h / 2;
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &r);
}

// GETTERS
int animal::get_x()
{
    return rect.x;
}
int animal::get_y()
{
    return rect.y;
}
int animal::get_speed()
{
    return speed;
}
int animal::get_x_speed()
{
    return x_speed;
}
int animal::get_y_speed()
{
    return y_speed;
}
int animal::get_radius()
{
    return radius;
}

// SETTERS
void animal::set_x_speed(int speed)
{
    x_speed = speed;
}
void animal::set_y_speed(int speed)
{
    y_speed = speed;
}
void animal::set_x(int x)
{
    rect.x = x;
}
void animal::set_y(int y)
{
    rect.y = y;
}
void animal::set_rect(unsigned h, unsigned w)
{
    rect.h = h;
    rect.w = w;
}
void animal::set_radius(int radius)
{
    this->radius = radius;
}