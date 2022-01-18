#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Amaury.h"

using namespace std;

/*Mon bot est un bot défensif il préfera fuir que d'aller au combat, cependant si l'occasion se présente d'aller 
attaquer un advesaire il ne va pas s'en priver, il va d'ailleurs essayer d'attaquer en premier mais il n'est pas rapide
donc si sa vie descend en dessous de 80% il va fuir comme un lâche*/

Amaury::Amaury() : FighterBot("Amaury", 4, 25, 1) { //stats défensive avec une bonne défense et une force de bébé Cadum
    this->targetId = "";
}

Fighter Amaury::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

        //Pas de cible retenu, on en choisit une !
    if (this->targetId == "") {
        //Reste-t-il autre chose que des Amaury dans l'arene ? pour taper les autres d'abord 
        
               bool onlyAmaury = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Amaury") {
                onlyAmaury = false;
                break;
            }
        }


        //Choissisons maintenant 
        if (onlyAmaury) {
            //On choisist n'importe qui d'autre dans l'arène 
            while (target.isMe(this)) {
                target = fighters[rand() % fighters.size()];
            }
        } else {

            //On ne chosit pas un frère 
            while (target.isMe(this) || (target.getName() == "Amaury")) {
                target = fighters[rand() % fighters.size()];
            }
        }
        //On retiens sont ID 
        this->targetId = target.getId();
        //et on l'annonce 
        this->display(" va tabasser " + target.getNameId());


    //sinon on choisit une autre cible dans l'arène 
    } else {
        bool found = false;
        for (Fighter fighter : fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
                found = true;
            }
        }
        //si on ne l'a pas trouvé 
        if (!found) {
            //on l'oublie 
            this->targetId = "";
            //...Et on en choisit un nouveau 
            target = this->selectTarget(arena);
        }
    }

    return target;
}

Action* Amaury::choose(Arena arena) {
    Action* action = nullptr;

//on sélectionne une cible 
  Fighter target = this->selectTarget(arena);
  vector<Fighter> fighters = arena.get();
  bool hasAttacked=false;  


 if (target.isHere(this)) { //Sommes-nous sur la case de la cible ?
while (this->getLife() <= 80 )
{
            action = new ActionAttack(target);//On tape l'adversaire tant que notre vie est supérieure a 80
              hasAttacked=true;
}



        if(this->getLife() <= 80 ){ 
             action = new ActionMove(rand()%3-1,rand()%3-1 ); //On prend la fuite vers une position aléatoire dans l'arène 
          } 

               //mais si on peut tuer notre chasseur a la prochaine attaque
        else {
             action = new ActionAttack(target); //alors on le démonte 
         }

    return action;
}
    }