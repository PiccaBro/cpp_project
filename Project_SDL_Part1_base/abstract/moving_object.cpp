#include "../application.h"

/**
 * @brief Construct a new moving object
 *
 * @param file_path the path to texture
 * @param renderer the renderer of the window
 */
moving_object::moving_object(const std::string &file_path,
                             SDL_Renderer *renderer)
    : rendered_object(file_path, renderer)
{
    speed = 0;
    x_speed = 0;
    y_speed = 0;
    dist = max_dist;
    hunted = false;
    interact = NULL;
    choosen = false;
    ordered = false;
    go_back = false;
    click = { -1, -1 };
}

/**
 * @brief Get the const speed
 *
 * @param speed the speed
 */
void moving_object::get_speed(int *speed)
{
    *speed = this->speed;
}

/**
 * @brief Get the vectors speed_x and speed_y
 *
 * @param speed_x the x component
 * @param speed_y the y component
 */
void moving_object::get_xy_speed(int *speed_x, int *speed_y)
{
    *speed_x = x_speed;
    *speed_y = y_speed;
}

/**
 * @brief Get the distance recorded
 *
 * @return int the distance
 */
int moving_object::get_dist()
{
    return dist;
}
/**
 * @brief if the object is hunted by another one
 *
 * @return true
 * @return false
 */
bool moving_object::is_hunted()
{
    return hunted;
}
/**
 * @brief if object is clicked on.
 * Just for dogs for the moment
 *
 * @return true
 * @return false
 */
bool moving_object::is_choosen()
{
    return choosen;
}
/**
 * @brief if object is choosen, the next click order it to go to.
 * Just for dogs for the moment
 *
 * @return true
 * @return false
 */
bool moving_object::is_ordered()
{
    return ordered;
}
/**
 * @brief If the object is going back.
 * Just for dogs for the moment
 *
 * @return true
 * @return false
 */
bool moving_object::is_going_back()
{
    return go_back;
}
/**
 * @brief Get the coordinates of the last click
 *
 * @param x the x component
 * @param y the y component
 */
void moving_object::get_click(int *x, int *y)
{
    *x = click.x;
    *y = click.y;
}

/**
 * @brief Set the speed of the object
 *
 * @param speed the speed
 */
void moving_object::set_speed(int speed)
{
    this->speed = speed;
}

/**
 * @brief Set the components of the speed
 *
 * @param speed_x the speed_x component
 * @param speed_y the speed y component
 */
void moving_object::set_xy_speed(int speed_x, int speed_y)
{
    x_speed = speed_x;
    y_speed = speed_y;
}
/**
 * @brief Set the distance to record
 *
 * @param d the distance
 */
void moving_object::set_dist(int d)
{
    dist = d;
}
/**
 * @brief Set true if the object is hunted by another one
 *
 * @param hunted the hunted boolean
 */
void moving_object::set_hunted(bool hunted)
{
    this->hunted = hunted;
}

/**
 * @brief Set true if the object is clicked on
 *
 * @param choosen the choosen boolean
 */
void moving_object::set_choosen(bool choosen)
{
    this->choosen = choosen;
}

/**
 * @brief Set true if the object is ordered
 *
 * @param ordered
 */
void moving_object::set_ordered(bool ordered)
{
    this->ordered = ordered;
}

/**
 * @brief If x > 0, the object is going back
 *
 * @param x the x component of the target
 * @param y the y component of the target
 */
void moving_object::set_go_back(int x, int y)
{
    click.x = x;
    click.y = y;
    go_back = x > 0;
}

/**
 * @brief Set the coordinates of the last click
 *
 * @param x the x component
 * @param y the y component
 */
void moving_object::set_click(int x, int y)
{
    click.x = x;
    click.y = y;
}