#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Altaryss.h"

using namespace std;

Altaryss::Altaryss() : FighterBot("Altaryss", 1, 1, 1) {
    this->targetId = "";
}

Fighter Altaryss::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    if (this->targetId == "") {
        bool focus = false;
        string EnnemySpotted = "";
        for (Fighter fighter : fighters) {
            if (fighter.getName() == "Megapoi2") {
                focus = true;
                EnnemySpotted = "Megapoi2";
                break;
            } else if (fighter.getName() == "Val") {
                focus = true;
                EnnemySpotted = "Val";
                break;
            }
        }

        if (focus == true) {
            target.getName() == EnnemySpotted;
        } else {
            while (target.isMe(this)) {
                target = fighters[rand() % fighters.size()];
            }
        }
        this->targetId = target.getId();
        this->display(" rush " + target.getNameId());

    } else {
        bool found = false;
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

Action* Altaryss::choose(Arena arena) {
    Action* action = nullptr;

    Fighter target = this->selectTarget(arena);

    if (target.isHere(this)) {
        action = new ActionAttack(target);

    } else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}
