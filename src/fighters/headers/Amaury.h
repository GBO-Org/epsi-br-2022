#ifndef FIGHTERS_AMAURY_H
#define FIGHTERS_AMAURY_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Amaury: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Amaury();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_AMAURY_H
