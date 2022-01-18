#include <algorithm>
#include <iostream>
#include <math.h>

#include "BattleRoyale.h"
#include "ActionMove.h"
#include "ActionAttack.h"
#include "cleplubo.h"


//le but est de créer un bot full defensif qui mettra peu de dégat mais qui resistera beaucoup pour essayer d'aller en final
cleplubo::cleplubo() : FighterBot("cleplubo", 3, 27, 0) {
    this->targetId = "";
}

Fighter cleplubo::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    int distancefighter;
    // si je n'ai pas encore de target et qu'il reste plus de 2 participant  
        if (this->targetId == "" && fighters.size() > 2)
        {
            //Tout d'abord on selectionne la target la plus proche de nous qui n'est pas moi et qui ne s'apelle pas cleplubo
            for (int i = 0; i < fighters.size(); i++)
            {
                    distancefighter= 1000;
                    int distanceFighterActuelle = sqrt(pow((this->getX() - fighters[i].getX()), 2) + pow((this->getY() - fighters[i].getY()), 2));

                    if(distancefighter > distanceFighterActuelle && !fighters[i].isMe(this) && fighters[i].getName() != "cleplubo")
                     {
                        distancefighter = distanceFighterActuelle;

                        target = fighters[i];

                        
                    }
            }
            //on récuper le nom de notre target et on l'affiche
            this->targetId = target.getId();
            this->display(" désigne comme cible " + target.getNameId());
        }
        //Sinon on choisit n'importe qui meme si c'est un collegue 
        else 
            {
                for (int i = 0; i < fighters.size(); i++){
                    distancefighter= 1000;
                    int distanceFighterActuelle = sqrt(pow((this->getX() - fighters[i].getX()), 2) + pow((this->getY() - fighters[i].getY()), 2));

                    if(distancefighter > distanceFighterActuelle && !fighters[i].isMe(this) )
                     {
                        distancefighter = distanceFighterActuelle;

                        target = fighters[i];
                    }
                    
                }
            //on récuper le nom de notre target et on l'affiche
            this->targetId = target.getId();
            this->display(" désigne comme cible " + target.getNameId());
            }

    return target;
}

Action* cleplubo::choose(Arena arena) {
    Action* action = nullptr;
    vector<Fighter> fighters = arena.get();

    Fighter target = this->selectTarget(arena);

    for (Fighter fighter : fighters)
    {
        //Si il rest plus 2 participant on applique notre strategie 
        if (fighters.size() > 2)
        {
            //Tant qu'il nous reste la moitié des points de vie on peut se battre sinon on fuie
            if (this->getLife() >= 50)
            {
                //Tant qu'il ne reste pas 2 participant on attaque pas les collègues
                if (target.isHere(this) && (target.getName() != "cleplubo"))
                {
                    action = new ActionAttack(target);

                }
                else {action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());}

            }
            else {action = new ActionMove(target.getX() + this->getX(), target.getY() + this->getY());} 
        }
        //Si il reste que 2 participant et qu'il se trouve sur ma case je le dégomme sinon je me déplace vers lui
        else {
            if (target.isHere(this)) {
            action = new ActionAttack(target);
             } 
            else {
                action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
            }
        }
     }
    
    this->targetId = "";

    return action;
}

    // De base je voulais faire un bot qui fuit à l'opposer de l'ennemi le plus proche malheureusement je n'ai pas réussi à le faire fonctionner
    //Le probleme est que mon bot s'active les 2/3 premier tours puis ne fait plus rien après...

    // if((target.getX() >= 0) && (target.getY() >= 0)){
     
    //  if ((this->getX()-1  && this->getX() <= arena.getWidth()) && (this->getY()-1 && this->getY() <= arena.getHeight())){
    //      action = new ActionMove(-1,-1);
    //    }
    // }

    // else if((target.getX() <= 0) && (target.getY() >= 0)){
        
    //  if ((this->getX()+1  && this->getX() < arena.getWidth()) && (this->getY()-1  && this->getY() < arena.getHeight())){
    //         action = new ActionMove(1,-1);   
    //     }
    // }

    // else if((target.getX() >= 0 && target.getY() <= 0)){
     
    //  if ((this->getX()-1  && this->getX() < arena.getWidth()) && (this->getY()+1  && this->getY() < arena.getHeight())){
    //         action = new ActionMove(-1,1);
    //     }
    // }

    // else if((target.getX() <= 0 && target.getY() <= 0)){
     
    //      if ((this->getX()+1  && this->getX() < arena.getWidth()) && (this->getY()+1 && this->getY() < arena.getHeight())){
    //         action = new ActionMove(1,1);   
    //     }
    // }        
    // else action = new ActionMove(rand() % 3 - 1,rand() % 3 - 1);