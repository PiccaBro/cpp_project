#include "application.h"

/*
  +=====================================================+
  |                       GROUND                        |
  +=====================================================+
*/

ground::ground(SDL_Renderer *renderer,
               std::vector<std::shared_ptr<rendered_object>> score)
{
    // Filling the surface with green color
    this->renderer = renderer;
    this->score = score;
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

void ground::draw_score(size_t n_sheep)
{
    score[10]->draw();
    int offset = 220;
    if (n_sheep > 999)
        n_sheep = 999;
    if (n_sheep < 100)
    {
        score[0]->set_xy(offset, 50, false);
        offset += 30;
        score[0]->draw();
    }
    if (n_sheep < 10)
    {
        score[0]->set_xy(offset, 50, false);
        offset += 30;
        score[0]->draw();
    }
    std::string s = std::to_string(n_sheep);
    for (char c : s)
    {
        score[c - '0']->set_xy(offset, 50, false);
        offset += 30;
        score[c - '0']->draw();
    }
}

void ground::update(SDL_Window *window_ptr)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 50, 188, 50, 255);
    SDL_RenderFillRect(renderer, NULL);

    size_t n_sheep = 0;

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
        if (moving_objects[i]->get_type() == SHEEP)
            n_sheep++;
    }
    draw_score(n_sheep);
    SDL_RenderPresent(renderer);
    /*
        if (SDL_UpdateWindowSurface(window_ptr) < 0)
            printf("Update Surface failed\n");*/
}