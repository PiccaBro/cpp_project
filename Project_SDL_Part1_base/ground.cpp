#include "application.h"

/*
  +=====================================================+
  |                       GROUND                        |
  +=====================================================+
*/

ground::ground(SDL_Surface *window_surface_ptr)
{
    // Filling the surface with green color
    this->window_surface_ptr_ = window_surface_ptr;
}

ground::~ground()
{}

std::vector<std::shared_ptr<moving_object>> ground::get_objects()
{
    return moving_objects;
}

void ground::add_object(std::shared_ptr<moving_object> moving_object)
{
    moving_objects.push_back(moving_object);
}

void ground::update(SDL_Window *window_ptr)
{
    if (SDL_FillRect(window_surface_ptr_, NULL,
                     SDL_MapRGB(window_surface_ptr_->format, 50, 188, 50))
        < 0)
        printf("%s\n", SDL_GetError());

    // sheeps update

    for (std::shared_ptr<moving_object> s : moving_objects)
    {
        // s->run_from_wolf(wolves);
        s->move();
        s->draw();
    }

    if (SDL_UpdateWindowSurface(window_ptr) < 0)
        printf("Update Surface failed\n");
}