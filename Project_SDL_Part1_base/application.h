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

// Classes
class sheep;
class ground;
class animal;
class wolf;
class object;
class playable_character;

constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // width of window in pixel
constexpr unsigned frame_height = 900; // height of window in pixel
constexpr unsigned frame_boundary =
    100; // minimal distance of animals to the border of the screen

enum animal_type
{
    SHEEP,
    WOLF,
    DOG
};

// helper function to initialize SDL
void init();

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

    SDL_Surface *load_surface_for(const std::string &path,
                                  SDL_Surface *window_surface_ptr)
    {
        // Helper function to load a png for a specific surface
        SDL_Surface *loaded_surface = IMG_Load(path.c_str());
        if (!loaded_surface)
            printf("IMG_Load: %s\n", IMG_GetError());

        SDL_Surface *optimized_surface =
            SDL_ConvertSurface(loaded_surface, window_surface_ptr->format, 0);
        if (!optimized_surface)
            printf("SDL_ConvertSurface: %s\n", SDL_GetError());
        return optimized_surface;
    }

    int distance(int x1, int y1, int x2, int y2)
    {
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }
} // namespace

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

    int quit;
    unsigned n_sheep;
    unsigned n_wolf;
    unsigned n_dog;
    std::shared_ptr<ground> grd;

    // other attributes here, for example an instance of ground

public:
    application(int argc, char *argv[]);
    ~application();
    int
    loop(unsigned period); // main loop of the application.
                           // this ensures that the screen is updated
                           // at the correct rate.
                           // the application terminate after 'period' seconds
    int get_exit_code()
    {
        return quit;
    }
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
    std::vector<std::shared_ptr<object>> objects;

public:
    ground(SDL_Surface *window_surface_ptr);
    ~ground();
    void update(SDL_Window *window); // refresh the screen : move & draw animals

    // other methods
    void add_object(std::shared_ptr<object>);
    std::vector<std::shared_ptr<object>> get_objects();
};

/*
  +=====================================================+
  |                       OBJECT                        |
  +=====================================================+
*/

class object
{
private:
    SDL_Surface *window_surface_ptr_; // surface on which the object is drawn
                                      // (non-owning)
    SDL_Surface *image_ptr_; // texture of the object (the loaded image)
    SDL_Rect rect;
    // other attributes
    int speed;
    int x_speed;
    int y_speed;

public:
    object(const std::string &file_path, SDL_Surface *window_surface_ptr);
    ~object();
    void draw(); // draw the object on the screen <-> window_surface_ptr.
    virtual void stay_on_screen(){};

    // getters
    int get_x();
    int get_y();
    int get_x_speed();
    int get_y_speed();
    int get_speed();

    // setters
    void set_x(int x);
    void set_y(int y);
    void set_x_speed(int speed);
    void set_y_speed(int speed);
    void set_speed(int speed);
    void set_rect(unsigned h, unsigned w);

    virtual void move(){};
};

/*
  +=====================================================+
  |                       ANIMAL                        |
  +=====================================================+
*/

class animal : public object
{
private:
    enum animal_type a_type;

public:
    animal(const std::string &file_path, SDL_Surface *window_surface_ptr)
        : object(file_path, window_surface_ptr){};
    virtual ~animal(){};
    virtual void interact_with_animal(std::shared_ptr<animal> target){};

    // getters
    enum animal_type get_type();

    // setters
    void set_type(enum animal_type type);

    // void move(){};
};

/*
  +=====================================================+
  |                 Playable Character                  |
  +=====================================================+
*/

class playable_character : public object
{
private:
public:
    playable_character(const std::string &file_path,
                       SDL_Surface *window_surface_ptr)
        : object(file_path, window_surface_ptr){};
    ~playable_character(){};
    void move();
};

/*
  +=====================================================+
  |                        SHEEP                        |
  +=====================================================+
*/

class sheep : public animal
{
private:
    // SDL_Point hunter;
    // int hunter_dist;

public:
    sheep(const std::string &file, SDL_Surface *window_surface);

    ~sheep()
    {}
    void stay_on_screen();
    void move();
    void interact_with_animal(std::shared_ptr<animal> target);
    // int give_birth(std::vector<sheep> sheeps);
    // void run_from_wolf(std::vector<wolf *> wolves);
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
    // SDL_Point target; // RM
    // int kill_radius;
    // int target_dist;

public:
    wolf(const std::string &file, SDL_Surface *window_surface);

    ~wolf()
    {}
    void move();
    void stay_on_screen();
    void interact_with_animal(std::shared_ptr<animal> target);

    // int chaise(std::vector<sheep *> sheeps);
    /*
    int get_kill_radius();
    int get_target_dist();
    void set_target_x(int x);
    void set_target_y(int y);
    */
};

/*
  +=====================================================+
  |                         DOG                         |
  +=====================================================+
*/

class dog : public animal
{
private:
public:
    dog(const std::string &file, SDL_Surface *window_surface);

    ~dog()
    {}
    void stay_on_screen();
    void move();
    void interact_with_animal(std::shared_ptr<animal> target);
};

/*
  +=====================================================+
  |                      SHEPHERD                       |
  +=====================================================+
*/

class shepherd : public playable_character
{
private:
public:
    shepherd(const std::string &file, SDL_Surface *window_surface);

    ~shepherd(){};
    void stay_on_screen();
    // void move();
    void interact_with_animal(std::shared_ptr<animal> target);
};