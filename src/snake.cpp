#include "snake.hpp"
// initialise le serpent 
void init_snake(Snake* snake,int x,int y,Direction dir_initiale){
   snake->head_x=x/2;// ou w
   snake->head_y=y/2;// ou heig
   snake->diremplacement=dir_initiale;
   snake->first=NULL;
   snake->second_last=NULL;

}
// la fonction sert a la gestion du mouvement de l'anneau 
void  move_anneau(Snake* snake,World *world){

    int prev_x=snake->head_x;
    int prev_y=snake->head_y;
    Anneau *current=snake->first;
    while (current!=NULL)
    {
      int tmp_x=current->anneau_x;
      int tmp_y=current->anneau_y;

        current->anneau_x=prev_x;
        current->anneau_y=prev_y;
        prev_x=tmp_x;
        prev_y=tmp_y;
        current=current->next;
    }
}
