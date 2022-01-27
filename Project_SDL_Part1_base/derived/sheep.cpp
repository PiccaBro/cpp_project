#include "../application.h"

/*
  +=====================================================+
  |                        SHEEP                        |
  +=====================================================+
*/

sheep::sheep(const std::string &file, SDL_Surface *window_surface)
    : animal(file, window_surface)
{
    set_rect(71, 67);
    setStamina(10);
    setSex(rand() % 2);
    setAlive(true);
    setPrey(true);
    setBirth(false);
    set_type(SHEEP);
    int speed = 5;
    set_x_speed((rand() % speed) * ((rand() % 2 == 0) ? -1 : 1));
    set_y_speed(sqrt(pow(speed, 2) - pow(get_x_speed(), 2))
                * ((rand() % 2 == 0) ? -1 : 1));
}

void sheep::interact_with_object(std::shared_ptr<moving_object> obj)
{
    if (getStamina() <= 0)
    {
        setAlive(false);
    }
    // obj->getSex() ? std::cout << "FEMALE\n" : std::cout << "MALE\n";
    if (get_type() == obj->get_type() && getSex() != obj->getSex()
        && getStamina() > 5 && obj->getStamina() > 5
        && distance(get_x(), get_y(), obj->get_x(), obj->get_y()) < 5)
    {
        obj->setStamina(obj->getStamina() - 10);
        setStamina(getStamina() - 5);
        setBirth(true);
    }
}

void sheep::move()
{
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

    /*
    // Getters
    int x = get_x();
    int y = get_y();
    int speed_x = get_x_speed();
    int speed_y = get_y_speed();
    bool effrayed = false;

    // Run from wolves
    if (hunter.x > -1)
    {
        int d = distance(x, y, hunter.x, hunter.y);
        int speed = get_speed();
        // Escape from boundaries
        if ((x < frame_boundary && speed < 0)
            || (x > frame_width - frame_boundary && speed > 0))
            hunter.x = x;
        if ((y < frame_boundary && speed < 0)
            || (y > frame_height - frame_boundary && speed > 0))
            hunter.y = y;
        // Avoid to go back and forth between the two modes
        if ((hunter.x > x && speed_x > 0) || (hunter.x < x && speed_x < 0))
            set_x_speed(speed_x * -1);
        if ((hunter.y > y && speed_y > 0) || (hunter.y < y && speed_y < 0))
            set_y_speed(speed_y * -1);
        // Speed up
        set_x(x - (((hunter.x - x) * speed * 1.75) / d));
        set_y(y - (((hunter.y - y) * speed) * 1.75 / d));
    }
    // No wolf around
    else
        // Escape from boundaries
        */
}

/*
int sheep::give_birth(std::vector<sheep> sheeps)
{
    if (sheeps.size() == 0)
        return -1;

    for (int i = 0; i < sheeps.size(); i++)
    {
        int dist = distance(get_x(), get_y(), sheeps[i].get_x(),
sheeps[i].get_y()); if (dist < get_radius()) return i;
    }
    return -1;
}
*/
/*
void sheep::run_from_wolf(std::vector<wolf *> wolves)
{
    // Getters
    int x = get_x();
    int y = get_y();
    int speed_x = get_x_speed();
    int speed_y = get_y_speed();
    int radius = get_radius();

    // Center of all wolves with their coordinates
    SDL_Point h;
    h.x = -1;
    h.y = -1;

    int min = distance(x, y, wolves[0]->get_x(), wolves[0]->get_y());
    int min_idx = 0;

    for (int i = 1; i < wolves.size(); i++)
    {
        int wolf_x = wolves[i]->get_x();
        int wolf_y = wolves[i]->get_y();
        int dist = distance(x, y, wolf_x, wolf_y);
        if (dist < radius && dist < min)
        {
            min = dist;
            min_idx = i;
            h.x = wolf_x;
            h.y = wolf_y;
        }
    }
    hunter.x = h.x;
    hunter.y = h.y;
    hunter_dist = min;
}
*/