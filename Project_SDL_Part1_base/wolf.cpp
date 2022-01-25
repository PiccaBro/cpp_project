#include "application.h"

/*
  +=====================================================+
  |                         WOLF                        |
  +=====================================================+
*/

wolf::wolf(const std::string &file, SDL_Surface *window_surface)
    : animal(file, window_surface)
{
    set_rect(42, 62);
    set_radius(300);
    set_type(WOLF);
    // target.x = -1;
    // target.y = -1;
    // target_dist = 0;
    // kill_radius = 20;
}

void wolf::move()
{
    stay_on_screen();
    /*
    int target_x = target.x;

    // Hunt the closest sheep
    if (target_x > -1)
    {
        int speed = get_speed();
        int target_y = target.y;

        set_x(x + (((target_x - x) * speed) / target_dist));
        set_y(y + (((target_y - y) * speed) / target_dist));
    }
    // Walk as the beginning
    else
    {
        */
    /*
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
    //}
}

void wolf::interact_with_animal(std::shared_ptr<animal> target)
{}

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