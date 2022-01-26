#include "../application.h"

/*
  +=====================================================+
  |                       SHEPHERD                      |
  +=====================================================+
*/

shepherd::shepherd(const std::string &file, SDL_Surface *window_surface)
    : playable_character(file, window_surface)
{
    set_rect(71, 67);
    set_x_speed(5);
    set_y_speed(5);
}
