#ifndef FIGHTERS_Altaryss_H
#define FIGHTERS_Altaryss_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Altaryss: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Altaryss();

    virtual Action* choose(Arena arena);
};

#endif
