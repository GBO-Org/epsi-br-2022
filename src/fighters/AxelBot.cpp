#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "AxelBot.h"

using namespace std;

Axel::Axel() : FighterBot("Axel", 9, 20, 1) {
    this->targetId = "";
}

Fighter Axel::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    // Pas de cible retenu, on en choisit une !
    if (this->targetId == "") {
        // Reste-t-il autre chose que des Ghislain dans l'arene ?
        // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
        bool onlyAxel = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Axel") {
                onlyAxel = false;
                break;
            }
        }

        // Choisissons, maintenant. . . 
        if (onlyAxel) {
            // On choisit n'importe qui d'autre dans l'arène
            while (target.isMe(this)) {
                target = fighters[rand() % fighters.size()];
            }
        } else {
            // On ne choisit pas un bro'
            while (target.isMe(this) || (target.getName() == "Axel")) {
                target = fighters[rand() % fighters.size()];
            }
        }
        // ...On retient son Id
        this->targetId = target.getId();
        // ...Et on le dit :)
        this->display(" désigne comme cible " + target.getNameId());

    // Sinon, on cherche notre cible dans l'arène
    } else {
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

Action* Axel::choose(Arena arena) {
    Action* action = nullptr;

    // On retrouve notre cible
    Fighter target = this->selectTarget(arena);

    // Sommes-nous sur la case de la cible ?
    if (target.isHere(this)) {
        action = new ActionAttack(target);

    // Sinon, allons-y !
    } else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}
