#include "application.h"

/*
  +=====================================================+
  |                        SHEEP                        |
  +=====================================================+
*/

shepherd::shepherd(const std::string &file, SDL_Surface *window_surface)
    : playable_character(file, window_surface)
{
    set_rect(71, 67);
}

void shepherd::move()
{
    stay_on_screen();
}
void shepherd::interact_with_animal(std::shared_ptr<animal> target)
{}