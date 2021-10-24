#include <algorithm>
#include <iostream>
#include <math.h>

#include "Fighter.h"
#include "ActionMove.h"
#include "ActionAttack.h"
#include "Pakbo.h"

using namespace std;



Pakbo::Pakbo() : FighterBot("Pakbo", 13, 13, 4) {
    this->targetId = "";
}

Fighter Pakbo::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this; 

    //si pas de cible on choisit une
    if (this->targetId == "") {
        // On check s'il reste que des pakbo et si oui on ne prend pas de cible
        bool onlyPakbo = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Pakbo") {
                onlyPakbo = false;
                break;
            }
        }

        double closerDistance = 0.0;
        double distance = 0.0;
        if (onlyPakbo)
        {
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
        }
        else
        {
            while (target.isMe(this) || (target.getName() == "Pakbo")) {
                target = fighters[rand() % fighters.size()];
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

Action* Pakbo::choose(Arena arena) {
    Action* action = nullptr;
    // S'il reste des joueurs on retrouve notre cible
    Fighter target = this->selectTarget(arena);

    vector<Fighter> fighters = arena.get();

    bool onlyPakbo;
    for (Fighter fighter : fighters) {
        if (fighter.getName() != "Pakbo") {
            onlyPakbo = false;
            break;
        }
    }
    
    if (onlyPakbo)
    {
        // s'il ne reste que des pakbos, on vérifie s'ils sont tous sur la meme case
        // this->targetId = "";
        // bool isHere = true;
        // for (Fighter fighter : fighters) {
        //     if (!fighter.isHere(this))
        //     {
        //         isHere = false;
        //         break;
        //     }
        // }
        if (!target.isHere(this))
        {
            action = new ActionMove(5, 5);
        }
        else
        {
            action = new ActionAttack(target);
        }   
    }
    else {

        // Sommes-nous sur la case de la cible ?
        if (target.isHere(this)) {
            action = new ActionAttack(target);

        // Sinon, allons-y !
        } else {
            action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
        }
    }

    return action;
}