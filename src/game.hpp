#ifndef GAME_HPP
#define GAME_HPP

#include "world.hpp"
#include "window.hpp"
#include "snake.hpp"
#include "view.hpp"




struct Game{
    World* world;
   Window *window;;
   Snake* snake;
    WorldView* view;
    SnakeView* snakeview;
    int score=0;
    Statut statut;

    
};
void init_view(Window*window,Game *game);
bool save_game(Game *game,string filename);
void check_and_eat_food(Game *game);
void remove_middle_anneau(Game* game) ;
void  change_statut(Game *game);
bool move_snake(Game *game);
void free_anneaux(Game *game) ;
bool load_game(Game *game,string filename);

#endif
