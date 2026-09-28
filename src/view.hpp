#ifndef VIEW_HPP
#define VIEW_HPP
using namespace std;

#include "window.hpp"
#include "snake.hpp"
#include "enum.hpp"
#include "world.hpp"



struct  WorldView{
    SDL_Texture *background;

    SDL_Texture *food_blue;
    SDL_Texture *food_red;
    SDL_Texture* food_green;
    SDL_Texture *food_star;
  


};
struct SnakeView{
    SDL_Texture *body_blue;
    SDL_Texture *body_green;
    SDL_Texture *body_red;
    SDL_Texture *head_close_down;
    SDL_Texture *head_close_up;
   SDL_Texture *head_close_right;
   SDL_Texture *head_close_left;
   SDL_Texture *head_open_down;
   SDL_Texture *head_open_up;
  SDL_Texture *head_open_right;
  SDL_Texture *head_open_left;
};
void draw_world(Window* window, World* world, WorldView* view,int score);
void draw_snake(Window* window, Snake* snake, SnakeView* snakeview, World* world);


#endif
