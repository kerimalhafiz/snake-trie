#ifndef WORLD_HPP
#define WORLD_HPP

#include "window.hpp"

#include "enum.hpp"
#include <iostream>

using namespace std;


struct World
{
    int width;//largeur
    int height;//hauteur
    Block*grid;
 
};


void init_world(World* world, int w, int h);
void free_world(World* world);
Block read(World* world, int x, int y);
void write(World* world, int x, int y, Block b);
void add_food(World* world, int x, int y, Block type);
void init_food(World *world,int number_food);
#endif
