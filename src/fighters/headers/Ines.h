#ifndef FIGHTERS_INES_H
#define FIGHTERS_INES_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Ines: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Ines();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_Ines_H
