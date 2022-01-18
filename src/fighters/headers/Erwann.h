#ifndef FIGHTERS_ERWANN_H
#define FIGHTERS_ERWANN_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Erwann: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Erwann();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_ERWANN_H
