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

class wolf;
class sheep;

constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // width of window in pixel
constexpr unsigned frame_height = 900; // height of window in pixel
constexpr unsigned frame_boundary =
    100; // minimal distance of animals to the border of the screen

constexpr unsigned WOLF_RADIUS = 200;
constexpr unsigned SHEEP_RADIUS = 200;

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
    void set_sheeps(std::vector<sheep *> sheeps);
    std::vector<sheep *> get_sheeps();
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
    int x_speed;
    int y_speed;
    SDL_Rect rect;
    unsigned radius;

public:
    animal(const std::string &file_path, SDL_Surface *window_surface_ptr);

    ~animal();

    void draw(); // draw the animal on the screen <-> window_surface_ptr.

    // getters
    unsigned get_x();
    unsigned get_y();
    int get_x_speed();
    int get_y_speed();
    unsigned get_radius();

    // setters
    void set_x(int x);
    void set_y(int y);
    void set_x_speed(int speed);
    void set_y_speed(int speed);
    void set_rect(unsigned h, unsigned w);
    void set_radius(unsigned radius);

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
    sheep(const std::string &file, SDL_Surface *window_surface) : animal(file, window_surface)
    {
        set_rect(71, 67);
        set_radius(SHEEP_RADIUS);
    }

    ~sheep()
    {}

    int give_birth(std::vector<sheep *> sheeps);

    void run_from_wolf(std::vector<wolf *> wolfs);

    void move();
};

/*
  +=====================================================+
  |                         WOLF                        |
  +=====================================================+
*/

class wolf : public animal
{
public:
    wolf(const std::string &file, SDL_Surface *window_surface) : animal(file, window_surface)
    {
        set_rect(42, 62);
        set_radius(WOLF_RADIUS);
    }

    ~wolf()
    {}

    virtual void move();

    int chaise(std::vector<sheep *> sheeps);
};