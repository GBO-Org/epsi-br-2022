#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Yohane.h"

using namespace std;

Yohane::Yohane() : FighterBot("Yohane", 10, 8, 9) {
    this->targetId = "";
    this->setStatus("Ready to win"); //Pour mettre un peu l'ambiance dans l'arene
}

Fighter Yohane::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get(); //il prend une cible parmi les fighters de l'arene
    Fighter target = *this;

    // Pas de cible retenu, on en choisit une !
    if (this->targetId == "") {
        // Reste-t-il autre chose que des Yohane dans l'arene ?
        
        // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
        bool onlyYohane = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Yohane") {
                onlyYohane = false;
                break;
            }
        }

        // Choisissons, maintenant. . . 
        if (onlyYohane) {
            // On choisit n'importe qui d'autre dans l'arène
            while (target.isMe(this)) {
                target = fighters[rand() % fighters.size()];
            }
        }  
        for (Fighter fighter : fighters)
        {
            //on choisit celui qui a la défense la plus faible 
            if (fighter.getDefense() < target.getDefense()&& fighter.isMe(this)==0)
            {
                target = fighter;
            }
            // ...On retient son Id
        this->targetId = target.getId();
        // ...Et on le dit :)
        this->display(" désigne comme cible " + target.getNameId());
        }
        }
        // Sinon, il recherche une cible à abbatre dans l'arène
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

Action* Yohane::choose(Arena arena) {
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
