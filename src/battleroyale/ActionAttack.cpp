#include <iostream>

#include "ActionAttack.h"

using namespace std;

ActionAttack::ActionAttack(Fighter fighter) : Action("Attack") {
    this->targetId = fighter.getId();
    this->targetName = fighter.getNameId();
}

string ActionAttack::getDisplay() {
    return "Attack " + this->targetName;
}

bool ActionAttack::isValid() {
    // On retrouve le Fighter effectif dans les Fighters
    this->target = nullptr;
    for (Fighter* fighter : this->fighters) {
        if (fighter->getId() == this->targetId) {
            this->target = fighter;
            break;
        }
    }
    // On vérifie que la cible est bien dans la même case que l'attaquant */
    return (this->target != nullptr) &&
            this->fighter->isHere(this->target->getX(), this->target->getY());
}

void ActionAttack::perform() {
    // On tabasse
    this->fighter->assault(this->target);
}
