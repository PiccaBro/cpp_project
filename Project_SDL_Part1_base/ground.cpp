#include "application.h"

/*
  +=====================================================+
  |                       GROUND                        |
  +=====================================================+
*/

ground::ground(SDL_Renderer *renderer)
{
    // Filling the surface with green color
    this->renderer = renderer;
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
    /* if (SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 50, 188, 50))
         < 0)
         printf("%s\n", SDL_GetError());*/
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 50, 188, 50, 255);
    SDL_RenderFillRect(renderer, NULL);

    for (size_t i = 0; i < moving_objects.size(); i++)
    {
        moving_objects[i]->move();
        moving_objects[i]->draw();

        moving_objects[i]->set_dist(max_dist);
        moving_objects[i]->set_hunted(false);
        for (std::shared_ptr<moving_object> obj : moving_objects)
            moving_objects[i]->interact_with_object(obj);

        if (moving_objects[i]->getBirth())
        {
            std::shared_ptr<moving_object> new_obj =
                moving_objects[i]->bear(renderer);
            moving_objects.push_back(new_obj);
            moving_objects[i]->setBirth(false);
        }

        if (!moving_objects[i]->isAlive())
        {
            moving_objects.erase(moving_objects.cbegin() + i);
            // std::cout << "REMOVED SHEEP\n";
        }
    }
    SDL_RenderPresent(renderer);
    /*
        if (SDL_UpdateWindowSurface(window_ptr) < 0)
            printf("Update Surface failed\n");*/
}