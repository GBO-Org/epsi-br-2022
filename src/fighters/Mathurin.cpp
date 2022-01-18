#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Mathurin.h"

using namespace std;

Mathurin::Mathurin() : FighterBot("Mathurin", 15, 15, 0) {
    this->targetId = "";
}

bool Mathurin::anybody_on(int x, int y, Arena arena) {
    vector<Fighter> fighters = arena.get();
    bool anybody = true;
    for (Fighter fighter : fighters){
        if (fighter.getX() == x && fighter.getY() == y){
            anybody = false;
        }
    }
    return anybody;
}

Fighter Mathurin::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    if (this->targetId == "") {
        bool onlyMathurin = true;
        for (Fighter fighter : fighters) {
            if (fighter.getName() != "Mathurin") {
                onlyMathurin = false;
                break;
            }
        }
 
        int distanceMin = 1000;
        int xMe = this->getX();
        int yMe = this->getY();
        int xOther = 0;
        int yOther = 0;
        int distX = 0;
        int distY = 0;
        int distTotal = 0;
        string idMe = this->getId();
        if (onlyMathurin) {
            for (Fighter fighter : fighters) {
                if (fighter.getId() != idMe) {
                    xOther = fighter.getX();
                    yOther = fighter.getY();
                    distX = abs(xMe - xOther);
                    distY = abs(yMe - yOther);
                    distTotal = distX + distY;
                    if (distTotal < distanceMin){
                        target = fighter;
                    }
                }
            }
        } else {
            for (Fighter fighter : fighters) {
                if (fighter.getName() != "Mathurin") {
                    xOther = fighter.getX();
                    yOther = fighter.getY();
                    distX = abs(xMe - xOther);
                    distY = abs(yMe - yOther);
                    distTotal = distX + distY;
                    if (distTotal < distanceMin){
                        target = fighter;
                    }
                }
            }
        }
        this->targetId = target.getId();
        this->display(" désigne comme cible " + target.getNameId());

    } else {
        bool found = false;
        for (Fighter fighter : fighters) {
            if (fighter.getId() == this->targetId) {
                target = fighter;
                found = true;
            }
        }
        if (!found) {
            this->targetId = "";
            target = this->selectTarget(arena);
        }
    }

    return target;
}

Action* Mathurin::choose(Arena arena) {
    Action* action = nullptr;

    Fighter target = this->selectTarget(arena);

    if (this->getLife() > 20){
        if (target.isHere(this)) {
        action = new ActionAttack(target);

        } else {
            action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
        }
    }
    else {
        //on recupère notre position et les dimensions de l'arène
        int xMe = this->getX();
        int yMe = this->getY();
        int xMax = arena.getWidth();
        int yMax = arena.getHeight();
        //on choisis une case ou personne n'est pour se déplacer
        if (this->anybody_on(xMe,(yMe-1), arena)){
            action = new ActionMove(xMe, (yMe-1));
        }
        else if (this->anybody_on((xMe-1),(yMe-1), arena) && xMe>1 && yMe>1){
            action = new ActionMove((xMe-1),(yMe-1));
        }
        else if (this->anybody_on((xMe+1),(yMe-1), arena) && xMe<(xMax-2) && yMe>1){
            action = new ActionMove((xMe+1),(yMe-1));
        }
        else if (this->anybody_on((xMe-1),yMe, arena) && xMe>1){
            action = new ActionMove((xMe-1),yMe);
        }
        else if (this->anybody_on((xMe+1),yMe, arena) && xMe<(xMax-2)){
            action = new ActionMove((xMe+1),yMe);
        }
        else if (this->anybody_on(xMe,(yMe+1), arena) && yMe<(yMax-2)){
            action = new ActionMove(xMe,(yMe+1));
        }
        else if (this->anybody_on((xMe-1),(yMe+1), arena) && xMe>1 && yMe<(yMax-2)){
            action = new ActionMove((xMe-1),(yMe+1));
        }
        else if (this->anybody_on((xMe+1),(yMe+1), arena) && xMe<(xMax-2) && yMe<(yMax-2)){
            action = new ActionMove((xMe+1),(yMe+1));
        }
        else{
            action = new ActionMove((xMe+1),(yMe+1) && xMe<(xMax-2) && yMe<(yMax-2));
            action = new ActionMove((xMe-1),(yMe-1) && xMe<1 && yMe<1);
        }
    }
    
    return action;
}
