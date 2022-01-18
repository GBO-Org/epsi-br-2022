#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Antoine.h"

using namespace std;


Antoine::Antoine() : FighterBot("Antoine", 11, 5, 14) {
    this->targetId = "";
}

Fighter Antoine::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    bool found = false;
    Fighter target = *this;

        // on choisis une cible random 
            while (target.isMe(this)) {
                
                    target = fighters[rand() % fighters.size()];
                           
            }
        
        this->targetId = target.getId(); 
        if ( this->getLife() > 30 ){ 
        this->display(" veut taper " + target.getNameId());
        for (Fighter fighter : fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
                found = true;
            }
        }
        if (!found) {
            this->targetId = "";
            target = this->selectTarget(arena);
        }
    }
   return target;
}


Action* Antoine::choose(Arena arena) {
    Action* action = nullptr;

    Fighter target = this->selectTarget(arena);
    if ( this->getLife() <= 30)
    {
        action = new ActionMove(this->getX() - target.getX(), this->getY() - target.getY()); 
        this->display("oh non pitiè ne me tuez pas " + target.getNameId() + "!!!!");
    } else if (target.isHere(this))  { 
        action = new ActionAttack(target);
    }
    else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}