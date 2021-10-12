#ifndef FIGHTERS_HUMAIN_H
#define FIGHTERS_HUMAIN_H

#include <iostream>

//#include "../src/battleroyale/headers/FighterBot.h"
#include "FighterBot.h"

using namespace std;

class Humain: public FighterBot {
public:
    Humain();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_HUMAIN_H
