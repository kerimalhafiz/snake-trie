#ifndef SNAKE_HPP
#define SNAKE_HPP
using namespace std;

#include "window.hpp"
#include "world.hpp"
#include"enum.hpp"

struct Anneau{
    int val;
    int anneau_x;
     int anneau_y;
     Anneau* next; // Pointeur vers l'anneau suivant
     Anneau* prev; // Pointeur vers l'anneau précédent
 };
struct Snake{
    int head_x;
    int head_y;
    Direction diremplacement;
    Anneau* first;             // Pointeur vers le premier anneau (queue)
    Anneau* second_last;      // Pointeur vers l'anneau juste derrière la tête
    bool mouth_open;
    int mouth_open_time;
};


void init_snake(Snake* snake,int x,int y, Direction dir_initiale);

void move_anneau(Snake*snake,World*world);
#endif