#include <iostream>
#include <algorithm>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "LoussouBot.h"

using namespace std;

LoussouBot::LoussouBot() : FighterBot("LoussouBot", 5, 12, 13) {
        this->targetId = "LB";
}

Fighter LoussouBot::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;
    // Pas de cible retenu, on en choisit une !
    if (this->targetId == "EC") {

        
        // Reste-t-il autre chose que des Ghislain dans l'arene ?
        // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
        bool onlyEclaireur = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "LoussouBot") {
                onlyEclaireur = false;
                break;
            }
        }

        // Choisissons, maintenant. . . 
        if (onlyEclaireur) {
            // On choisit n'importe qui d'autre dans l'arène
            while (target.isMe(this)) {
                target = fighters[rand() % fighters.size()];
            }
        } else {
            // On ne choisit pas un bro'
            while (target.isMe(this) || (target.getName() == "LoussouBot")) {
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


Action* LoussouBot::choose(Arena arena) {
    Action* action = nullptr;
    bool hasAttacked=false;  
    vector<Fighter> fighters = arena.get();


    // On retrouve notre cible
    Fighter target = this->selectTarget(arena);
    if(target.getName()=="LoussouBot"){
        action=new ActionMove(target.getX()-this->getX(), target.getY()-this->getY());
    }
    // Sommes-nous sur la case de la cible ?
    if (target.isHere(this)&&!hasAttacked) {
        action = new ActionAttack(target);//On tape
              hasAttacked=true;
        while (target.isMe(this) || (target.getName() == "LoussouBot")||(target.isHere(this))) {
                target = fighters[rand() % fighters.size()];
            }//Et on target un autre bot

    // Sinon, allons-y !
    }else if(target.isHere(this)&&hasAttacked){
        action=new ActionMove(this->getX()-3, this->getY()-5);
        hasAttacked=false;
    }else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}