#include "gestionevent.hpp"



// la fonction sert à gerer les evenements en fonction de la touche appuyée
bool handle_event(Game *game,string filename){
    SDL_Event event;
    while (SDL_PollEvent(&event)!=0)
    {
         if (event.type==SDL_QUIT)
         {
              return true;
         }
         else if(event.type==SDL_KEYDOWN){
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                if (game->snake->diremplacement != South)
                 game->snake->diremplacement = North;
                break;
            case SDLK_DOWN:
                if (game->snake->diremplacement != North) 
                game->snake->diremplacement = South;
                break;
            case SDLK_LEFT:
                if (game->snake->diremplacement != East)
                 game->snake->diremplacement = West;
                break;
            case SDLK_RIGHT:
                if (game->snake->diremplacement != West) 
                game->snake->diremplacement = East;
                break;
            case SDLK_q:
            return true;
            case SDLK_s:
            if( save_game(game,filename))
               return true;
              break;
            case SDLK_ESCAPE:
                change_statut(game);
            break;
            case SDLK_l:
            if (load_game(game, filename)) {  
                draw_text(game->window, "Jeu charge avec succes", 100, 100);  
                refresh_window(game->window); 
                 SDL_Delay(1000); 
            } else {
                draw_text(game->window, "Erreur de chargement du jeu.", 100, 100);  
                refresh_window(game->window); 
                SDL_Delay(1000); 
            }
            break;             
            default:
                break;
            }
         }
    }
    return false;
    
}
