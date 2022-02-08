#include "../application.h"

/*
  +=====================================================+
  |                        SHEEP                        |
  +=====================================================+
*/

sheep::sheep(const std::string &file, SDL_Surface *window_surface)
    : animal(file, window_surface)
{
    set_rect(71, 67, false);
    setMaxStamina(10);
    setStamina(10, false);
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
            int speed_x = get_x_speed();
            int speed_y = get_y_speed();

            if ((x < frame_boundary && speed_x < 0)
                || (x > frame_width - frame_boundary && speed_x > 0))
            {
                boundary_x = true;
            }
            if ((y <= frame_boundary && speed_y < 0)
                || (y >= frame_height - frame_boundary && speed_y > 0))
            {
                boundary_y = true;
            }

            if (!boundary_x)
                speed_x = -((hunt_x - x) * speed) / d;
            if (!boundary_y)
                speed_y = -((hunt_y - y) * speed) / d;

            set_x_speed(speed_x);
            set_y_speed(speed_y);
        }
        return;
    }
    if (getSex() && !obj->getSex() && get_type() == obj->get_type()
        && getStamina() == getMaxStamina()
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
    int speed_x = get_x_speed();
    int speed_y = get_y_speed();
    bool hunted = is_hunted();
    bool boundary_y = false;
    bool boundary_x = false;
    float boost = 1.25;

    if ((x < frame_boundary && speed_x < 0)
        || (x > frame_width - frame_boundary && speed_x > 0))
    {
        boundary_x = true;
        if (!hunted)
        {
            set_x_speed(speed_x *= -1);
            speed_x *= -1;
        }
    }

    if ((y <= frame_boundary && speed_y < 0)
        || (y >= frame_height - frame_boundary && speed_y > 0))
    {
        boundary_y = true;
        if (!hunted)
        {
            set_y_speed(speed_y *= -1);
            speed_y *= -1;
        }
    }

    set_x(hunted ? (boundary_x ? x : x + speed_x * boost) : x + speed_x);
    set_y(hunted ? (boundary_y ? y : y + speed_y * boost) : y + speed_y);

    int stamina = getStamina();
    if (stamina < getMaxStamina())
        setStamina(++stamina, true);

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