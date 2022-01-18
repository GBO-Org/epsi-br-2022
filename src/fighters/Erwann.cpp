#include <iostream>
#include <algorithm>
#include <math.h>
#include "ActionMove.h"
#include "ActionAttack.h"

#include "Erwann.h"

using namespace std;

Erwann::Erwann() : FighterBot("Erwann", 14, 8, 8) {
    this-> targetId = "";
}

Fighter Erwann::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;
    // Pas de cible retenu, on en choisit une !
    if (this->targetId == "") {
        // On évite de se taper dessus donc on va choisir une cible autre que les "Erwann"
        bool onlyEclaireur = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Erwann") {
                onlyEclaireur = false;
                break;
            }
        }

        double closerDistance = 0.0;
        double distance = 0.0;
            while (target.isMe(this)) {
                for (size_t i = 0; i < fighters.size(); i++)
                {
                    int xB = fighters[i].getX();
                    int yB = fighters[i].getY();
                    distance = sqrt(pow((this->getX() - xB), 2.0) + pow((this->getY() - yB), 2.0));
                    if (i == 0) 
                    {
                        closerDistance = distance;
                        target = fighters[i];
                    }
                    if (distance < closerDistance) 
                    {
                        closerDistance = distance;
                        target = fighters[i];
                    }
                }
            }

        this->targetId = target.getId();
        this->display(" désigne comme cible " + target.getNameId());

    } 
    else {
        bool found = false;
        for (Fighter fighter : fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
                found = true;
            }
        }
        // Si on ne l'a pas trouvé (il est sorti, visiblement)
        if (!found) {
            // ...On l'oublie
            this->targetId = "";
            // ...Et on en choisit un nouveau
            target = this->selectTarget(arena);
        }
    }

    return target;
}


Action* Erwann::choose(Arena arena) {
    Action* action = nullptr;
    for (Fighter fighter : arena.get(this)) {
        if (!fighter.isMe(this)) {
            action = new ActionAttack(fighter);
            break;
        }
    }
    return action;
}