﻿// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>
#include <math.h>


class wolf;

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;



// Helper function to initialize SDL
void init();

//------------------ ANIMAL ----------------

class animal {
private:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for
  // todo: Attribute(s) to define its position
  int x_speed;
  int y_speed;
  SDL_Rect rect;
  unsigned radius;
  
public:

  animal(const std::string& file_path, SDL_Surface* window_surface_ptr);
  // todo: The constructor has to load the sdl_surface that corresponds to the
  // texture
  ~animal(); // todo: Use the destructor to release memory and "clean up
               // behind you"

  void draw(); // todo: Draw the animal on the screen <-> window_surface_ptr.
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance
  unsigned get_x();
  unsigned get_y();
  void set_x(int x);
  void set_y(int y);
  int get_y_speed();
  int get_x_speed();
  void set_x_speed(int speed);
  void set_y_speed(int speed);
  void set_rect(unsigned h, unsigned w);
  unsigned get_radius();
  void set_radius(unsigned radius);

  virtual void move(){} // todo: Animals move around, but in a different
                             // fashion depending on which type of animal
};

//------------------- SHEEP -----------------------
// Insert here:
// class sheep, derived from animal
class sheep : public animal {
  public:
  sheep(const std::string& file, SDL_Surface* window_surface):animal(file, window_surface){
     set_rect(71, 67);
     set_radius(20);
  }
  ~sheep(){}
  int give_birth(std::vector<sheep *>sheeps);
  void run_from_wolf(std::vector<wolf *>wolfs);
  void move();
  // todo
  // Ctor
  // Dtor
  // implement functions that are purely virtual in base class
};

//---------------------- WOLF ----------------------------
// Insert here:
// class wolf, derived from animal
// Use only sheep at first. Once the application works
// for sheep you can add the wolves

class wolf : public animal {
  public:
  wolf(const std::string& file, SDL_Surface* window_surface):animal(file, window_surface){
     set_rect(42, 62);
     set_radius(100);
  }
  ~wolf(){}
  virtual void move();
  int chaise(std::vector<sheep *> sheeps);
};


//-------------------- GROUND -----------------------
// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
class ground {
private:
  // Attention, NON-OWNING ptr, again to the screen
  SDL_Surface* window_surface_ptr_;
  // Some attribute to store all the wolves and sheep
  std::vector<sheep *> sheeps;
  std::vector<wolf *> wolves;

public:
  ground(SDL_Surface* window_surface_ptr); // todo: Ctor
  ~ground(); // todo: Dtor, again for clean up (if necessary)
  void add_animal(std::string name); 
  void set_sheeps(std::vector<sheep *> sheeps);
  std::vector<sheep *> get_sheeps();
  void update(SDL_Window *window); // todo: "refresh the screen": Move animals and draw them
 
  // Possibly other methods, depends on your implementation
};


// --------------------- APPLICATION ----------------------

// The application class, which is in charge of generating the window
class application {
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  SDL_Event window_event_;
 
  int quit;
  unsigned n_sheep;
  unsigned n_wolf;
  // Other attributes here, for example an instance of ground

public:
  application(unsigned n_sheep, unsigned n_wolf); // Ctor
  ~application();                                 // dtor

  int loop(unsigned period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};