#ifndef FIGHTERS_TEXIER_T
#define FIGHTERS_TEXIER_T

#include <iostream>

#include "FighterBot.h"

using namespace std;


class Texier: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);
    
public:
    Texier();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_TEXIER_T
