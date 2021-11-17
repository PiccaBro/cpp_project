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

void init(){
    //srand (time(NULL));
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

namespace{
    // Defining a namespace without a name -> Anonymous workspace
    // Its purpose is to indicate to the compiler that everything
    // inside of it is UNIQUELY used within this source file.

    SDL_Surface *load_surface_for(const std::string &path, SDL_Surface *window_surface_ptr){
        // Helper function to load a png for a specific surface
        SDL_Surface *loaded_surface = IMG_Load(path.c_str());
        if (!loaded_surface)
            printf("IMG_Load: %s\n", IMG_GetError());

        SDL_Surface *optimized_surface = SDL_ConvertSurface(loaded_surface, window_surface_ptr->format, 0);
        if (!optimized_surface)
            printf("SDL_ConvertSurface: %s\n", SDL_GetError());

        return optimized_surface;
    }

    int distance(int x1, int y1, int x2, int y2){
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }
}

/*
  +=====================================================+
  |                    APPLICATION                      |
  +=====================================================+
*/

application::application(unsigned n_sheep, unsigned n_wolf){
    // create the application window
    const char *title = "The Happy Farm";
    window_ptr_ = SDL_CreateWindow(title, 0, 0, frame_width, frame_height, 0);
    this->n_sheep = n_sheep;
    this->n_wolf = n_wolf;
}

application::~application(){
    if (window_surface_ptr_ == NULL){
        std::cout << "ERROR ptr is NULL\n";
        SDL_FreeSurface(window_surface_ptr_);
    }
    if (window_surface_ptr_ == NULL){
        std::cout << "ERROR \n";
        SDL_DestroyWindow(window_ptr_);
    }
}

int application::loop(unsigned period){
    unsigned int lastTime = 0, currentTime;
    quit = 0;

    // create ground
    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
    if (window_surface_ptr_ == NULL)
        printf("Create Surface failed\n");

    ground the_ground = ground(window_surface_ptr_);
    while (n_sheep > 0 || n_wolf > 0){
        if (n_sheep > 0){
            the_ground.add_animal("sheep");
            n_sheep--;
        }
        if (n_wolf > 0){
            the_ground.add_animal("wolf");
            n_wolf--;
        }
    }

    // loop
    while (!quit){
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + frame_rate){
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
//Test push
/*
  +=====================================================+
  |                       GROUND                        |
  +=====================================================+
*/

ground::ground(SDL_Surface *window_surface_ptr){
    // Filling the surface with green color
    this->window_surface_ptr_ = window_surface_ptr;
}

ground::~ground(){}

std::vector<sheep *> ground::get_sheeps(){
    return sheeps;
}

std::vector<wolf *> ground::get_wolves(){
    return wolves;
}
//sheeps.emplace.back(args);
void ground::add_animal(std::string name){
    if (name == "sheep"){
        //sheeps.emplace_back("../media/sheep.png", window_surface_ptr_);
        sheeps.push_back(new sheep("../media/sheep.png", window_surface_ptr_));
    }
    else if (name == "wolf"){
        //wolves.emplace_back("../media/wolf.png", window_surface_ptr_);
        wolves.push_back(new wolf("../media/wolf.png", window_surface_ptr_));
    }
    else
        printf("Error: unknow name '%s' !", name.c_str());
}

void ground::update(SDL_Window *window_ptr){
    if (SDL_FillRect(window_surface_ptr_, NULL, SDL_MapRGB(window_surface_ptr_->format, 50, 188, 50)) < 0)
        printf("%s\n", SDL_GetError());

    // sheeps update

    for (sheep *s : sheeps){
        s->move();
        s->draw();
    }

    // wolves update
    for (wolf *w : wolves){
        // the wolf looks for the closest sheep
        auto it = sheeps.begin();
        int i;
        if (((i = w->chaise(sheeps)) > -1) && (w->get_target_dist() <= w->get_kill_radius())){
            it = sheeps.erase(it + i);
            w->set_target_x(-1);
        }
        w->move();
        w->draw();
    }

    if (SDL_UpdateWindowSurface(window_ptr) < 0)
        printf("Update Surface failed\n");
}

/*
  +=====================================================+
  |                       ANIMAL                        |
  +=====================================================+
*/

animal::animal(const std::string &file_path, SDL_Surface *window_surface_ptr){
    image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    window_surface_ptr_ = window_surface_ptr;

    // initial position of the animal
    rect.x = (rand() % (frame_width - (2 * frame_boundary))) + frame_boundary;
    rect.y = (rand() % (frame_height - (2 * frame_boundary))) + frame_boundary;

    speed = 5;
    x_speed = (rand() % speed) * ((rand() % 2 == 0) ? -1 : 1);
    y_speed = sqrt(pow(speed, 2) - pow(x_speed, 2)) * ((rand() % 2 == 0) ? -1 : 1);
}

animal::~animal(){
    SDL_FreeSurface(image_ptr_);
    SDL_FreeSurface(window_surface_ptr_);
}

void animal::draw(){
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &rect);
}

// GETTERS
int animal::get_x() { return rect.x; }
int animal::get_y() { return rect.y; }
int animal::get_speed() { return speed; }
int animal::get_x_speed() { return x_speed; }
int animal::get_y_speed() { return y_speed; }
int animal::get_radius() { return radius; }


// SETTERS
void animal::set_x_speed(int speed) { x_speed = speed; }
void animal::set_y_speed(int speed) { y_speed = speed; }
void animal::set_x(int x) { rect.x = x; }
void animal::set_y(int y) { rect.y = y; }
void animal::set_rect(unsigned h, unsigned w) { rect.h = h; rect.w = w; }
void animal::set_radius(int radius) {this->radius = radius;}

/*
  +=====================================================+
  |                        SHEEP                        |
  +=====================================================+
*/

void sheep::move(){
    // movement
    int x = get_x();
    int y = get_y();
    int speed_x = get_x_speed();
    int speed_y = get_y_speed();

    if ((x < frame_boundary && speed_x < 0) || (x > frame_width - frame_boundary && speed_x > 0))
        set_x_speed(speed_x * (-1));
    set_x(x + speed_x);

    if ((y < frame_boundary && speed_y < 0) || (y > frame_height - frame_boundary && speed_y > 0))
        set_y_speed(speed_y * (-1));
    set_y(y + speed_y);
}
/*
int sheep::give_birth(std::vector<sheep> sheeps)
{
    if (sheeps.size() == 0)
        return -1;
    
    for (int i = 0; i < sheeps.size(); i++)
    {
        int dist = distance(get_x(), get_y(), sheeps[i].get_x(), sheeps[i].get_y());
        if (dist < get_radius())
            return i;
    }
    return -1;
}

void sheep::run_from_wolf(std::vector<wolf> wolves)
{
    int x = get_x();
    int y = get_y();
    int speed_x = get_x_speed();
    int speed_y = get_y_speed();
    int radius = get_radius();

    int count = 0;
    std::vector<SDL_Point> points;

    for (int i = 0; i < wolves.size(); i++)
    {
        int wolf_x = wolves[i].get_x();
        int wolf_y = wolves[i].get_y();
        int dist = distance(x, y, wolf_x, wolf_y);
        if (dist < radius){
            SDL_Point point;
            point.x = wolf_x;
            point.y = wolf_y;
            points.push_back(point);
            count++;
        }
    }
    if (count == 0)
        return;

    SDL_Point center;
    int sum_x = 0;
    int sum_y = 0;
    for (SDL_Point point : points){
        sum_x += point.x;
        sum_y += point.y;
    }
    center.x = sum_x / count;
    center.y = sum_y / count;
    int d = distance(x, y, center.x, center.y);
    set_x(x - (center.x - x) * speed_x / d);
    set_y(y - (center.y - y) * speed_y / d);
}
*/
/*
  +=====================================================+
  |                         WOLF                        |
  +=====================================================+
*/

void wolf::move()
{
    // movement
    int x = get_x();
    int y = get_y();
    int target_x = target.x;

    if (target_x >= 0) {
        int speed = get_speed();
        int target_y = target.y;

        set_x(x + (((target_x - x) * speed) / target_dist));
        set_y(y + (((target_y - y) * speed) / target_dist));    
    }
    else {
        int speed_x = get_x_speed();
        int speed_y = get_y_speed();
        if ((y < frame_boundary && speed_y < 0) || (y > frame_height - frame_boundary && speed_y > 0))
            set_y_speed(speed_y * (-1));
        set_y(y + speed_y);
        if ((x < frame_boundary && speed_x < 0) || (x > frame_width - frame_boundary && speed_x > 0))
            set_x_speed(speed_x * (-1));
        set_x(x + speed_x);
    }
}

int wolf::chaise(std::vector<sheep *> sheeps)
{
    if (sheeps.size() == 0){
      set_target_x(-1);
      return -1;
    }
    int radius = get_radius();
    int x = get_x();
    int y = get_y();
    int min = distance(x, y, sheeps[0]->get_x(), sheeps[0]->get_y());
    int min_index = 0;

    for (int i = 1; i < sheeps.size(); i++){
      int dist = distance(x, y, sheeps[i]->get_x(), sheeps[i]->get_y());
      if (dist < radius && dist < min)
        min = dist;
        min_index = i;
    }
    if (min < radius) {
      sheep *target = sheeps[min_index];
      set_target_x(target->get_x());
      set_target_y(target->get_y());
      target_dist = min;
      return min_index;
    }
    set_target_x(-1);
    return -1;
}

int wolf::get_kill_radius(){
    return kill_radius;
}

int wolf::get_target_dist(){
    return target_dist;
}

void wolf::set_target_x(int x){
    target.x = x;
}

void wolf::set_target_y(int y){
    target.y = y;
}