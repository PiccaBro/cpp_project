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

std::vector<std::shared_ptr<animal>> ground::get_animals()
{
    return animals;
}

void ground::add_animal(std::shared_ptr<animal> animal)
{
    animals.push_back(animal);
}

void ground::update(SDL_Window *window_ptr)
{
    if (SDL_FillRect(window_surface_ptr_, NULL,
                     SDL_MapRGB(window_surface_ptr_->format, 50, 188, 50))
        < 0)
        printf("%s\n", SDL_GetError());

    // sheeps update

    for (std::shared_ptr<animal> s : animals)
    {
        // s->run_from_wolf(wolves);
        s->move();
        s->draw();
        for (std::shared_ptr<animal> t : animals)
        {
            s->interact_with_animal(t);
        }
    }

    if (SDL_UpdateWindowSurface(window_ptr) < 0)
        printf("Update Surface failed\n");
}