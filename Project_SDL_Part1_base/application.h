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
#include <time.h>
#include <unistd.h>
#include <vector>

// Classes
class application;
class ground;
class interacting_object;
class rendered_object;
class moving_object;
class animal;
class playable_character;
class sheep;
class wolf;

constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // width of window in pixel
constexpr unsigned frame_height = 900; // height of window in pixel
constexpr unsigned frame_boundary =
    100; // minimal distance of animals to the border of the screen
constexpr unsigned max_dist = frame_height + frame_width;

enum animal_type
{
    SHEEP,
    WOLF,
    DOG,
    SHEPHERD
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
    std::vector<std::shared_ptr<moving_object>> moving_objects;

public:
    ground(SDL_Surface *window_surface_ptr);
    ~ground();
    void update(SDL_Window *window); // refresh the screen : move & draw animals

    // other methods
    void add_object(std::shared_ptr<moving_object>);
    std::vector<std::shared_ptr<moving_object>> get_objects();
};

/*
  +=====================================================+
  |                INTERACTING OBJECT                   |
  +=====================================================+
*/

class interacting_object
{
private:
    float stamina; // 0-10
    float max_stamina; // 10
    bool sex; // is female
    bool alive;
    bool prey;
    bool give_birth;
    enum animal_type a_type;

public:
    interacting_object(){};
    ~interacting_object(){};

    virtual void interact_with_object(std::shared_ptr<moving_object> obj){};
    float getStamina()
    {
        return this->stamina;
    }
    float getMaxStamina()
    {
        return this->max_stamina;
    }
    void setMaxStamina(float max)
    {
        this->max_stamina = max;
    }
    void setStamina(float stamina)
    {
        this->stamina = stamina;
    }

    bool getSex()
    {
        return this->sex;
    }

    void setSex(bool sex)
    {
        this->sex = sex;
    }

    bool getBirth()
    {
        return this->give_birth;
    }

    void setBirth(bool give_birth)
    {
        this->give_birth = give_birth;
    }

    bool isAlive()
    {
        return this->alive;
    }

    void setAlive(bool alive)
    {
        this->alive = alive;
    }

    bool isPrey()
    {
        return this->prey;
    }

    void setPrey(bool prey)
    {
        this->prey = prey;
    }

    // getters
    enum animal_type get_type()
    {
        return a_type;
    }

    // setters
    void set_type(enum animal_type type)
    {
        a_type = type;
    }
};

/*
  +=====================================================+
  |                  RENDERED OBJECT                    |
  +=====================================================+
*/
class rendered_object : public interacting_object
{
private:
    SDL_Surface *window_surface_ptr_; // surface on which the rendered_object is
                                      // drawn (non-owning)
    SDL_Surface
        *image_ptr_; // texture of the rendered_object (the loaded image)
    SDL_Rect rect;

public:
    rendered_object(const std::string &file_path,
                    SDL_Surface *window_surface_ptr);
    ~rendered_object();
    void
    draw(); // draw the rendered_object on the screen <-> window_surface_ptr.

    // getters
    int get_x();
    int get_y();
    SDL_Surface *get_window_surface()
    {
        return window_surface_ptr_;
    }

    // setters
    void set_x(int x);
    void set_y(int y);
    void set_rect(unsigned h, unsigned w);
};

/*
  +=====================================================+
  |                    MOVING OBJECT                    |
  +=====================================================+
*/
class moving_object : public rendered_object
{
private:
    int speed;
    int x_speed;
    int y_speed;
    int dist;
    std::shared_ptr<moving_object> interact;

public:
    moving_object(const std::string &file_path,
                  SDL_Surface *window_surface_ptr);
    ~moving_object(){};

    // getters
    int get_speed();
    int get_x_speed();
    int get_y_speed();
    int get_dist();
    std::shared_ptr<moving_object> get_interact();

    // setters
    void set_speed(int speed);
    void set_x_speed(int speed);
    void set_y_speed(int speed);
    void set_dist(int dist);
    void set_interact(std::shared_ptr<moving_object> obj);
    virtual void move(){};
};

/*
  +=====================================================+
  |                       ANIMAL                        |
  +=====================================================+
*/

class animal : public moving_object
{
private:
public:
    animal(const std::string &file_path, SDL_Surface *window_surface_ptr)
        : moving_object(file_path, window_surface_ptr){};
    virtual ~animal(){};
};

/*
  +=====================================================+
  |                 Playable Character                  |
  +=====================================================+
*/

class playable_character : public moving_object
{
private:
public:
    playable_character(const std::string &file_path,
                       SDL_Surface *window_surface_ptr)
        : moving_object(file_path, window_surface_ptr){};
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
public:
    sheep(const std::string &file, SDL_Surface *window_surface);

    ~sheep()
    {}
    void interact_with_object(std::shared_ptr<moving_object> obj);
    void move();
};

/*
  +=====================================================+
  |                         WOLF                        |
  +=====================================================+
*/

class wolf : public animal
{
private:
    std::shared_ptr<moving_object> target;

public:
    wolf(const std::string &file, SDL_Surface *window_surface);

    ~wolf()
    {}
    void interact_with_object(std::shared_ptr<moving_object> obj);
    void move();
};

/*
  +=====================================================+
  |                         DOG                         |
  +=====================================================+
*/

class dog : public animal
{
private:
    // std::shared_ptr<moving_object> shepherd;
    float angle;
    int inc;

public:
    dog(const std::string &file, SDL_Surface *window_surface);
    void interact_with_object(std::shared_ptr<moving_object> obj);
    ~dog()
    {}
    void move();
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
};