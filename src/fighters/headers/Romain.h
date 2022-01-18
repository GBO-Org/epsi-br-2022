#ifndef FIGHTERS_ROMAIN_H
#define FIGHTERS_ROMAIN_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Romain: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Romain();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_GHISLAIN_H
