#include "../application.h"

/*
  +=====================================================+
  |                         DOG                         |
  +=====================================================+
*/

dog::dog(const std::string &file, SDL_Renderer *renderer)
    : animal(file, renderer)
{
    set_rect(56, 62, false);
    setStamina(10, false);
    setMaxStamina(10);
    setSex(false);
    setBirth(false);
    setAlive(true);
    setPrey(false);
    setPredator(false);
    set_type(DOG);

    angle = (rand() % 360);
    inc = (3 + (rand() % 4)) * ((rand() % 2) ? -1 : 1);
    radius = 80 + (rand() % 50);
}

void dog::interact_with_object(std::shared_ptr<moving_object> obj)
{
    if (obj->get_type() == SHEPHERD)
    {
        int x = get_x();
        int y = get_y();

        angle %= 360;
        float r_angle = angle * 3.14159 / 180;

        const float c = cos(r_angle);
        const float s = sin(r_angle);

        angle += inc;
        r_angle = angle * 3.14159 / 180;
        // Handle flip depending on direction
        set_flip(((inc > 0 && s > 0) || (inc < 0 && s < 0))
                     ? SDL_FLIP_NONE
                     : SDL_FLIP_HORIZONTAL);
        set_x(obj->get_x() + cos(r_angle) * radius + obj->get_w() / 4);
        set_y(obj->get_y() + sin(r_angle) * radius + obj->get_h() / 3);
    }
}

void dog::move()
{}