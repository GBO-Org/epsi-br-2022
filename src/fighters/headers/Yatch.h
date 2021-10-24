#ifndef FIGHTERS_YATCH_H
#define FIGHTERS_YATCH_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Yatch: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Yatch();

    int actionnull = 0;

    virtual Action* choose(Arena arena);
};

#endif
