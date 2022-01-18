#ifndef FIGHTERS_MATHURIN_H
#define FIGHTERS_MATHURIN_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Mathurin: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

    bool anybody_on(int x, int y, Arena arena);

public:
    Mathurin();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_MATHURIN_H
