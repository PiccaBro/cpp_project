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
    set_speed(6);
    setStamina(200, false);
    setMaxStamina(200);
    setSex(false);
    setAlive(true);
    setPrey(false);
    setPredator(true);
}

void wolf::move()
{
    int speed_x = get_x_speed();
    set_flip((speed_x < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    set_x(get_x() + speed_x);
    set_y(get_y() + get_y_speed());

    int stamina = getStamina();
    if (stamina > 0)
        setStamina(--stamina, true);
    else
        setAlive(false);
}

void wolf::interact_with_object(std::shared_ptr<moving_object> obj)
{
    int x = get_x();
    int y = get_y();
    int target_x = obj->get_x();
    int target_y = obj->get_y();
    int speed = get_speed();
    auto d = distance(get_x(), get_y(), obj->get_x(), obj->get_y());
    if (obj->get_type() == DOG && d < 200 && d <= get_dist())
    {
        set_hunted(true);
        set_x_speed(-((target_x - x) * speed) / d);
        set_y_speed(-((target_y - y) * speed) / d);
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
        set_x_speed(((target_x - x) * speed) / d);
        set_y_speed(((target_y - y) * speed) / d);
    }
}