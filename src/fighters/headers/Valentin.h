#ifndef FIGHTERS_VALENTIN_H
#define FIGHTERS_VALENTIN_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Valentin: public FighterBot {
private:
    string hunterId;

    Fighter selectHunter(Arena arena);
public:
    Valentin();

    virtual Action* choose(Arena arena);
};

#endif //FIGHTERS_VALENTIN_H
