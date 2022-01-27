#include "../application.h"

/*
  +=====================================================+
  |                         DOG                         |
  +=====================================================+
*/

dog::dog(const std::string &file, SDL_Surface *window_surface)
    : animal(file, window_surface)
{
    set_rect(42, 62);
    setStamina(10);
    setSex(false);
    setAlive(true);
    setPrey(false);
    set_type(DOG);

    angle = (rand() % 360) * ((rand() % 2 == 0) ? -1 : 1);
}

void dog::interact_with_object(std::shared_ptr<moving_object> obj)
{
    if (obj->get_type() == SHEPHERD)
    {
        int t_x = obj->get_x();
        int t_y = obj->get_y();
        int x = get_x();
        int y = get_y();
        int radius = 100;
        angle += 5;
        float r_angle = angle * 3.14159 / 180;

        if (angle == 360)
            angle = 1;

        if ((x < frame_boundary) || (x > frame_height - frame_boundary))
            set_x(t_x - cos(r_angle) * radius);
        else
            set_x(t_x + cos(r_angle) * radius);

        if ((y < frame_boundary) || (y > frame_width - frame_boundary))
            set_y(t_y - sin(r_angle) * radius);
        else
            set_y(t_y + sin(r_angle) * radius);
    }
    /*
    if (obj->get_type() == SHEPHERD)
    {
        int x = get_x();
        int y = get_y();

        int radius = 10;
        int speed_x = obj->get_x() + cos((angle + 1) % 360) * radius;
        int speed_y = obj->get_y() + sin((angle + 1) % 360) * radius;

        if ((y < frame_boundary && speed_y < 0)
            || (y > frame_height - frame_boundary && speed_y > 0))
            set_y_speed(speed_y * (-1));
        set_y(y + speed_y);

        if ((x < frame_boundary && speed_x < 0)
            || (x > frame_width - frame_boundary && speed_x > 0))
            set_x_speed(speed_x * (-1));
        set_x(x + speed_x);
    }
    */
    // this->shepherd = obj;
}

void dog::move()
{
    /*
    int x = get_x();
    int y = get_y();
    int radius = 100;
    angle = (angle + 0.1);
    set_x(500 + cos(this->angle) * radius);
    set_y(500 + sin(this->angle) * radius);

    if ((y < frame_boundary && angle < 0)
        || (y > frame_height - frame_boundary && angle > 0))
        angle *= -1;
    set_x(500 + cos(this->angle) * radius);

    if ((x < frame_boundary && speed_x < 0)
        || (x > frame_width - frame_boundary && speed_x > 0))
        angle *= -1;
    set_y(500 + sin(this->angle) * radius);
    */
}