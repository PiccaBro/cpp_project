#include "../application.h"

/**
 * @brief Construct a new rendered object
 *
 * @param file_path the path to the texture
 * @param renderer the renderer of the window
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

/**
 * @brief Destroy the rendered object and its texture
 *
 */
rendered_object::~rendered_object()
{
    SDL_DestroyTexture(texture);
}

/**
 * @brief draw the rendered object on the renderer with his texture and the good
 * flip
 */
void rendered_object::draw()
{
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, flip);
}

/**
 * @brief get the coordinates x and y of a object
 *
 * @param x the x component
 * @param y the y component
 */
void rendered_object::get_xy(int *x, int *y)
{
    *x = rect.x;
    *y = rect.y;
}

/**
 * @brief Get the dimension of a image
 *
 * @param h the height param
 * @param w the width param
 */
void rendered_object::get_dim(int *h, int *w)
{
    *h = rect.h;
    *w = rect.w;
}

/**
 * @brief To know if bounds x or y are touched
 *
 * @param bound_x true if bound x is touched
 * @param bound_y true if bound y is touched
 */
void rendered_object::get_bounds(bool *bound_x, bool *bound_y)
{
    *bound_x = this->bound_x;
    *bound_y = this->bound_y;
}

/**
 * @brief Set the point (x, y) on the ground
 *
 * @param x the x component
 * @param y the y component
 * @param bounded if the object need to be placed between the bounds
 */
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
/**
 * @brief Set the image dimensions
 *
 * @param h the height param
 * @param w the width param
 * @param random to make the change slower
 */
void rendered_object::set_rect(unsigned h, unsigned w, bool random)
{
    if (!(random && rand() % 4))
    {
        rect.h = h;
        rect.w = w;
    }
}

/**
 * @brief Set the flip mode of the image
 *
 * @param flip the flip mode
 */
void rendered_object::set_flip(SDL_RendererFlip flip)
{
    this->flip = flip;
}
