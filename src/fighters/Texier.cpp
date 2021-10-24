#include <algorithm>
#include <iostream>

#include <cstring>


#include "ActionMove.h"
#include "ActionAttack.h"
#include "Texier.h"

using namespace std;


//Stats (30)
int statAttack = 10;
int statDefense = 15;
int statSpeed = 5;
                         
Texier::Texier() : FighterBot("Texier", statAttack, statDefense, statSpeed){//attaque, défense, vitesse
    this->targetId = "";
    this->setStatus("TACT");
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
            
        // On choisit une cible    
        if (onlyFans){
            //On choisit n'importe qui d'autre dans l'arène
            while (target.isMe(this)){
                
                target = fighters[rand() % fighters.size()];

            }
        }else {
            //On tape pas la Tact Team (Et moi même au passage)
            while (target.isMe(this) || (target.getName() == "Texier") || (target.getStatus() == "TACT") || (target.getName() == "Axebita") || (target.getName() == "Gravy") || (target.getName() == "Cam") || (target.getName() == "Mathurin")) {
                target = fighters[rand() % fighters.size()];
            }
        } 
        //Sélection de l'Id de la cible + affichage
        this->targetId = target.getId();
        this->display(" part éclater le beaut " + target.getNameId());
        
    //Sinon, on cherche notre cible
    }else{
        bool found = false;
        for (Fighter fighter : fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
                found = true;
            } 
        }
        //Si on ne l'a pas trouvé 
        if  (!found){
            //On choisie une nouvelle cible
            this->targetId = "";
            target = this->selectTarget(arena);
        }
    }

    return target;

}

Action* Texier::choose(Arena arena){
    vector<Fighter> fighters = arena.get();
    bool hasAttacked = false;
    Action* action = nullptr;

    //On retrouve notre cible
    Fighter target =  this->selectTarget(arena);

    //On fuit car on est des lâches et on change de cible
    if (this->getLife() <= 15)
    {

        action = new ActionMove(this->getX() - rand() % 3 - 1, this->getY() - rand() % 3 - 1);

        //On change de cible bien évidement on oublie la TactTeam (pour le moment)
        while (target.isMe(this) || target.isHere(this) || (target.getName() == "Texier") || (target.getStatus() == "TACT") || (target.getName() == "Axebita") || (target.getName() == "Gravy") || (target.getName() == "Cam") || (target.getName() == "Mathurin"))
        {
           target = fighters[rand() % fighters.size()];
            
        }  

    }
    

    //On vérifie si on est sur la case de la cible, si oui on l'attaque
    if (target.isHere(this)){
     
        action = new ActionAttack(target);
        hasAttacked = true;


    //Si la cible à des stats qui nous correspondent pas on choisit une nouvelle cible et on fuit !!!!!
    }else if(target.getAttack() >= 10 && target.getDefense() >= 15){

        target = fighters[rand() % fighters.size()];
        action = new ActionMove(rand() % 3 - 1,rand() % 3 - 1);
        hasAttacked = false;

    }else if(target.isHere(this) && target.getStatus() == "TACT" && target.getLife() <= 10){ //Si le target est un Tact et qu'il à - 10 HP on va lui abréger ses souffrances 0_0

        action = new ActionAttack(target);
        this->display("Deso pas deso..."  + target.getNameId());

    }else if(target.isHere(this) && hasAttacked){// Si on attaqué on part de la case

        action = new ActionMove(rand() % 3 - 1,rand() % 3 - 1);
    

    }else{//Sinon on part ailleurs 

        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
        hasAttacked = false;
    }

    return action;
    
}