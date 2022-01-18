#ifndef FIGHTERS_YOHANE_H
#define FIGHTERS_YOHANE_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Yohane: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    Yohane();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_YOHANE_H
