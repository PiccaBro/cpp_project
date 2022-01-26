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
    SDL_Rect r = rect;
    r.x += rect.w / 2;
    r.y += rect.h / 2;
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &r);
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
