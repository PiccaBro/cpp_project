// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <optional>
#include <vector>

class sheep;
class wolf;

constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // width of window in pixel
constexpr unsigned frame_height = 900; // height of window in pixel
constexpr unsigned frame_boundary = 100; // minimal distance of animals to the border of the screen

constexpr int WOLF_RADIUS = 300;
constexpr int SHEEP_RADIUS = 100;

// helper function to initialize SDL
void init();

/*
  +=====================================================+
  |                    APPLICATION                      |
  +=====================================================+
*/

// the application class, which is in charge of generating the window
class application
{
private:
    // the following are OWNING ptrs
    SDL_Window *window_ptr_;
    SDL_Surface *window_surface_ptr_;
    SDL_Event window_event_;

    int quit;
    unsigned n_sheep;
    unsigned n_wolf;

    // other attributes here, for example an instance of ground

public:
    application(unsigned n_sheep, unsigned n_wolf);
    ~application();

    int
    loop(unsigned period); // main loop of the application.
                           // this ensures that the screen is updated
                           // at the correct rate.
                           // the application terminate after 'period' seconds
};

/*
  +=====================================================+
  |                       GROUND                        |
  +=====================================================+
*/

// the ground on which all the animals live
class ground
{
private:
    SDL_Surface *window_surface_ptr_; // NON-OWNING ptr, again to the screen

    // other attributes
    std::vector<sheep *> sheeps;
    std::vector<wolf *> wolves;

public:
    ground(SDL_Surface *window_surface_ptr);
    ~ground();
    void update(SDL_Window *window); // refresh the screen : move & draw animals

    // other methods
    void add_animal(std::string name);
    //void set_sheeps(std::vector<sheep> sheeps);
    std::vector<sheep *> get_sheeps();
    std::vector<wolf *> get_wolves();
};

/*
  +=====================================================+
  |                       ANIMAL                        |
  +=====================================================+
*/

class animal
{
private:
    SDL_Surface *window_surface_ptr_; // surface on which the animal is drawn
                                      // (non-owning)
    SDL_Surface *image_ptr_; // texture of the animal (the loaded image)

    // other attributes
    int speed;
    int x_speed;
    int y_speed;
    SDL_Rect rect;
    int radius;

public:
    animal(const std::string &file_path, SDL_Surface *window_surface_ptr);

    ~animal();

    void draw(); // draw the animal on the screen <-> window_surface_ptr.

    // getters
    int get_x();
    int get_y();
    int get_x_speed();
    int get_y_speed();
    int get_speed();
    int get_radius();

    // setters
    void set_x(int x);
    void set_y(int y);
    void set_x_speed(int speed);
    void set_y_speed(int speed);
    void set_rect(unsigned h, unsigned w);
    void set_radius(int radius);

    virtual void move()
    {}
};

/*
  +=====================================================+
  |                        SHEEP                        |
  +=====================================================+
*/

class sheep : public animal
{
public:
    sheep(const std::string &file, SDL_Surface *window_surface)
    : animal(file, window_surface)
    {
        set_rect(71, 67);
        set_radius(SHEEP_RADIUS);
    }

    ~sheep(){}

    void move();
   // int give_birth(std::vector<sheep> sheeps);
    //void run_from_wolf(std::vector<wolf> wolves);
};

/*
  +=====================================================+
  |                         WOLF                        |
  +=====================================================+
*/

class wolf : public animal
{
private:
    // coord target X Y
    SDL_Point target; //RM
    int kill_radius;
    int target_dist;
    
public:
    wolf(const std::string &file, SDL_Surface *window_surface)
    : animal(file, window_surface)
    {
        set_rect(42, 62);
        set_radius(WOLF_RADIUS);
        target.x = -1;
        target.y = -1;
        target_dist = 0;
        kill_radius = 20;
    }

    ~wolf(){}

    virtual void move();
    int chaise(std::vector<sheep *> sheeps);
    int get_kill_radius();
    int get_target_dist();
    void set_target_x(int x);
    void set_target_y(int y);
};