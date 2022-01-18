#ifndef FIGHTERS_ALEXANDRE_H
#define FIGHTERS_ALEXANDRE_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Alexandre: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);
    Fighter calculDistance(Fighter);

public:
    Alexandre();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_ALEXANDRE_H
