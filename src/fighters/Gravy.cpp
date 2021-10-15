#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Gravy.h"

using namespace std;

struct Position
{
    int x;
    int y;
};

// TODO faire la doc sur mes fonctions et classes, surtout class Enemy et 
// fonction selectTarget(Arena arena, int x, int y)

Position CheckPosAvailable(vector<Position> posis) {
    /*
    todo :
    - check les positions autour de moi que je peux prendre
    - check les positions à eviter dans posis
    - voir les positions restantes puis :
        . Soit une position est disponible et j'y vais : this->moveTo();
        . Soit auccune position safe n'est disponible dans ce cas :
            / Je vérifie tous les combatants autour de moi (ptet modif
            le posis pour qu'il stocke l'ennemi)
            / Et je cherche celui contre lequel j'ai le plus de chances de
            gagner et je me dirige vers lui (puique je n'ai pas d'autres choix)
    */
}

Gravy::Gravy() : FighterBot("HowBaka", 20, 10, 0) {
    this->targetId = "";
}

Enemy::Enemy(int x, int y) {
    this->x = x;
    this->y = y;
}

int Enemy::getX() {
    return this->x;
}

int Enemy::getY() {
    return this->y;
}

// Ma fonction selectTarget afin de donner plus de chances à mon bot
Fighter Gravy::selectTarget(Arena arena, int x, int y) {
    int enemyX;
    int enemyY;
    int tmp = 0;
    vector<Enemy*> enemies;
    vector<Position> AvoidPositions;
    vector<Fighter> fighters = arena.get();

    for (int i = 0; i < fighters.size(); i++) {
        enemyX = fighters[i].getX();
        enemyY = fighters[i].getY();
        if ((enemyX - 2) == x || (enemyY - 2) == y) {
            Enemy* enemy = new Enemy(enemyX, enemyY);
            enemies[tmp] = enemy;
            tmp++;
        }
        for (int z = 0; z < enemies.size(); z++) {
            int tmpX = enemies[z]->getX();
            int tmpY = enemies[z]->getY();
            AvoidPositions[z].x = tmpX;
            AvoidPositions[z].y = tmpY;
        }
        Position pos = CheckPosAvailable(AvoidPositions);
    }
}

void Gravy::run(Arena arena) {
    /* 
    J'ai décidé de faire du polymorphisme ici puisque je vais réaliser la même
    fonction mais avec une autre optique en tête ;) 
    */
    this->selectTarget(arena, this->getX(), this->getY());
}

Fighter Gravy::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    // Si j'ai plus beaucoup de vie je change de tactique
    if(this->getLife() <= 25) {
        this->run(arena);
    }

    else {
        // Pas de cible retenu, on en choisit une !
        if (this->targetId == "") {
            // Reste-t-il autre chose que des Ghislain dans l'arene ?
            // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
            bool onlyGravy = true;
            for (Fighter fighter : fighters) {
                if (fighter.getName() != "Gravy") {
                    onlyGravy = false;
                    break;
                }
            }

            // Choisissons, maintenant. . . 
            if (onlyGravy) {
                // On choisit n'importe qui d'autre dans l'arène
                while (target.isMe(this)) {
                    target = fighters[rand() % fighters.size()];
                }
            } else {
                // On ne choisit pas un bro'
                while (target.isMe(this) || (target.getName() == "HowBaka")) {
                    target = fighters[rand() % fighters.size()];
                }
            }

            // On "scanne" l'ennemi désigné pour voir si l'on a nos chances ou pas contre lui
            if (target.getAttack() > this->getAttack() || target.getAttack() > this->getDefense() * 1.5) {
                // Si l'on a pas nos chances contre cet ennemi on change de cible
                target = this->selectTarget(arena);
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
    }

    return target;
}

Action* Gravy::choose(Arena arena) {
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
