#ifndef FIGHTERS_PAKBO_H
#define FIGHTERS_PAKBO_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Pakbo : public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Pakbo();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_GHISLAIN_H
