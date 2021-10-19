#include <algorithm>
#include <iostream>
#include <math.h>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Valentin.h"

using namespace std;

Valentin::Valentin() : FighterBot("Valentin", 5, 10, 15) {
    this->hunterId = "";
}

Fighter Valentin::selectHunter(Arena arena) {

    vector<Fighter> fighters = arena.get();
    Fighter hunter = *this;


    bool onlyValentin = true;
    for (Fighter fighter : fighters){
         if (fighter.getName() != "Valentin"){
            onlyValentin = false;
            break;
        }
    }
    if (onlyValentin) {
        // On choisit n'importe qui d'autre dans l'arène
        while (hunter.isMe(this)) {
            hunter = fighters[rand() % fighters.size()];
        }
    }else{
        while (hunter.isMe(this) || (hunter.getName() == "Valentin"))
        {
            float distance = sqrt( pow(arena.getHeight(),2) + pow(arena.getWidth(),2) );
            for(Fighter possibleHunter : fighters){
                if(possibleHunter.getId() != this->getId()){
                    float possibleDistance = sqrt( pow((possibleHunter.getX() - this->getX()),2) + pow((possibleHunter.getY() - this->getY()),2));
                    if (distance > possibleDistance)
                    {
                        distance = possibleDistance;
                        hunter = possibleHunter;
                    }                        
                }
            }
        }    
    }

    return hunter;
    
}

Action* Valentin::choose(Arena arena){
    Action* action = nullptr;

    Fighter hunter = this->selectHunter(arena); 
    
    action = new ActionMove(this->getX()-hunter.getX(),this->getY()-hunter.getY());
    action->setArena(&arena);
    action->setFighter(this);
    if (!action->isValid())
    {
        action = new ActionMove(this->getX()-hunter.getX(),this->getY());
        action->setArena(&arena);
        action->setFighter(this);
        if (!action->isValid()){
            action = new ActionMove(this->getX(),this->getY()-hunter.getY());
            action->setArena(&arena);
            action->setFighter(this);
        }
    }
    
    
    while(!action->isValid()){
        action = new ActionMove(rand() % 3 - 1,rand() % 3 - 1);
        action->setArena(&arena);
        action->setFighter(this);
    }
    if(hunter.isHere(this) ){
        action = new ActionAttack(hunter);   
    }

    return action;
}
