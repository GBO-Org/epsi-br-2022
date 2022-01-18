#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Bambouzelle.h"

using namespace std;

Bambouzelle::Bambouzelle() : FighterBot("Bambouzelle", 12, 6, 12) {
    this->targetId = "";
}

Fighter Bambouzelle::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    bool found = false;
    Fighter target = *this;
    int j = 0;
        // choisir une cible sur la map
        for (int i = 0 ; i < fighters.size() ; i++)
        {
            int personne_proche = 255; // on met une valeur beaucoup trop haut pour être sur que la valeur change 
            
            int search = this->getX() - fighters[i].getX() + this->getY() - fighters[i].getY();
            if (search < 0)
            search = -search; 
            if (search < personne_proche && fighters[i].getName() != "Bambouzelle") {
                    personne_proche = search;
                    j = i;
            }  
        }  
        target = fighters[j];// on défini notre cible 
        this->targetId = target.getId(); // on chope ces position
        if ( this->getLife() > 50 ){ // todo faire gérer le condtion pour la bonne fuite de mon BOT et patch le message annonciateur
        this->display(" veut taper " + target.getNameId()); // petit message annonciateur
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

Action* Bambouzelle::choose(Arena arena) {
    Action* action = nullptr;

    Fighter target = this->selectTarget(arena);
    if (this->getLife() <= 50 && this->getX() - target.getX() + this->getY() - target.getY() != 0) // condition pour checker notre vie pour ne pas partir au suicide et que l'essaye de fuir en ne bougeant pas
    {
        action = new ActionMove(this->getX() - target.getX(), this->getY() - target.getY());
        this->display("courage fuyons " + target.getNameId());
    } else if (target.isHere(this))  { // sinon on va casser des bouches 
        action = new ActionAttack(target); 
    }  
    else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}
