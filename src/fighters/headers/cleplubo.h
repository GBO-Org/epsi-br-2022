#ifndef FIGHTERS_CLEPLUBO_H
#define FIGHTERS_CLEPLUBO_H

#include <iostream>

#include "FighterBot.h"

using namespace std;


class cleplubo: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);
public:
    cleplubo();

    virtual Action* choose(Arena arena);
};

#endif 