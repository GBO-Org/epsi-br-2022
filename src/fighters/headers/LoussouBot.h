#ifndef FIGHTERS_LOUSSOUBOT_H
#define FIGHTERS_LOUSSOUBOT_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class LoussouBot: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    LoussouBot();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_GHISLAIN_H
