#include "application.h"

using namespace std;
/*
  +=====================================================+
  |                  INITIALISATION                     |
  +=====================================================+
*/

void init()
{
    // srand (time(NULL));
    // Initialize SDL
    int status = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    if (status < 0)
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
    window_ptr_ =
        SDL_CreateWindow("The Happy Farm", 0, 0, frame_width, frame_height, 0);
    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
    if (window_surface_ptr_ == NULL)
        printf("Create Surface failed\n");
    
    // init ground
    grd = std::make_unique<ground>(window_surface_ptr_);

    // init animal count
    this->n_sheep = atoi(argv[1]);
    this->n_wolf = atoi(argv[2]);
    this->n_dog = atoi(argv[3]);

    for (size_t i = 0; i < max(max(n_sheep, n_wolf), n_sheep); i++)
    {
        if (i < n_sheep)
            grd->add_object(std::make_unique<sheep>("../media/sheep.png",
                                                    window_surface_ptr_));
        if (i < n_wolf)
            grd->add_object(std::make_unique<wolf>("../media/wolf.png",
                                                   window_surface_ptr_));
        if (i < n_dog)
            grd->add_object(
                std::make_unique<dog>("../media/dog.png", window_surface_ptr_));
    }
    grd->add_object(std::make_unique<shepherd>("../media/shepherd.png",
                                               window_surface_ptr_));
    quit = loop(std::stoul(argv[argc - 1]) * 1000);
}

application::~application()
{
    if (window_surface_ptr_ == NULL)
        std::cout << "ERROR ptr is NULL\n";
    if (window_surface_ptr_ == NULL)
        std::cout << "ERROR \n";
    SDL_DestroyWindow(window_ptr_);
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
    this->~application();
    return 0;
}
