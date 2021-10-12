#ifndef FIGHTERS_GRAVY_H
#define FIGHTERS_GRAVY_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Gravy: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Gravy();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_GRAVY_H
