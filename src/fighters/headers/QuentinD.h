#ifndef FIGHTERS_QUENTIND_H
#define FIGHTERS_GUENTIND_H

#include <iostream>

#include "FighterBot.h"

using namespace std;

class QuentinD: public FighterBot {
private:
    string targetId;

    Fighter selectTarget(Arena arena);

public:
    QuentinD();

    virtual Action* choose(Arena arena);
    bool TargetPresence(Arena arena, int i, int j);
};

#endif //FIGHTERS_QUENTIND_H
