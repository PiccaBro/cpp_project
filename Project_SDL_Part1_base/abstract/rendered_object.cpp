#include "../application.h"

/*
  +=====================================================+
  |                  RENDERED OBJECT                    |
  +=====================================================+
*/

rendered_object::rendered_object(const std::string &file_path,
                                 SDL_Renderer *renderer)
{
    rect.x = (rand() % (frame_width - (2 * frame_boundary))) + frame_boundary;
    rect.y = (rand() % (frame_height - (2 * frame_boundary))) + frame_boundary;
    flip = SDL_FLIP_NONE;
    this->renderer = renderer;
    texture = IMG_LoadTexture(renderer, file_path.c_str());
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

rendered_object::~rendered_object()
{
    SDL_DestroyTexture(texture);
}

void rendered_object::draw()
{
    // SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, flip);
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
void rendered_object::set_rect(unsigned h, unsigned w, bool random)
{
    if (!(random && rand() % 4))
    {
        rect.h = h;
        rect.w = w;
    }
}
void rendered_object::set_flip(SDL_RendererFlip flip)
{
    this->flip = flip;
}
