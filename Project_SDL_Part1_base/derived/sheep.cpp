#include "../application.h"

/*
  +=====================================================+
  |                        SHEEP                        |
  +=====================================================+
*/

sheep::sheep(const std::string &file, SDL_Renderer *renderer)
    : animal(file, renderer)
{
    set_rect(71, 67, false);
    setMaxStamina(20);
    setStamina(20, false);
    setSex(rand() % 2);
    setAlive(true);
    setPrey(true);
    setPredator(false);
    setBirth(false);
    set_type(SHEEP);
    int speed = 4 + rand() % 2;
    set_speed(speed);
    boost = 1.25;
    set_hunted(false);
    set_x_speed((rand() % speed) * ((rand() % 2) ? -1 : 1));
    set_y_speed(sqrt(pow(speed, 2) - pow(get_x_speed(), 2))
                * ((rand() % 2) ? -1 : 1));
}

void sheep::interact_with_object(std::shared_ptr<moving_object> obj)
{
    if (obj->isPredator())
    {
        int x = get_x();
        int y = get_y();
        int hunt_x = obj->get_x();
        int hunt_y = obj->get_y();
        int speed = get_speed();

        int d = distance(x, y, hunt_x, hunt_y);
        if (d < 200 && d <= get_dist())
        {
            set_dist(d);
            set_hunted(true);
            set_x_speed(-((hunt_x - x) * speed * boost) / d);
            set_y_speed(-((hunt_y - y) * speed * boost) / d);
        }
        return;
    }
    if (!is_hunted() && getSex() && !obj->getSex()
        && get_type() == obj->get_type() && getStamina() == getMaxStamina()
        && distance(get_x(), get_y(), obj->get_x(), obj->get_y()) < 20)
    {
        setStamina(0, false);
        setBirth(true);
    }
}
void sheep::move()
{
    bool hunted = is_hunted();
    int speed_x = get_x_speed();
    int speed_y = get_y_speed();

    set_x(get_x() + speed_x);
    set_y(get_y() + speed_y);

    if (!hunted)
    {
        if (get_bound_x())
            set_x_speed(speed_x * -1);
        if (get_bound_y())
            set_y_speed(speed_y * -1);
    }

    int stamina = getStamina();
    if (stamina < getMaxStamina())
        setStamina(stamina + 1, true);

    // grow
    int h = get_h();
    int w = get_w();
    if (h < 71 || w < 67)
    {
        if (w < 67)
            w++;
        if (h < 71)
            h++;
        set_rect(h, w, true);
    }
}

std::shared_ptr<moving_object> sheep::bear(SDL_Renderer *renderer)
{
    std::shared_ptr<moving_object> new_s =
        std::make_unique<sheep>("../media/sheep.png", renderer);
    new_s->set_x(get_x());
    new_s->set_y(get_y());
    new_s->setStamina(0, false);
    new_s->set_rect(43, 40, false);
    return new_s;
}