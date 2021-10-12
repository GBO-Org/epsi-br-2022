#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Texier.h"

using namespace std;
                         
Texier::Texier() : FighterBot("Texier", 15, 7, 8){//attaque, défense, vitesse
    this->targetId = "";
}

Fighter Texier::selectTarget(Arena arena){
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    if (this->targetId == ""){

        bool onlyFans = true;
        for (Fighter fighter : fighters){
            if (fighter.getName() != "Texier"){
                onlyFans = false;
                break;
            }    
        }

        if (onlyFans){
            while (target.isMe(this)){
                target = fighters[rand() % fighters.size()];
            }
            
        } else {
            while (target.isMe(this) || (target.getName() == "Texier")) {
                target = fighters[rand() % fighters.size()];
            }
        }
        this->targetId = target.getId();
        this->display(" vient de désigner comme cible " + target.getNameId());
        

    }else{
        bool found = false;
        for (Fighter fighter : fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
                found = true;
            } 
        }
        if  (!found){
            this->targetId = "";
            target = this->selectTarget(arena);
        }
    }

    return target;

}

Action* Texier::choose(Arena arena){
    Action* action = nullptr;

    Fighter target =  this->selectTarget(arena);

    //On vérifie si on est sur la case de la cible, si oui on l'attaque
    if (target.isHere(this)){

        action = new ActionAttack(target);

    //Sinon on part ailleurs 
    }else{

        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    
    }

    return action;
    
}