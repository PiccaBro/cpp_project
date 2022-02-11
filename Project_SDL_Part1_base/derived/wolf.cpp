#include "../application.h"

/*
  +=====================================================+
  |                         WOLF                        |
  +=====================================================+
*/

wolf::wolf(const std::string &file, SDL_Renderer *renderer)
    : animal(file, renderer)
{
    set_rect(63, 93, false);
    set_type(WOLF);
    set_speed(5 + rand() % 2);
    setStamina(30, false);
    setMaxStamina(30);
    setSex(false);
    setBirth(false);
    setAlive(true);
    setPrey(false);
    setPredator(true);
}

void wolf::move()
{
    int x, y, speed_x, speed_y;
    get_xy(&x, &y);
    get_xy_speed(&speed_x, &speed_y);
    set_xy(x + speed_x, y + speed_y);

    set_flip((speed_x < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    int stamina = getStamina();
    if (stamina > 0)
        setStamina(stamina - 1, true);
    else
        setAlive(false);
}

void wolf::interact_with_object(std::shared_ptr<moving_object> obj)
{
    int x, y, target_x, target_y, speed_x, speed_y, speed;
    get_xy(&x, &y);
    obj->get_xy(&target_x, &target_y);

    get_speed(&speed);
    int d = distance(x, y, target_x, target_y);
    if (obj->get_type() == DOG && d < 100 && d <= get_dist())
    {
        set_hunted(true);
        set_xy_speed(-((target_x - x) * speed) / d,
                     -((target_y - y) * speed) / d);
        return;
    }
    if (obj->isPrey() && d <= get_dist() && !is_hunted())
    {
        if (d < 5)
        {
            obj->setAlive(false);
            setStamina(getMaxStamina(), false);
            return;
        }
        set_dist(d);
        set_xy_speed(((target_x - x) * speed) / d,
                     ((target_y - y) * speed) / d);
    }
}