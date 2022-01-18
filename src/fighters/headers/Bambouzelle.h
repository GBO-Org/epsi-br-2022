#ifndef FIGHTERS_BAMBOUZELLE_H
#define FIGHTERS_BAMBOUZELLE_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Bambouzelle: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Bambouzelle();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_BAMBOUZELLE_H
