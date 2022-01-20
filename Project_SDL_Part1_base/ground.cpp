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

std::vector<sheep *> ground::get_sheeps()
{
    return sheeps;
}

std::vector<wolf *> ground::get_wolves()
{
    return wolves;
}
// sheeps.emplace.back(args);
void ground::add_animal(std::string name)
{
    if (name == "sheep")
    {
        // sheeps.emplace_back("../media/sheep.png", window_surface_ptr_);
        sheeps.push_back(new sheep("../media/sheep.png", window_surface_ptr_));
    }
    else if (name == "wolf")
    {
        // wolves.emplace_back("../media/wolf.png", window_surface_ptr_);
        wolves.push_back(new wolf("../media/wolf.png", window_surface_ptr_));
    }
    else
        printf("Error: unknow name '%s' !", name.c_str());
}

void ground::update(SDL_Window *window_ptr)
{
    if (SDL_FillRect(window_surface_ptr_, NULL,
                     SDL_MapRGB(window_surface_ptr_->format, 50, 188, 50))
        < 0)
        printf("%s\n", SDL_GetError());

    // sheeps update

    for (auto *s : sheeps)
    {
        s->run_from_wolf(wolves);
        s->move();
        s->draw();
    }

    // wolves update
    for (wolf *w : wolves)
    {
        // the wolf looks for the closest sheep
        auto it = sheeps.begin();
        int i = w->chaise(sheeps);

        if ((i > -1) && (w->get_target_dist() <= w->get_kill_radius()))
        {
            it = sheeps.erase(it + i);
            w->set_target_x(-1);
        }
        w->move();
        w->draw();
    }
    if (SDL_UpdateWindowSurface(window_ptr) < 0)
        printf("Update Surface failed\n");
}