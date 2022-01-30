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
    set_speed(5);
    setStamina(20);
    setMaxStamina(20);
    setSex(false);
    setAlive(true);
    setPrey(false);
    // target.x = -1;
    // target.y = -1;
    // target_dist = 0;
    // kill_radius = 20;
}

void wolf::move()
{
    set_x(get_x() + get_x_speed());
    set_y(get_y() + get_y_speed());

    float stamina = getStamina();
    if (stamina > 0)
    {
        setStamina(stamina - 0.1);
        // printf("wolf = %f\n", stamina);
    }
    else
        setAlive(false);
    /*
        int x = get_x();
        int y = get_y();
        int speed_x = get_x_speed();
        int speed_y = get_y_speed();
        if ((y < frame_boundary && speed_y < 0)
            || (y > frame_height - frame_boundary && speed_y > 0))
            set_y_speed(speed_y * (-1));
        set_y(y + speed_y);
        if ((x < frame_boundary && speed_x < 0)
            || (x > frame_width - frame_boundary && speed_x > 0))
            set_x_speed(speed_x * (-1));
        set_x(x + speed_x);
        */
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

/*
int wolf::chaise(std::vector<sheep *> sheeps)
{
    if (sheeps.size() == 0)
    {
        set_target_x(-1);
        return -1;
    }
    if (!sheeps[0])
        printf("ERROR ptr NULL\n");
    int radius = get_radius();
    int x = get_x();
    int y = get_y();
    int min = distance(x, y, sheeps[0]->get_x(), sheeps[0]->get_y());
    int min_index = 0;

    for (int i = 1; i < sheeps.size(); i++)
    {
        int dist = distance(x, y, sheeps[i]->get_x(), sheeps[i]->get_y());
        if (dist < radius && dist < min)
        {
            min = dist;
            min_index = i;
        }
    }
    if (min < radius)
    {
        sheep *target = sheeps[min_index];
        set_target_x(target->get_x());
        set_target_y(target->get_y());
        target_dist = min;
        return min_index;
    }
    set_target_x(-1);
    return -1;
}
*/
/*
int wolf::get_kill_radius()
{
    return kill_radius;
}
int wolf::get_target_dist()
{
    return target_dist;
}
void wolf::set_target_x(int x)
{
    target.x = x;
}
void wolf::set_target_y(int y)
{
    target.y = y;
}
*/