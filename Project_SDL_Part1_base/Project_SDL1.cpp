#include "Project_SDL1.h"

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
    srand (time(NULL));
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
  |                     NAMESPACE                       |
  +=====================================================+
*/

namespace
{
    // Defining a namespace without a name -> Anonymous workspace
    // Its purpose is to indicate to the compiler that everything
    // inside of it is UNIQUELY used within this source file.

    SDL_Surface *load_surface_for(const std::string &path, SDL_Surface *window_surface_ptr)
    {
        // Helper function to load a png for a specific surface
        SDL_Surface *loaded_surface = IMG_Load(path.c_str());
        if (!loaded_surface)
            printf("IMG_Load: %s\n", IMG_GetError());

        SDL_Surface *optimized_surface = SDL_ConvertSurface(loaded_surface, window_surface_ptr->format, 0);
        if (!optimized_surface)
            printf("SDL_ConvertSurface: %s\n", SDL_GetError());

        return optimized_surface;
    }

    unsigned distance(unsigned x1, unsigned y1, unsigned x2, unsigned y2)
    {
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }
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
    {
        printf("Create Surface failed\n");
    }
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
        {
            quit = 1;
        }
    }

    // free
    this->~application();

    return 0;
}

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

void ground::set_sheeps(std::vector<sheep *> sheeps)
{
    this->sheeps = sheeps;
}

std::vector<sheep *> ground::get_sheeps()
{
    return sheeps;
}

void ground::add_animal(std::string name)
{
    if (name == "sheep")
        sheeps.push_back(new sheep("../../media/sheep.png", window_surface_ptr_));
    else if (name == "wolf")
        wolves.push_back(new wolf("../../media/wolf.png", window_surface_ptr_));
    else
        printf("Error: unknow name '%s' !", name.c_str());
}

void ground::update(SDL_Window *window_ptr)
{
    if (SDL_FillRect(window_surface_ptr_, NULL, SDL_MapRGB(window_surface_ptr_->format, 143, 188, 143)) < 0)
        printf("%s\n", SDL_GetError());

    // sheeps update
    if (sheeps.size() > 0)
    {
        for (sheep *s : sheeps)
        {
            s->move();
            /*
            int i = s->give_birth(sheeps);
            // printf("New sheep: %d\n",i);
            if (i >= 0)
            {
                sheep *new_sheep = new sheep("../../media/sheep.png", window_surface_ptr_);
                new_sheep->set_x(sheeps[i]->get_x() + 50); // arbitrary choosen
                new_sheep->set_y(sheeps[i]->get_y() + 50); // arbitrary choosen
                sheeps.push_back(new_sheep);
            }
            // s->run_from_wolf(wolves);
            */
            s->draw();
        }
    }

    // wolves update
    for (wolf *w : wolves)
    {
        w->move();
        if (sheeps.size() > 0)
        {
            // the wolf looks for the closest sheep
            auto it = sheeps.begin();
            int i;
            if ((i = w->chaise(sheeps)) >= 0)
                it = sheeps.erase(it + i);
        }
        w->draw();
    }

    if (SDL_UpdateWindowSurface(window_ptr) < 0)
    {
        printf("Update Surface failed\n");
    }
}

/*
  +=====================================================+
  |                       ANIMAL                        |
  +=====================================================+
*/

animal::animal(const std::string &file_path, SDL_Surface *window_surface_ptr)
{
    image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    window_surface_ptr_ = window_surface_ptr;

    // initial position of the animal
    rect.x = (rand() % (frame_width - (2 * frame_boundary))) + frame_boundary;
    rect.y = (rand() % (frame_height - (2 * frame_boundary))) + frame_boundary;

    x_speed = (rand() % 5 + 5) * ((rand() % 2 == 0) ? -1 : 1);
    y_speed = (rand() % 5 + 5) * ((rand() % 2 == 0) ? -1 : 1);
}

animal::~animal()
{
    SDL_FreeSurface(image_ptr_);
    SDL_FreeSurface(window_surface_ptr_);
}

