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
    set_speed(7 + rand() % 2);
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
    if (!is_ordered() && !is_going_back() && obj->get_type() == SHEPHERD)
    {
        int x, y, h, w;
        obj->get_xy(&x, &y);
        obj->get_dim(&h, &w);

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

        set_xy(x + cos(r_angle) * radius + w / 4,
               y + sin(r_angle) * radius + h / 3, true);
    }
}

void dog::move()
{
    int x, y, h, w, speed, limit, d;
    SDL_Point target;
    get_xy(&x, &y);
    get_dim(&h, &w);
    get_click(&target.x, &target.y);

    d = distance(x + w / 2, y + h / 2, target.x, target.y);
    if (is_ordered() && d < w)
    {
        set_ordered(false);
        set_go_back(x, y); // ask for back signal
        return;
    }
    if (is_going_back() && d <= radius)
    {
        angle = atan2(y - target.y, x - target.x) * 180
            / 3.14159; // synchro to circle around the shepherd
        inc *= rand() % 2 ? 1 : -1;
        set_go_back(-1, -1); // stop back signal
        target.x = -1; // reset target
        return;
    }
    if (is_ordered() || is_going_back())
    {
        get_speed(&speed);
        int speed_x = ((target.x - x) * speed) / d;
        int speed_y = ((target.y - y) * speed) / d;
        set_flip((speed_x > 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        set_xy(x + speed_x, y + speed_y, true);
    }
}