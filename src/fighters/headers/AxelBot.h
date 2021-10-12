#ifndef FIGHTERS_AXEL_H
#define FIGHTERS_AXEL_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Axel: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Axel();

    virtual Action* choose(Arena arena);
};

#endif 
