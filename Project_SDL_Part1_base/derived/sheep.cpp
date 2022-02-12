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
    int speed_x = (rand() % speed) * ((rand() % 2) ? -1 : 1);
    set_xy_speed(speed_x,
                 sqrt(pow(speed, 2) - pow(speed_x, 2))
                     * ((rand() % 2) ? -1 : 1));
}

void sheep::interact_with_object(std::shared_ptr<moving_object> obj)
{
    int x, y, hunt_x, hunt_y, speed;
    get_xy(&x, &y);
    obj->get_xy(&hunt_x, &hunt_y);
    if (obj->isPredator())
    {
        get_speed(&speed);

        int d = distance(x, y, hunt_x, hunt_y);
        if (d < 200 && d <= get_dist())
        {
            set_dist(d);
            set_hunted(true);
            set_xy_speed(-((hunt_x - x) * speed * boost) / d,
                         -((hunt_y - y) * speed * boost) / d);
        }
        return;
    }
    if (!is_hunted() && getSex() && !obj->getSex()
        && get_type() == obj->get_type() && getStamina() == getMaxStamina()
        && distance(x, y, hunt_x, hunt_y) < 30)
    {
        setStamina(0, false);
        setBirth(true);
    }
}
void sheep::move()
{
    bool bound_x, bound_y, hunted = is_hunted();
    int x, y, h, w, speed_x, speed_y;
    get_xy(&x, &y);
    get_xy_speed(&speed_x, &speed_y);

    set_xy(x + speed_x, y + speed_y, true);
    get_bounds(&bound_x, &bound_y);

    if (!hunted)
    {
        if (bound_x)
            speed_x *= -1;
        if (bound_y)
            speed_y *= -1;
        set_xy_speed(speed_x, speed_y);
    }

    int stamina = getStamina();
    if (stamina < getMaxStamina())
        setStamina(stamina + 1, true);

    // grow
    get_dim(&h, &w);
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
    int x, y;
    get_xy(&x, &y);
    new_s->set_xy(x, y, true);
    new_s->setStamina(0, false);
    new_s->set_rect(43, 40, false);
    return new_s;
}