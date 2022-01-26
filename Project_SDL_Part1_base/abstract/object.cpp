#include "../application.h"

/*
  +=====================================================+
  |                       OBJECT                        |
  +=====================================================+
*/

object::object(const std::string &file_path, SDL_Surface *window_surface_ptr)
{
    image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    window_surface_ptr_ = window_surface_ptr;

    // initial position of the object
    rect.x = (rand() % (frame_width - (2 * frame_boundary))) + frame_boundary;
    rect.y = (rand() % (frame_height - (2 * frame_boundary))) + frame_boundary;
    speed = 0;
    x_speed = 0;
    y_speed = 0;
    /*
    speed = 5;
    x_speed = (rand() % speed) * ((rand() % 2 == 0) ? -1 : 1);
    y_speed =
        sqrt(pow(speed, 2) - pow(x_speed, 2)) * ((rand() % 2 == 0) ? -1 : 1);
    */
}

object::~object()
{
    SDL_FreeSurface(image_ptr_);
}

void object::draw()
{
    SDL_Rect r = rect;
    r.x += rect.w / 2;
    r.y += rect.h / 2;
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &r);
}

// GETTERS
int object::get_x()
{
    return rect.x;
}
int object::get_y()
{
    return rect.y;
}
int object::get_speed()
{
    return speed;
}
int object::get_x_speed()
{
    return x_speed;
}
int object::get_y_speed()
{
    return y_speed;
}

// SETTERS
void object::set_x_speed(int speed)
{
    x_speed = speed;
}
void object::set_speed(int speed)
{
    this->speed = speed;
}
void object::set_y_speed(int speed)
{
    y_speed = speed;
}
void object::set_x(int x)
{
    rect.x = x;
}
void object::set_y(int y)
{
    rect.y = y;
}
void object::set_rect(unsigned h, unsigned w)
{
    rect.h = h;
    rect.w = w;
}
