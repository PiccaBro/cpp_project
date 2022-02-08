#include "../application.h"

/*
  +=====================================================+
  |                         WOLF                        |
  +=====================================================+
*/

wolf::wolf(const std::string &file, SDL_Surface *window_surface)
    : animal(file, window_surface)
{
    set_rect(42, 62);
    set_type(WOLF);
    set_speed(6);
    setStamina(20);
    setMaxStamina(20);
    setSex(false);
    setAlive(true);
    setPrey(false);
    setPredator(true);
}

void wolf::move()
{
    set_x(get_x() + get_x_speed());
    set_y(get_y() + get_y_speed());

    float stamina = getStamina();
    if (stamina > 0)
        setStamina(stamina - 0.1);
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
    if (obj->isPrey() && d <= get_dist())
    {
        if (d < 5)
        {
            obj->setAlive(false);
            setStamina(getMaxStamina());
            return;
        }
        set_dist(d);
        set_x_speed(((target_x - x) * speed) / d);
        set_y_speed(((target_y - y) * speed) / d);
    }
}