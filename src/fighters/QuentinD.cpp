#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "QuentinD.h"
#include "log.h"

using namespace std;

QuentinD::QuentinD() : FighterBot("QuentinD", 14, 0, 16) {
    this->targetId = "";
    this->setStatus("Enervé");
}

bool QuentinD::TargetPresence(Arena arena, int i, int j) {  // Creation de la fonction qui va nous permetre de savoir si il y a des bots autour de nous
    ActionMove* action = new ActionMove(i,j); //Crée une action comme pour se deplacer pour savoir si il y a quelquen
        action->setArena(&arena);
        action->setFighter(this);
    vector<Fighter> list = arena.get(i, j); //Prend la liste des bots present autour de ma case
    return ((list.size() < 1) && (action->isValid())); // Return true si la liste est vide et que l'action est valide (Le bot ne fait rien)
}
/*
Fighter QuentinD::selectTarget(Arena arena) { //Creation de la fonction qui nous permet de selectionner une cible quand il ne reste qu'un joueur
    vector<Fighter> fighters = arena.get(); //creation 
    bool oneleft = false;
    Fighter target = *this;

    if (fighters.size() == 1) {
        bool oneleft = true;
        Fighter target = *this;
    }
    return target;
}
*/
Action* QuentinD::choose(Arena arena) { // la fonction qui va nous faire le choix entre courir et se battre
    Action* action = nullptr;
    Fighter target = *this; //attribution de ma target en fonction de select
    vector<Fighter> fighters = arena.get();
    bool Playerfound = false; // Booléen qui change si il y a un fighter sur la même case que le bot

    for (Fighter fighter : arena.get(this)) { //pour tout les fighters qui sont sur la même case que le bot
            if (!fighter.isMe(this)) { // Si le fighter est un autre fighter que moi
                Playerfound = true; // Passage de joueurtrouvé en true
            }  
    }
    if(Playerfound == true && fighters.size() > 1 ){ // si nous trouvons un joueur mais qu'il reste plus d'un joeueur en jeu
        for (int i = -1; i < 2; i++) { //alors je prepare ma fuite 
            for (int j  = -1; j < 2; j++) { //pareil dans l'autre direction
                if(TargetPresence(arena,i,j)){ //Lance la fonction VerifFighter, et fait le if si il return "true"
                    action = new ActionMove(i,j); //Deplace le bot sur une case non utilisé
                }
            }
        }              
    } else if (fighters.size() == 1 && (target.isHere(this))) { //sinon si il reste un seul bot et qu'il est accessible
            action = new ActionAttack(target); //on le tape
            } else if (fighters.size() == 1 && (!target.isHere(this))) { //sinon si il est un seul bot et qu'il n'est pas accessible
                    action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY()); //on bouge vers lui
        }
        return action;
    }