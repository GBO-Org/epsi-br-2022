#include <algorithm>
#include <iostream>
#include <vector>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "MagalieContant.h"

using namespace std;
// Grande inspiration de Gandalf le Blanc : 
                // "Vite! Fuyons!!!!!!!"
// La meilleur tactique n'est pas l'attaque mais l'esquive!
Magalie::Magalie() : FighterBot("Magalie", 5, 0, 25) {
   
}

Action* Magalie::choose(Arena arena) {
    Action* action = nullptr;
    vector<string> squadsNames;
    vector<Fighter> fighters = arena.get();
     
    //Regarder si je suis en mode esquive ou fin de partie : 
    //S'il reste, dans le tableau, au moins 2 autres types différents de combattants, je suis en mode esquive. Sinon, en mode attaque
    for (Fighter fighter:fighters){
        bool exists = false;
        for (string name:squadsNames){
            if (name == fighter.getName()){
                exists = true;
                break;
            }
        }
        if(!exists){
            squadsNames.push_back(fighter.getName());
        }
    }
    //Si que 2 types: on est que 2 sur le terrain donc attaque
    if(squadsNames.size() == 2){
        for (Fighter fighter:fighters){
            if(fighter.getName() != this->getName() 
                    && fighter.isHere(this)){
                action = new ActionAttack(fighter);
                break;
            }
        }
    }
    //Si plus que 2 bot -> en mode esquive (déplacement)
    else if (anybodyHere(fighters)){
        action = escape(arena);
    }

    return action;
}

Action* Magalie::escape(Arena arena) {
    Action* action = nullptr;
    
    // test si déplacement possible (A l'intérieur de l'arène et personne sur la case)
    // retourne l'action déplacement 
    // case x-1 y-1
    if ((this->getX()-1 >= 0 && this->getX() < arena.getWidth()) 
        && (this->getY()-1 >= 0 && this->getY() < arena.getHeight())){
        action = new ActionMove(-1, -1);
    // case x-1 y
    } else if ((this->getX()-1 >= 0 && this->getX() < arena.getWidth()) 
        && (this->getY() >= 0 && this->getY() < arena.getHeight())){
        action = new ActionMove(-1, 0);
    // case x y-1
    } else if ((this->getX() >= 0 && this->getX() < arena.getWidth()) 
        && (this->getY()-1 >= 0 && this->getY() < arena.getHeight())){
        action = new ActionMove(0, -1);
    // case x+1 y+1
    } else if ((this->getX()+1 >= 0 && this->getX() < arena.getWidth()) 
        && (this->getY()+1 >= 0 && this->getY() < arena.getHeight())){
        action = new ActionMove(1, 1);
    // case x+1 y
    } else if ((this->getX()+1 >= 0 && this->getX() < arena.getWidth()) 
        && (this->getY() >= 0 && this->getY() < arena.getHeight())){
        action = new ActionMove(1, 0);
    // case x y+1
    } else if ((this->getX() >= 0 && this->getX() < arena.getWidth()) 
        && (this->getY()+1 >= 0 && this->getY() < arena.getHeight())){
        action = new ActionMove(0, 1);
    // case x+1 y-1
    } else if ((this->getX()+1 >= 0 && this->getX() < arena.getWidth()) 
        && (this->getY()-1 >= 0 && this->getY() < arena.getHeight())){
        action = new ActionMove(1, -1);
    // case x-1 y+1
    } else{
        action = new ActionMove(-1, 1);
    } 
    
    return action;
}
//Il y a-t-il quelqu'un d'autre à cette position?
bool Magalie::anybodyHere(vector<Fighter> fighters){
    bool someoneHere = false;
    for (Fighter fighter:fighters){
        if(fighter.getName() != this->getName() && fighter.isHere(this->getX(), this->getY())){
            someoneHere = true;
            // si true, on arrete la boucle
            break;
        }
    }  
    return someoneHere;
}