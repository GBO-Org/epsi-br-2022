#ifndef FIGHTERS_ECLAIREUR_H
#define FIGHTERS_ECLAIREUR_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Eclaireur: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Eclaireur();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_GHISLAIN_H
