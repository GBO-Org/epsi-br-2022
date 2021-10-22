#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Thomas.h"

using namespace std;

Thomas::Thomas() : FighterBot("Thomas", 15, 15, 0)
{
}

Action *Thomas::choose(Arena arena)
{
    vector<Fighter> fighters = arena.get();
    ActionAttack *actionatt = nullptr;
    ActionMove *actionmv = nullptr;
    for (Fighter fighter : arena.get(this))
    {
        if (fighters.size() == 2)
        {
            return actionatt = new ActionAttack(fighter);
        }
        else
        {
            if (fighter.isMe(this))
            {
                return actionmv = new ActionMove(fighter.getX() + 5, fighter.getY() - 5);
            }
        }
    }
}