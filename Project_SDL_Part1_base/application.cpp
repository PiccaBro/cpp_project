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

application::application(int argc, char *argv[])
{
    // create the application window
    const char *title = "The Happy Farm";
    window_ptr_ = SDL_CreateWindow(title, 0, 0, frame_width, frame_height, 0);
    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
    if (window_surface_ptr_ == NULL)
        printf("Create Surface failed\n");

    // init ground
    grd = std::make_shared<ground>(window_surface_ptr_);

    // init animal count
    this->n_sheep = atoi(argv[1]);
    this->n_wolf = atoi(argv[2]);
    for (size_t i = 0; i < n_sheep; i++)
    {
        std::shared_ptr<animal> s(
            new sheep("../media/sheep.png", window_surface_ptr_));
        grd->add_animal(s);
    }
    for (size_t i = 0; i < n_wolf; i++)
    {
        std::shared_ptr<animal> s(
            new wolf("../media/wolf.png", window_surface_ptr_));
        grd->add_animal(s);
    }

    // game loop
    quit = loop(std::stoul(argv[argc - 1]) * 1000);
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
    // loop
    while (!quit)
    {
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + frame_rate)
        {
            grd->update(window_ptr_);
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
