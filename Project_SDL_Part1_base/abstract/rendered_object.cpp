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
    bound_x = false;
    bound_y = false;
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
void rendered_object::get_xy(int *x, int *y)
{
    *x = rect.x;
    *y = rect.y;
}

void rendered_object::get_dim(int *h, int *w)
{
    *h = rect.h;
    *w = rect.w;
}

void rendered_object::get_bounds(bool *bound_x, bool *bound_y)
{
    *bound_x = this->bound_x;
    *bound_y = this->bound_y;
}

// SETTERS

void rendered_object::set_xy(int x, int y, bool bounded)
{
    if (bounded)
    {
        if (x < frame_boundary)
        {
            bound_x = true;
            x = frame_boundary;
        }
        else if (x > frame_width - frame_boundary)
        {
            bound_x = true;
            x = frame_width - frame_boundary;
        }
        else
            bound_x = false;
    }
    rect.x = x;
    if (bounded)
    {
        if (y < frame_boundary)
        {
            bound_y = true;
            y = frame_boundary;
        }
        else if (y > frame_height - frame_boundary)
        {
            bound_y = true;
            y = frame_height - frame_boundary;
        }
        else
            bound_y = false;
    }
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
