#ifndef ENUM_HPP
#define ENUM_HPP
    
enum Direction {
    North,  // Nord  //equivalent de up le haut

    South,  // Sud  // equivalent de down

    East,   // Est  // equivalent de left
    West    // Ouest // equivalent de right
};


enum Block {
    Empty,       // Case vide
    RedFood,
    GreenFood,
    BlueFood,
    StarFood
};
enum Statut{
    Begin,Play,Pause,Win,GameOver
};
#endif
