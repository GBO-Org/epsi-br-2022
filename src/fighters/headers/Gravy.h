#ifndef FIGHTERS_GRAVY_H
#define FIGHTERS_GRAVY_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Gravy: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);
    Position selectTarget(Arena arena, int x, int y);
    Fighter randFighter(bool friendInArena, vector<Fighter> fighters, Fighter target);
    Fighter findTarget(Fighter target, vector<Fighter> fighters, bool friendInArena);
    Position CheckPosAvailable(vector<Position> enemyPos, Gravy myBot, vector<Fighter> fighters);

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