void animal::draw()
{
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &rect);
}

// GETTERS
unsigned animal::get_x() { return rect.x; }
unsigned animal::get_y() { return rect.y; }
int animal::get_x_speed() { return x_speed; }
int animal::get_y_speed() { return y_speed; }
unsigned animal::get_radius() { return radius; }


// SETTERS
void animal::set_x_speed(int speed) { x_speed = speed; }
void animal::set_y_speed(int speed) { y_speed = speed; }
void animal::set_x(int x) { rect.x = x; }
void animal::set_y(int y) { rect.y = y; }
void animal::set_radius(unsigned radius) { this->radius = radius; }
void animal::set_rect(unsigned h, unsigned w) { rect.h = h;
                                                rect.w = w; }

/*
  +=====================================================+
  |                        SHEEP                        |
  +=====================================================+
*/

void sheep::move()
{
    // movement
    unsigned x = get_x();
    unsigned y = get_y();
    int speed_x = get_x_speed();
    int speed_y = get_y_speed();

    if ((x < frame_boundary && speed_x < 0) || (x > frame_width - frame_boundary && speed_x > 0))
        set_x_speed(speed_x * (-1));
    set_x(x + speed_x);

    if ((y < frame_boundary && speed_y < 0) || (y > frame_height - frame_boundary && speed_y > 0))
        set_y_speed(speed_y * (-1));
    set_y(y + speed_y);
}

int sheep::give_birth(std::vector<sheep *> sheeps)
{
    if (sheeps.size() == 0)
        return -1;
    
    for (int i = 0; i < sheeps.size(); i++)
    {
        unsigned dist = distance(get_x(), get_y(), sheeps[i]->get_x(), sheeps[i]->get_y());
        if (dist > 0 && dist < get_radius())
            return i;
    }
    return -1;
}

void sheep::run_from_wolf(std::vector<wolf *> wolfs)
{
    unsigned x = get_x();
    unsigned y = get_y();
    int speed_x = get_x_speed();
    int speed_y = get_y_speed();

    for (int i = 0; i < wolfs.size(); i++)
    {
        unsigned dist = distance(get_x(), get_y(), wolfs[i]->get_x(), wolfs[i]->get_y());
        unsigned rad = get_radius() + wolfs[i]->get_radius();
        if (dist < rad)
        {
            set_x_speed(speed_x * (-1));
            set_y_speed(speed_y * (-1));
        }
    }
}

/*
  +=====================================================+
  |                         WOLF                        |
  +=====================================================+
*/

void wolf::move()
{
    // movement
    unsigned x = get_x();
    unsigned y = get_y();
    int speed_x = get_x_speed();
    int speed_y = get_y_speed();

    if ((x < frame_boundary && speed_x < 0) || (x > frame_width - frame_boundary && speed_x > 0))
        set_x_speed(speed_x * (-1));
    set_x(x + speed_x);

    if ((y < frame_boundary && speed_y < 0) || (y > frame_height - frame_boundary && speed_y > 0))
        set_y_speed(speed_y * (-1));
    set_y(y + speed_y);
}

int wolf::chaise(std::vector<sheep *> sheeps)
{
    if (sheeps.size() == 0)
        return -1;
    
    int min = distance(get_x(), get_y(), sheeps[0]->get_x(), sheeps[0]->get_y());
    int min_index = 0;

    for (int i = 1; i < sheeps.size(); i++)
    {
        int dist = distance(get_x(), get_y(), sheeps[i]->get_x(), sheeps[i]->get_y());
        if (dist < get_radius())
            if (dist < min)
            {
                min = dist;
                min_index = i;
            }
            else
                continue;
    }
    return (min < get_radius()) ? min_index : -1;
    
    /*
    for (int i = 0; i < sheeps.size(); i++)
    {
        int dist = distance(get_x(), get_y(), sheeps[i]->get_x(), sheeps[i]->get_y());
        if (dist < get_radius())
            return i;
    }
    */
    return -1;
    
}