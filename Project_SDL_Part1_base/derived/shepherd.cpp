#include "../application.h"

/**
 * @brief Construct a new shepherd
 *
 * @param file the path to texture
 * @param renderer the renderer of the window
 */
shepherd::shepherd(const std::string &file, SDL_Renderer *renderer)
    : playable_character(file, renderer)
{
    set_rect(128, 128, false);
    set_xy_speed(5, 5);
    set_click(-1, -1);
    set_type(SHEPHERD);
    setAlive(true);
    setPrey(false);
    setPredator(false);
    setStamina(10, false);
    setMaxStamina(10);
    setBirth(false);
    setSex(false);
}

/**
 * @brief interact only with dogs, give orders if click on them and call them
 * back
 *
 * @param obj the object to interact with
 */
void shepherd::interact_with_object(std::shared_ptr<moving_object> obj)
{
    if (obj->get_type() != DOG)
        return;

    int x, y, h, w, dog_x, dog_y, dog_h, dog_w, click_x, click_y;
    get_xy(&x, &y);
    get_dim(&h, &w);
    obj->get_xy(&dog_x, &dog_y);
    obj->get_dim(&dog_h, &dog_w);
    get_click(&click_x, &click_y);

    bool choosen = obj->is_choosen();
    bool ordered = obj->is_ordered();
    bool go_back = obj->is_going_back();

    if (go_back) // is dog is going back
        obj->set_go_back(x + w / 2, y + h / 2); // send back signal

    // if click on dog's image
    if (click_x >= dog_x && click_x < dog_x + dog_w && click_y >= dog_y
        && click_y < dog_y + dog_h)
    {
        obj->set_choosen(true); // make dog choosen
        set_click(-1, -1); // no target now
    }
    else if (choosen && click_x >= 0)
    {
        obj->set_choosen(false); // allow to be choosen again
        obj->set_ordered(true); // go to target
        obj->set_go_back(-1, -1); // if dog was going back
        obj->set_click(click_x, click_y); // set target
    }
}