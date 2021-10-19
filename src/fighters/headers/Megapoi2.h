#ifndef FIGHTERS_MEGAPOI2_H
#define FIGHTERS_MEGAPOI2_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Megapoi2: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Megapoi2();
    
    virtual Action* choose(Arena arena);

    bool VerifFighter(Arena arena, int i, int j);
};

#endif //FIGHTERS_MEGAPOI2_H
