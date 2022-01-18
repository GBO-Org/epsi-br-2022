#ifndef FIGHTERS_MAGALIE_H
#define FIGHTERS_MAGALIE_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Magalie: public FighterBot {
private:
    virtual Action* escape(Arena arena);
    Fighter selectEscape(Arena arena);
    bool anybodyHere(vector<Fighter> fighters);

public:
    Magalie();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_MAGALIE_H