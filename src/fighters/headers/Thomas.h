#ifndef FIGHTERS_THOMAS_H
#define FIGHTERS_THOMAS_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Thomas : public FighterBot
{
public:
    Thomas();

    virtual Action *choose(Arena arena);

private:
    string targetId;
    Action *goForTarget(Arena arena);
    Fighter selectTarget(Arena arena);
};

#endif //FIGHTERS_THOMAS_H