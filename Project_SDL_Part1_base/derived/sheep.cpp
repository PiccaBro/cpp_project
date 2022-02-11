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
    int speed = 5;
    set_speed(speed);
    set_hunted(false);
    set_x_speed((rand() % speed) * ((rand() % 2 == 0) ? -1 : 1));
    set_y_speed(sqrt(pow(speed, 2) - pow(get_x_speed(), 2))
                * ((rand() % 2 == 0) ? -1 : 1));
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
        bool boundary_x = false;
        bool boundary_y = false;

        int d = distance(x, y, hunt_x, hunt_y);
        if (d < 200 && d <= get_dist())
        {
            set_dist(d);
            set_hunted(true);
            set_x_speed(-((hunt_x - x) * speed) / d);
            set_y_speed(-((hunt_y - y) * speed) / d);
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
    int x = get_x();
    int y = get_y();
    int speed = get_speed();
    bool hunted = is_hunted();
    int speed_x = get_x_speed();
    int speed_y = get_y_speed();
    float boost = 1.25;

    bool boundary_x = ((x < frame_boundary && speed_x < 0)
                       || (x > frame_width - frame_boundary && speed_x > 0));

    if (!hunted && boundary_x)
    {
        speed_x *= -1;
        set_x_speed(speed_x);
    }

    bool boundary_y = ((y <= frame_boundary && speed_y < 0)
                       || (y >= frame_height - frame_boundary && speed_y > 0));

    if (!hunted && boundary_y)
    {
        speed_y *= -1;
        set_y_speed(speed_y);
    }

    set_x(hunted ? (boundary_x ? x : x + speed_x * boost) : x + speed_x);
    set_y(hunted ? (boundary_y ? y : y + speed_y * boost) : y + speed_y);

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