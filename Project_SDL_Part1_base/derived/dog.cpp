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
    setAlive(true);
    setPrey(false);
    setPredator(false);
    set_type(DOG);

    angle = (rand() * 10 % 360) * ((rand() % 2 == 0) ? -1 : 1);
    inc = 5 * ((rand() % 2 == 0) ? -1 : 1);
}

void dog::interact_with_object(std::shared_ptr<moving_object> obj)
{
    if (obj->get_type() == SHEPHERD)
    {
        int t_x = obj->get_x();
        int t_y = obj->get_y();
        int x = get_x();
        int y = get_y();
        int radius = 100;

        if (angle == 360 || angle == -360)
            angle = 0;
        float r_angle = angle * 3.14159 / 180;

        const float c = cos(r_angle);
        const float s = sin(r_angle);

        // Handle bounderies with rotations
        if ((y < frame_boundary && ((inc > 0 && c < 0) || (inc < 0 && c > 0)))
            || (y > frame_height - frame_boundary
                && ((inc > 0 && c > 0) || (inc < 0 && c < 0)))
            || ((x < frame_boundary
                 && ((inc < 0 && s < 0) || (inc > 0 && s > 0)))
                || (x > frame_width - frame_boundary
                    && ((inc < 0 && s > 0) || (inc > 0 && s < 0)))))
            inc *= -1;

        angle += inc;
        r_angle = angle * 3.14159 / 180;
        set_flip(((inc > 0 && s > 0) || (inc < 0 && s < 0))
                     ? SDL_FLIP_NONE
                     : SDL_FLIP_HORIZONTAL);
        set_x(t_x + cos(r_angle) * radius + obj->get_w() / 4);
        set_y(t_y + sin(r_angle) * radius + obj->get_h() / 3);
    }
}

void dog::move()
{}