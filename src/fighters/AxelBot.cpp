#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "AxelBot.h"

using namespace std;

/* AxeBot est un Bot assez bourrin puisqu'il prend en chasse les ennemis qu'il peut possiblement tuer en un seul coup
Cependant, si sa vie descend trop bas, il préférera prendre la fuite pour sauver son derrière :') */

Axel::Axel() : FighterBot("Axel", 15, 5, 10) { //statistiques bourrin
    this->targetId = "";
}

Fighter Axel::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    //Pas de cible retenu, on en choisit une !
    if (this->targetId == "") {
        //Reste-t-il autre chose que des Axel dans l'arene ?
        //Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'

        bool onlyAxel = true;

        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Axel") {
                onlyAxel = false;
                break;
            }
        }

        
        // Choisissons, maintenant. . . 
        if (onlyAxel) {
            // On choisit n'importe qui d'autre dans l'arène
            while (target.isMe(this)) {
              target = fighters[rand() % fighters.size()];  
            }
        } 
        else {
            // On ne choisit pas un bro'
        
            while (target.isMe(this)|| (target.getName() == "Axel")) {
              target = fighters[rand() % fighters.size()];
        }
    }
        // ...On retient son Id
        this->targetId = target.getId();
        // ...Et on le dit :)
        this->display(" désigne comme cible " + target.getNameId());

    // Sinon, on cherche notre cible dans l'arène
    } 
    
    else {
        bool found = false;

        for (Fighter fighter : fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
                found = true;
            }
        }
        //Si on ne l'a pas trouvé (il est sorti, visiblement)
        if (!found) {
            //...On l'oublie
            this->targetId = "";
            //...Et on en choisit un nouveau
            target = this->selectTarget(arena);
        }
    }

    return target;
}


Action* Axel::choose(Arena arena) {
    Action* action = nullptr;

     // On selectionne une cible
    
  Fighter target = this->selectTarget(arena);
  vector<Fighter> fighters = arena.get();



 int  i =0 ;
// on check si il y a une personne qui peut potentiellement mourir à la prochaine attaque du AxeBot (avec un marge de sécurité)
    while(i <fighters.size()){
        
        int LifeCheck = fighters[i].getLife();

        if((LifeCheck <= this->getAttack() - 5) && (fighters[i].getName() != "Axel")){

            target = fighters[i]; //On focus ceux qu'on peut Tuer d'un seul coup 
        }
        i++;
     }


   
 
    if (target.isHere(this)) { //Sommes-nous sur la case de la cible ?

        if(this->getLife() <= 20 && target.getLife() > this->getAttack() - 5 ){ 
             action = new ActionMove(rand()%3-1,rand()%3-1 ); //On prend la fuite vers une position random 
          } 
             //mais si votre chasseur peut se faire tuer à la prochaine attaque...
        else {
             action = new ActionAttack(target); //...alors on tente de le tuer tout de même
         }
    } 

    else  {
        if(this->getLife()<=20){
            action = new ActionMove(rand()%3-1,rand()%3-1 ); 
            
        }
        else {
          action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());

        }

    }
    
    return action;
}
