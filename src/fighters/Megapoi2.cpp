#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Megapoi2.h"

using namespace std;
//Ceci est un bot invinsible, comme ca celui-ci ne peut pas perdre 
//A la fin des rounds il sera déclaré gagnant car il a tout ses points de vie
Megapoi2::Megapoi2() : FighterBot("Megapoi2", 0, 0, 30) {
    this->targetId = "";
}


bool Megapoi2::VerifFighter(Arena arena, int i, int j) { 
    ActionMove* action = new ActionMove(i,j); //Crée une action comme si le bot allait se déplacer dans la case séléctionné
    action->setArena(&arena); 
    action->setFighter(this); 
    std::vector<Fighter> list = arena.get(this->getX()+i,this->getY()+j); //Prend la liste des fighter qui sont sur la case
    return ((list.size() < 1) && (action->isValid())); // Return true si la liste est vide et que l'action est valide (Le bot reste dans l'arène)
                    

}

Action* Megapoi2::choose(Arena arena) {
    Action* action = nullptr; // Initialise l'action
    bool DangerSurCase = false; // Booléen qui change si il y a un fighter sur la même case que le bot

    for (Fighter fighter : arena.get(this)) { //for pour tout les fighter sur la même case que le bot
            if (!fighter.isMe(this)) { // Si le fighter est un autre fighter que le bot
                
                DangerSurCase = true; // Variable qui dit qu'il y a un fighter sur la case
           

            }  
    }

    if(DangerSurCase == true){
        for (int i = -1; i < 2; i++) {
            for (int j  = -1; j < 2; j++) {   
                
                
                if(VerifFighter(arena,i,j)){ //Lance la fonction VerifFighter, et fait le if si il return "true"
                    action = new ActionMove(i,j); //Deplace le bot sur une case non utilisé
                }
            }
        }              
    }
    return action; 
}
