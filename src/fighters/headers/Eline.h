#ifndef FIGHTERS_ELINE_H
#define FIGHTERS_ELINE_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Eline: public FighterBot {
private:
    string targetId;
    int myLife;
    int oldLife;
    Fighter selectTarget(Arena arena);

public:
    Eline();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_ELINE_H
