#include "application.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

/*
  +=====================================================+
  |                  INITIALISATION                     |
  +=====================================================+
*/

void init()
{
    // srand (time(NULL));
    // Initialize SDL
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("init():" + std::string(SDL_GetError()));

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
        throw std::runtime_error("init(): SDL_image could not initialize! "
                                 "SDL_image Error: "
                                 + std::string(IMG_GetError()));
}

/*
  +=====================================================+
  |                    APPLICATION                      |
  +=====================================================+
*/

application::application(unsigned n_sheep, unsigned n_wolf)
{
    // create the application window
    const char *title = "The Happy Farm";
    window_ptr_ = SDL_CreateWindow(title, 0, 0, frame_width, frame_height, 0);
    this->n_sheep = n_sheep;
    this->n_wolf = n_wolf;
}

application::~application()
{
    if (window_surface_ptr_ == NULL)
    {
        std::cout << "ERROR ptr is NULL\n";
        SDL_FreeSurface(window_surface_ptr_);
    }
    if (window_surface_ptr_ == NULL)
    {
        std::cout << "ERROR \n";
        SDL_DestroyWindow(window_ptr_);
    }
}

int application::loop(unsigned period)
{
    unsigned int lastTime = 0, currentTime;
    quit = 0;

    // create ground
    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
    if (window_surface_ptr_ == NULL)
        printf("Create Surface failed\n");

    ground the_ground = ground(window_surface_ptr_);
    while (n_sheep > 0 || n_wolf > 0)
    {
        if (n_sheep > 0)
        {
            the_ground.add_animal("sheep");
            n_sheep--;
        }
        if (n_wolf > 0)
        {
            the_ground.add_animal("wolf");
            n_wolf--;
        }
    }

    // loop
    while (!quit)
    {
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + frame_rate)
        {
            the_ground.update(window_ptr_);
            SDL_Delay(frame_time);
            lastTime = currentTime;
        }
        if (currentTime > period)
            quit = 1;
    }

    // free
    this->~application();
    //
    return 0;
}
// Test push
