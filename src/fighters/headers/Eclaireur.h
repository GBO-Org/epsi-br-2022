#pragma once

#include <iostream>

#include "FighterBot.h"

using namespace std;

class Eclaireur: public FighterBot {
public:
    Eclaireur();

    virtual Action* choose(Arena arena);
};
