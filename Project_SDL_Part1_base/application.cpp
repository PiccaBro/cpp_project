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
    window =
        SDL_CreateWindow("The Happy Farm", 0, 0, frame_width, frame_height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    grd = std::make_unique<ground>(renderer);

    // init animal count
    this->n_sheep = atoi(argv[1]);
    this->n_wolf = atoi(argv[2]);
    this->n_dog = atoi(argv[3]);

    for (size_t i = 0; i < max(max(n_sheep, n_wolf), n_dog); i++)
    {
        if (i < n_sheep)
            grd->add_object(
                std::make_unique<sheep>("../media/sheep.png", renderer));
        if (i < n_wolf)
            grd->add_object(
                std::make_unique<wolf>("../media/wolf.png", renderer));
        if (i < n_dog)
            grd->add_object(
                std::make_unique<dog>("../media/dog.png", renderer));
    }
    grd->add_object(
        std::make_unique<shepherd>("../media/shepherd.png", renderer));
    quit = loop(std::stoul(argv[argc - 1]) * 1000);
}

application::~application()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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
            grd->update(window);
            SDL_Delay(frame_time);
            lastTime = currentTime;
        }
        if (currentTime > period)
            quit = 1;
    }
    this->~application();
    return 0;
}
