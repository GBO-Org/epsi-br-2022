#include <algorithm>
#include <iostream>
#include <math.h>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Valentin.h"

using namespace std;

Valentin::Valentin() : FighterBot("Valentin", 15, 0, 15) {
    this->hunterId = "";
}

Fighter Valentin::selectHunter(Arena arena) {

    cout << "test";
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

    Action* possibilite1 = new ActionMove(this->getX()-hunter.getX(),this->getY()-hunter.getY());
    possibilite1->setArena(&arena);
    possibilite1->setFighter(this);
    Action* possibilite2 = new ActionMove(rand() % 3 - 1,rand() % 3 - 1);
    possibilite2->setArena(&arena);
    possibilite2->setFighter(this);
    Action* possibilite3 = new ActionAttack(hunter);
    
    action = possibilite1;
    
    if( (this->getX()-hunter.getX())==0 && (this->getY()-hunter.getY())==0){
    action = possibilite2;
    }
    if(!action->isValid() && hunter.isHere(this) ){
        action = possibilite3;   
    }

    if(action == possibilite1){
        action = new ActionMove(this->getX()-hunter.getX(),this->getY()-hunter.getY());
    }else if(action == possibilite2){
        action = new ActionMove(rand() % 3 - 1,rand() % 3 - 1);
    }

    return action;
}
