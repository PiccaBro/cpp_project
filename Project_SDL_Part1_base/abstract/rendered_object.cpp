#include "../application.h"

/*
  +=====================================================+
  |                  RENDERED OBJECT                    |
  +=====================================================+
*/

rendered_object::rendered_object(const std::string &file_path,
                                 SDL_Surface *window_surface_ptr)
{
    image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    window_surface_ptr_ = window_surface_ptr;

    // initial position of the rendered_object
    rect.x = (rand() % (frame_width - (2 * frame_boundary))) + frame_boundary;
    rect.y = (rand() % (frame_height - (2 * frame_boundary))) + frame_boundary;
}

rendered_object::~rendered_object()
{
    SDL_FreeSurface(image_ptr_);
}

void rendered_object::draw()
{
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &rect);
}

// GETTERS
int rendered_object::get_x()
{
    return rect.x;
}
int rendered_object::get_y()
{
    return rect.y;
}

int rendered_object::get_h()
{
    return rect.h;
}

int rendered_object::get_w()
{
    return rect.w;
}

// SETTERS

void rendered_object::set_x(int x)
{
    rect.x = x;
}
void rendered_object::set_y(int y)
{
    rect.y = y;
}
void rendered_object::set_rect(unsigned h, unsigned w)
{
    rect.h = h;
    rect.w = w;
}
