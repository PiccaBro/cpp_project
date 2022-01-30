#include "application.h"

/*
  +=====================================================+
  |                       GROUND                        |
  +=====================================================+
*/

ground::ground(SDL_Surface *window_surface_ptr)
{
    // Filling the surface with green color
    this->window_surface_ptr_ = window_surface_ptr;
}

ground::~ground()
{}

std::vector<std::shared_ptr<moving_object>> ground::get_objects()
{
    return moving_objects;
}

void ground::add_object(std::shared_ptr<moving_object> moving_object)
{
    moving_objects.push_back(moving_object);
}

void ground::update(SDL_Window *window_ptr)
{
    if (SDL_FillRect(window_surface_ptr_, NULL,
                     SDL_MapRGB(window_surface_ptr_->format, 50, 188, 50))
        < 0)
        printf("%s\n", SDL_GetError());

    // sheeps update

    for (size_t i = 0; i < moving_objects.size(); i++)
    {
        // s->run_from_wolf(wolves);
        moving_objects[i]->move();
        moving_objects[i]->draw();
        moving_objects[i]->set_dist(max_dist);
        for (std::shared_ptr<moving_object> obj : moving_objects)
        {
            moving_objects[i]->interact_with_object(obj);
        }
        if (moving_objects[i]->getBirth() == true)
        {
            std::shared_ptr<moving_object> new_s = std::make_unique<sheep>(
                "../media/sheep.png", window_surface_ptr_);
            new_s->set_x(moving_objects[i]->get_x());
            new_s->set_y(moving_objects[i]->get_y());
            moving_objects.push_back(new_s);
            // std::cout << "BIRTH\n";
            moving_objects[i]->setBirth(false);
        }

        if (!moving_objects[i]->isAlive())
        {
            moving_objects.erase(moving_objects.cbegin() + i);
            //  std::cout << "REMOVED SHEEP\n";
        }
    }

    if (SDL_UpdateWindowSurface(window_ptr) < 0)
        printf("Update Surface failed\n");
}