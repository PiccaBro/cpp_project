#include "../application.h"

/*
  +=====================================================+
  |                       SHEPHERD                      |
  +=====================================================+
*/

shepherd::shepherd(const std::string &file, SDL_Renderer *renderer)
    : playable_character(file, renderer)
{
    set_rect(128, 128, false);
    set_xy_speed(5, 5);
    set_type(SHEPHERD);
    setAlive(true);
    setPrey(false);
    setPredator(false);
    setStamina(10, false);
    setMaxStamina(10);
    setBirth(false);
    setSex(false);
}

void shepherd::interact_with_object(std::shared_ptr<moving_object> obj)
{
    if (obj->get_type() != DOG)
        return;

    SDL_Event event;
    int x, y, dog_x, dog_y, dog_h, dog_w;
    get_xy(&x, &y);
    obj->get_xy(&dog_x, &dog_y);
    obj->get_dim(&dog_h, &dog_w);

    bool choosen = obj->is_choosen();
    bool ordered = obj->is_ordered();
    bool go_back = obj->is_going_back();

    if (go_back)
        obj->set_go_back(x, y);

    while (SDL_PollEvent(&event))
    {
        if (event.type != SDL_MOUSEBUTTONDOWN
            || event.button.button != SDL_BUTTON_LEFT)
            continue;
        std::cout << "button !" << std::endl;
        if (!choosen && x >= dog_x && x < dog_x + dog_w && y >= dog_y
            && y < dog_y + dog_h)
            obj->set_choosen(true);
        else
        {
            obj->set_choosen(false);
            obj->set_target(event.button.x, event.button.y);
        }
    }
}