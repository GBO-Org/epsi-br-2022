#ifndef FIGHTERS_GRAVY_H
#define FIGHTERS_GRAVY_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Gravy: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);
    Fighter selectTarget(Arena arena, int x, int y);

public:
    Gravy();

    virtual Action* choose(Arena arena);
};

class Enemy {
    private : 
    int x;
    int y;

    public : 
    int getX();
    int getY();

    Enemy(int x, int y);

};

#endif //FIGHTERS_GRAVY_H
