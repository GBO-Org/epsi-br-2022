#ifndef FIGHTERS_MAEL_H
#define FIGHTERS_MAEL_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Mael: public FighterBot {
private:
    string targetId;
    Fighter selectTarget(Arena arena);

public:
    Mael();

    virtual Action* choose(Arena arena);
    //Determine si il reste d'autre bot "Mael"
    
};

#endif //FIGHTERS_GHISLAIN_H
