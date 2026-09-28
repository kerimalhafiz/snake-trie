#include "world.hpp"
using namespace std;
#include <iostream>
#include <new>
#include <fstream>


//initialisation du monde
void init_world(World* world,int w,int h){

world->height = h;
world->width = w;
world->grid = new Block[h*w];

for (int i=0;i<h*w;i++){
    world->grid[i] = Empty;
}
}
// la fonction sert à liberer la mémoire allouée pour le monde
void free_world(World* world){
        delete []world->grid;
    
}
// la fonction sert à lire le monde

Block read(World* world, int x, int y){
      if (x<0|| x>=world->width|| y<0 || y>=world->height)
      {
           cout<<"erreur"<<x<<","<<y;
           return Empty;
      }
         int i=y*world->width+x;
         return world->grid[i];
      
}
// la fonction sert à écrire dans le monde
void write(World* world, int x, int y, Block b){
    if (x<0|| x>=world->width|| y<0 || y>=world->height)
      {
           cout<<"erreur"<<x<<","<<y;
      }
      int i=y*world->width+x;
      world->grid[i]=b;// l'ecriture 
}
// la fonction sert à ajouter de la nourriture au monde
void add_food(World*World,int x,int y,Block type){
    if (x<0 ||x>=World->width || y<0 || y>=World->height)
    {
        cout<<"erreur"<<endl;
        return;
    }
    
   write(World,x,y,type);// ecriture de la nourriture
} 

// ajouter de la nourriture en position aleatoire en fonction de la taille du monde et appel la fonction add_food
void init_food(World*world,int number_food){
    Block tabfood[] = {GreenFood, RedFood, BlueFood, StarFood};
    for (int i = 0; i < number_food; i++) {
        int x = rand() % world->width;
        int y = rand() % world->height;
        
        // S'assurer que la case n'est pas déjà occupée par un autre type de nourriture
        while (read(world, x, y) != Empty) {
            x = rand() % world->width;
            y = rand() % world->height;
        }

        // choisir le type de nourriture qui a ete mangeé dans une position aleatoire 
        
        add_food(world, x, y, tabfood[i]);
    }
    
}
