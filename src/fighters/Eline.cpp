#include <algorithm>
#include <iostream>
#include <string>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Eline.h"

using namespace std;

//initialisation du bot 
Eline::Eline() : FighterBot("Eline", 10, 5, 15) {
    this->targetId = "";
    this->myLife = this->getLife();
    this->oldLife = myLife;
}

Fighter Eline::selectTarget(Arena arena){
    //on récupère les fighters présents dans l'arène
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    //on choisit une cible si nous n'en avons pas 
    if (this->targetId == "") {
        //on choisit au hasard
        //attention il peut se choisir lui-même
        target = fighters[rand() % fighters.size()];
        this->targetId = target.getId();
        this->display( target.getNameId() + " j'arrive ! ");
    } else {
        //si on a déjà une cible on la cherche dans l'arène
        for (Fighter fighter : fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
            } else {
            //on réinitialise la cible
            this->targetId = "";
            //on relance une recherche
            target = this->selectTarget(arena);
            }
            break;
        }
    }

    return target;
}


Action* Eline::choose(Arena arena) {
    Action* action = nullptr;

    //on récupère sa vie
    this->myLife = this->getLife();

    //s'il a perdu de sa vie  
    if (oldLife>myLife){
        //il s'enfuie donc se déplace aléatoirement
        //il n'a plus de cible
         this->targetId = "";
         action = new ActionMove(rand()%3-1, rand()%3-1);
         this->display("Aïe ! fuyons !");
    } else {
        //sinon on suit une cible 
        //on la selectionne
        Fighter target = this->selectTarget(arena);
        if (target.isHere(this)) {
            //si elle est sur notre case on l'attaque
            action = new ActionAttack(target);
        } else {
            //sinon on va à sa rencontre
            action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
        }
    }

    //on remplace l'ancienne vie par la nouvelle
    oldLife=myLife;
    return action;
}


