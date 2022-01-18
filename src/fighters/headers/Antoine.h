#ifndef FIGHTERS_Antoine_H
#define FIGHTERS_Antoine_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Antoine: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Antoine();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_Antoine_H