#include "application.h"

/*
  +=====================================================+
  |                       ANIMAL                        |
  +=====================================================+
*/

playable_character::playable_character(const std::string &file_path,
                                       SDL_Surface *window_surface_ptr)
{
    image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    window_surface_ptr_ = window_surface_ptr;

    // initial position of the playable_character
    rect.x = (rand() % (frame_width - (2 * frame_boundary))) + frame_boundary;
    rect.y = (rand() % (frame_height - (2 * frame_boundary))) + frame_boundary;

    speed = 5;
    x_speed = (rand() % speed) * ((rand() % 2 == 0) ? -1 : 1);
    y_speed =
        sqrt(pow(speed, 2) - pow(x_speed, 2)) * ((rand() % 2 == 0) ? -1 : 1);
}

playable_character::~playable_character()
{
    SDL_FreeSurface(image_ptr_);
}

void playable_character::draw()
{
    SDL_Rect r = rect;
    r.x += rect.w / 2;
    r.y += rect.h / 2;
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &r);
}
void playable_character::stay_on_screen()
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

// GETTERS
int playable_character::get_x()
{
    return rect.x;
}
int playable_character::get_y()
{
    return rect.y;
}
int playable_character::get_speed()
{
    return speed;
}
int playable_character::get_x_speed()
{
    return x_speed;
}
int playable_character::get_y_speed()
{
    return y_speed;
}

// SETTERS
void playable_character::set_x_speed(int speed)
{
    x_speed = speed;
}
void playable_character::set_y_speed(int speed)
{
    y_speed = speed;
}
void playable_character::set_x(int x)
{
    rect.x = x;
}
void playable_character::set_y(int y)
{
    rect.y = y;
}
void playable_character::set_rect(unsigned h, unsigned w)
{
    rect.h = h;
    rect.w = w;
}
