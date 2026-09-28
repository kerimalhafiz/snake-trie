#include <iostream>
#include "world.hpp"  
#include "window.hpp"
#include"game.hpp"
#include "snake.hpp"
#include "gestionevent.hpp"
#include "view.hpp"
using namespace std;

int main(int argc, char** argv) {
    
    string filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "save.txt";
    }
        
    Game game;
    Snake snake;
    Window window;
    World world;
    bool quit = false;
    world.width=20;
    world.height=20;
    game.world=&world;
    game.snake=&snake;
    game.window=&window;
    game.statut=Begin;

    init_window(&window, 800, 600, "Snake-trie");
    init_world(&world, 20, 20);
    init_snake(&snake, 20, 20, North);

    init_food(&world,4);
    
    init_view(&window,&game);
    while (!quit) {
    
        
        if (handle_event(&game,filename)) {
            quit = true;
       
        
        }
        if (move_snake(&game))
        {
            quit=true;
        }
       
        clear_window(&window);
        draw_world(&window,&world,game.view,game.score);
         draw_snake(&window,&snake, game.snakeview, &world);

        refresh_window(&window);

        SDL_Delay(300); 
    }

    free_world(&world);
    close_window(&window);
    return 0;
}