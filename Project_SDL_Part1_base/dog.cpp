#include "application.h"

/*
  +=====================================================+
  |                         DOG                         |
  +=====================================================+
*/

dog::dog(const std::string &file, SDL_Surface *window_surface)
    : animal(file, window_surface)
{
    set_rect(42, 62);
    set_radius(300);
    set_type(DOG);
}

void dog::move()
{
    stay_on_screen();
}

void dog::interact_with_animal(std::shared_ptr<animal> target)
{}
