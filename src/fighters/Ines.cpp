// Ines BOUCARD 
// 24/10/2021 
// B2

// on inclut toutes les bibliothèques et fichiers dont on a besoin 
#include <algorithm>
#include <iostream>
#include "ActionMove.h"
#include "ActionAttack.h"
#include "Ines.h"

using namespace std;

// Ines a :
// - 20 d'attaque
// - 5 de défense 
// - 5 de vitesse 
Ines::Ines() : FighterBot("Ines", 20, 5, 5) {
    // Ines n'a pas de cible 
    this->targetId = "";
    this->setStatus("content");
}

Fighter Ines::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    // Ines n'a pas de cible, donc elle va en choisir une 
    if (this->targetId == "") {
        
        
        bool onlyInes = true;
        // Si le fighter n'est pas Ines, on met la variable onlyInes à false
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Ines") {
                onlyInes = false;
                break;
            }
        }

        // Ines choisis 
        if (onlyInes) {
            // On prend un fighter au hasard si il n'y a que des Ines dans l'arene 
            while (target.isMe(this)) {
                target = fighters[rand() % fighters.size()];
            }
        } 
        // Si il y a d'autre fighter que des Ines dans l'arene 
        // Ines prend pour cible le fighter le plus proche
        else {
            // On initialise le meilleur ecart possible entre Ines et un fighter
            double MeilleurecartTotal = 19;
            // On regarde pour tout les fighters, leurs distances avec Ines
            for (Fighter fighter1 : fighters) {
            // Ines ne prend pas pour cible une autre Ines
            if (fighter1.getName() != "Ines") {
            double ecartX = 0;
            double ecartY = 0;
            double ecartTotal = 0;
            double MeilleurEcartX = 0;
            double MeilleurEcartY = 0;
                
                
            ecartX = abs(this->getX()) - abs(fighter1.getX());
            ecartY = abs(this->getY()) - abs(fighter1.getY());
            // L'écart total est la distance en x et en y entre Ines et un fighter additionnée
            ecartTotal = abs(ecartX) + abs(ecartY);

            // Si l'écart total est plus petit que le meilleur écart total, Ines prend ce fighter 
            // pour cible 
                    if(ecartTotal < MeilleurecartTotal){
                        
                        MeilleurEcartX = ecartX;
                        MeilleurEcartY = ecartY;
                        target = fighter1;
                        MeilleurecartTotal = ecartTotal;
                    } 
                }
            }
         
        }
        // On retient l'Id de la cible
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
            // On la cible
            this->targetId = "";
            // Et on en choisit une autre cible
            target = this->selectTarget(arena);
        }
    }

    return target;
}

Action* Ines::choose(Arena arena) {
    Action* action = nullptr;

    // On retrouve notre cible
    Fighter target = this->selectTarget(arena);

    // Sommes-nous sur la case de la cible ?
    if (target.isHere(this)) {
        action = new ActionAttack(target);

    // Sinon, allons-y !
    } else {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}
