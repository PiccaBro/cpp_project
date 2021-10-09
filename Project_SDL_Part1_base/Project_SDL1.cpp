#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

//--------------------------- INIT ------------------------------

void init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw std::runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             std::string(IMG_GetError()));
}

namespace {
// Defining a namespace without a name -> Anonymous workspace
// Its purpose is to indicate to the compiler that everything
// inside of it is UNIQUELY used within this source file.

  SDL_Surface* load_surface_for(const std::string& path,
                                SDL_Surface* window_surface_ptr) {

    // Helper function to load a png for a specific surface
    // See SDL_Convert Surface

    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (!loaded_surface)
      printf("IMG_Load: %s\n", IMG_GetError());
    
    SDL_Surface *optimized_surface = SDL_ConvertSurface (loaded_surface, window_surface_ptr->format, 0);
    if (!optimized_surface)
      printf("SDL_ConvertSurface: %s\n", SDL_GetError());

    return optimized_surface;
  } // namespace
}


// ----------------------------- APPLICATION ---------------------------------

application::application(unsigned n_sheep, unsigned n_wolf){
  
  // create the application window
  const char *title = "The Happy Farm";
  window_ptr_ = SDL_CreateWindow(title, 0, 0, frame_width, frame_height, 0);
}

application::~application(){
  if (window_surface_ptr_ == NULL) {
    std::cout << "ERROR ptr is NULL\n";
    SDL_FreeSurface(window_surface_ptr_);
  }
  if (window_surface_ptr_ == NULL) {
    std::cout << "ERROR \n";
    SDL_DestroyWindow(window_ptr_);
  }
}

int application::loop(unsigned period){
  unsigned int lastTime = 0, currentTime;
  quit = 0;

  // create ground
  window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
  if (window_surface_ptr_ == NULL){
    printf("Create Surface failed\n");
  }
  ground the_ground = ground(window_surface_ptr_);
  the_ground.add_animal();

  // loop
  while (!quit) {
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + frame_rate) {
      the_ground.update(window_ptr_);
      SDL_Delay(frame_time);
      lastTime = currentTime;
    }
    if(currentTime > period){
      quit = 1;
    }
  }

  // free
  this->~application();

  return 0;
}

//--------------------------- GROUND ------------------------------

ground::ground(SDL_Surface* window_surface_ptr){
  
  // Filling the surface with green color
  this->window_surface_ptr_ = window_surface_ptr;
}

ground::~ground(){

}

void ground::add_animal(){
  sh = new sheep("../../media/sheep.png",window_surface_ptr_);
}

void ground::update(SDL_Window *window_ptr){
   
  if(SDL_FillRect(window_surface_ptr_, NULL, SDL_MapRGB(window_surface_ptr_->format, 143, 188, 143)) < 0)
    printf("%s\n", SDL_GetError());

  sh->move();
  sh->draw();
 
  if (SDL_UpdateWindowSurface(window_ptr) < 0){
      printf("Update Surface failed\n");
  }
}

// -------------------------- ANIMAL ----------------------------

animal::animal(const std::string& file_path, SDL_Surface* window_surface_ptr){
    image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    window_surface_ptr_ = window_surface_ptr;
    
    // coordonnées initiales de l'animal
    srand(time(NULL));
    x = (rand() % (frame_width - (2 * frame_boundary))) + frame_boundary;
    y = (rand() % (frame_height - (2 * frame_boundary))) + frame_boundary;
    
    printf("x = %u\n",x);
    printf("y = %u\n",y);
    srand(time(NULL));
    x_speed = (rand() % 3 + 3) * ((rand() % 2 == 0) ? -1 : 1);
    y_speed = (rand() % 3 + 3) * ((rand() % 2 == 0) ? -1 : 1);
}

void animal::draw(){
  SDL_Rect size;
  size.x = x;
  size.y = y;
  size.w = 67;
  size.h = 71;
  SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &size);
}

//GETTERS

unsigned animal::get_x(){
  return x;
}

unsigned animal::get_y(){
  return y;
}

int animal::get_x_speed(){
  return x_speed;
}

int animal::get_y_speed(){
  return y_speed;
}

//SETTERS

void animal::set_x_speed(int speed) {
  x_speed = speed;
}

void animal::set_y_speed(int speed) {
  y_speed = speed;
}

void animal::set_x(int x){
  this->x = x;
}

void animal::set_y(int y){
  this->y = y;
}

// -------------------------  SHEEP ---------------------------

void sheep::move(){
  unsigned x = get_x();
  unsigned y = get_y();
  int speed_x = get_x_speed();
  int speed_y = get_y_speed();

  if(x < frame_boundary || x > frame_width - frame_boundary)
    set_x_speed(speed_x * (-1));
  set_x(x + speed_x);

  if(y < frame_boundary || y > frame_height - frame_boundary)
    set_y_speed(speed_y * (-1));
  set_y(y + speed_y);
}

