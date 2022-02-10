#include "../application.h"

/*
  +=====================================================+
  |                       SHEPHERD                      |
  +=====================================================+
*/

shepherd::shepherd(const std::string &file, SDL_Renderer *renderer)
    : playable_character(file, renderer)
{
    set_rect(128, 128, false);
    set_x_speed(5);
    set_type(SHEPHERD);
    set_y_speed(5);
    setAlive(true);
    setPrey(false);
    setPredator(false);
    setStamina(10, false);
    setMaxStamina(10);
    setBirth(false);
    setSex(false);
}
