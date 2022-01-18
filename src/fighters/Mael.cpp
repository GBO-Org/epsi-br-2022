#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Mael.h"
#include <math.h>

using namespace std;


Mael::Mael() : FighterBot("Mael", 15, 15, 0) {
    this->targetId = "";
}



Fighter Mael::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    if (this->targetId == "") {
        bool onlyMael = true;
        for (int i = 0; i < fighters.size(); i++)
        {
            if (fighters[i].getName() != "Mael"){
                onlyMael = false;
                break;
            }
        }
        
        if (onlyMael) {
            int distanceEnnemiPlusProche = 1000;

            //on recupere la target la plus proche et qui n'est pas le bot en question
            for (int i = 0; i < fighters.size(); i++)
            {
                    int distanceEnnemiActuelle = sqrt(pow((this->getX() - fighters[i].getX()), 2) + pow((this->getY() - fighters[i].getY()), 2));

                    if(distanceEnnemiPlusProche > distanceEnnemiActuelle && !fighters[i].isMe(this)) {
                        distanceEnnemiPlusProche = distanceEnnemiActuelle;
                        target = fighters[i];
                    }
            }
        } else {
            //on récupère en target le joueur plus proche et qui n'est pas un collègue et pas le bot en question
            int distanceEnnemiPlusProche = 1000;

            for (int i = 0; i < fighters.size(); i++)
            {
                    int distanceEnnemiActuelle = sqrt(pow((this->getX() - fighters[i].getX()), 2) + pow((this->getY() - fighters[i].getY()), 2));

                    if(distanceEnnemiPlusProche > distanceEnnemiActuelle && fighters[i].getName() != "Mael" && !fighters[i].isMe(this)) {
                        distanceEnnemiPlusProche = distanceEnnemiActuelle;
                        target = fighters[i];
                    }
            }
        }
        // ...On retient son Id
        this->targetId = target.getId();
        // ...Et on le dit :)
        this->display(" désigne comme cible " + target.getNameId());

    // Sinon, on cherche notre cible dans l'arène
    } else {
        bool found = false;
        for (Fighter fighter : fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
                found = true;
            }
        }
        // Si on ne l'a pas trouvé (il est sorti, visiblement)
        if (!found) {
            // ...On l'oublie
            this->targetId = "";
            // ...Et on en choisit un nouveau
            target = this->selectTarget(arena);
        }
    }

    return target;
}

Action* Mael::choose(Arena arena) {
    Action* action = nullptr;
    vector<Fighter> fighters = arena.get();
    Fighter collegue = *this;

    bool someMael = false;
            for (int i = 0; i < fighters.size(); i++)
            {
                if (fighters[i].getName() == "Mael" && !fighters[i].isMe(this)){
                    someMael = true;
                    collegue = fighters[i];
                    break;
                }
            }

    //si on a moins de 30 PV
    if(this->getLife() < 30 && someMael)
    {
        Fighter target = this->selectTarget(arena);

        //si notre adversaire a moins de 20PV et qu'il est plus lent que nous en attaque, on l'achève 
        //if(target.getLife() < 20 &&  this.compare(this, target)) (ne fonctionne pas)
        if(target.getLife() < 20)
        {
            if (target.isHere(this)) {
                action = new ActionAttack(target);
            } 
            else {
                action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
            }
        }
        //sinon on fuit vers un collegue ou dans une position aléatoire si il ne reste plus personne
        else {
            if(someMael) {
                this->display(" s'enfuit vers " + collegue.getNameId());
                new ActionMove(collegue.getX() - this->getX(), collegue.getY() - this->getY());
            }
            else {
                this->display(" s'enfuit... " + collegue.getNameId());
                new ActionMove(rand() % ((1 - (-1)) + 1) + (-1), rand() % ((1 - (-1)) + 1) + (-1));
            }
            }
        }

    else {
        // On retrouve notre cible
        Fighter target = this->selectTarget(arena);
        
        //si notre cible est sur notre case on l'attaque
        if (target.isHere(this)) {
            action = new ActionAttack(target);
        //sinon on va vers lui
        } else {
            action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
        }
    }
    

    return action;
}
