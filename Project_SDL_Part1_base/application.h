// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_image.h>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <err.h>
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <string>
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
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

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
    SDL_Renderer *renderer;
    std::vector<std::shared_ptr<moving_object>> moving_objects;

public:
    ground(SDL_Renderer *renderer);
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
    int stamina; // 0-10
    int max_stamina; // 10
    bool sex; // is female
    bool alive;
    bool prey;
    bool predator;
    bool give_birth;
    enum animal_type a_type;

public:
    interacting_object(){};
    ~interacting_object(){};

    virtual void interact_with_object(std::shared_ptr<moving_object> obj){};
    int getStamina()
    {
        return this->stamina;
    }
    int getMaxStamina()
    {
        return this->max_stamina;
    }
    void setMaxStamina(int max)
    {
        this->max_stamina = max;
    }
    void setStamina(int stamina, bool random)
    {
        if (!(random && rand() % 6))
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

    bool isPredator()
    {
        return this->predator;
    }

    void setPredator(bool predator)
    {
        this->predator = predator;
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
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Rect rect;
    SDL_RendererFlip flip;

public:
    rendered_object(const std::string &file_path, SDL_Renderer *renderer);
    ~rendered_object();
    void draw(); // draw the rendered_object on the screen <-> surface_win.

    // getters
    int get_x();
    int get_y();
    int get_h();
    int get_w();
    /*SDL_Surface *get_window_surface()
    {
        return surface_win;
    }*/

    // setters
    void set_x(int x);
    void set_y(int y);
    void set_rect(unsigned h, unsigned w, bool random);
    void set_flip(SDL_RendererFlip flip);
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
    bool hunted;
    std::shared_ptr<moving_object> interact;

public:
    moving_object(const std::string &file_path, SDL_Renderer *renderer);
    ~moving_object(){};

    // getters
    int get_speed();
    int get_x_speed();
    int get_y_speed();
    int get_dist();
    bool is_hunted();

    // setters
    void set_speed(int speed);
    void set_x_speed(int speed);
    void set_y_speed(int speed);
    void set_dist(int dist);
    void set_hunted(bool hunted);
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
    animal(const std::string &file_path, SDL_Renderer *renderer)
        : moving_object(file_path, renderer){};
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
    playable_character(const std::string &file_path, SDL_Renderer *renderer)
        : moving_object(file_path, renderer){};
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
    sheep(const std::string &file, SDL_Renderer *renderer);

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
    wolf(const std::string &file, SDL_Renderer *renderer);

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
    float angle;
    int inc;

public:
    dog(const std::string &file, SDL_Renderer *renderer);
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
    shepherd(const std::string &file, SDL_Renderer *renderer);

    ~shepherd(){};
};