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

/*
La fonction CalculatePotentialPossitions(Gravy myBot) permet de retourner un 
vector contenant les positions potentielles de mon bot ^^
Je me base sur le carré de 9 cases autour de la position de mon bot dans l'arene
ainsi je peux savoir quelles positions il peut prendre pour le prochain tour
ça nous servira plus tard ;) 
*/
vector<Position> CalculatePotentialPositions(Gravy myBot) {
    int tmpX = -1;
    int tmpY = -1;
    vector<Position> posAvalable;
    // J'initialise les varables dont j'ai besoin pour calculer les positions
    // que je peux prendre dans l'arene
    for (int a = 0; a <= 8; a++) {
        posAvalable[a].x = myBot.getX() - tmpX;
        posAvalable[a].y = myBot.getY() - tmpY;
        tmpX++;
         // ici je prend ma position en X et Y et je lui enlève un nombre entre
         // -1 et 1 afin de pouvoir calculer toutes les options s'offrant à mon
         // bot en termes de déplacements
        if (a == 2 || a == 5) {
            tmpX = 0;
            tmpY++;
            // J'incrémente la valeur enlevée à X à chaque itération du for,
            // et une fois que j'ai atteint la fin de la ligne X que
            // mon personnage peut effectuer, je remet la valeur que j'enlève
            // à X à 0 et j'incrémente la valeur enlevée à Y pour passer à la ligne
            // horizontale suivante
        }
    }
    return posAvalable;
}
/*
La fonction CalculatePotentialPossitions(vector<Position> enemyPositions) va quant
à elle effectuer la même fonction que la fonction décrite ci-dessus à l'exception
près que cette dernière va prendre en argument des positions dans un vector au lieu
d'un bot de la classe Gravy. En l'occurrence ici les positions de tous les ennemis
de l'arène encore présents.

Le fonctionnement logique étant le même que la fonction décrite ci-dessus je vous
laisse remonter sur les commentaires présents sur la fonction sus-metionée pour
comprendre le fonctionnement de la fonction suivante.
*/
vector<Position> CalculatePotentialPositions(vector<Position> enemyPositions) {
    int tmpX = -1;
    int tmpY = -1;
    vector<Position> posAvalable;
    for (int b = 0; b < enemyPositions.size(); b++) {
        for (int a = 0; a <= 8; a++) {
            posAvalable[a].x = enemyPositions[b].x - tmpX;
            posAvalable[a].y = enemyPositions[b].y - tmpY;
            tmpX++;
            if (a == 2 || a == 5) {
                tmpX = 0;
                tmpY++;
            }
        }
    }
    return posAvalable;
}

/* 
 Dans cette fonction je compare les 2 vectors afin de return une position 
 faisant partie du vector "MyPotentialPos" mais ne faisant pas partie 
 du vector "EnemyPotentialPos"
*/
Position CalculateBestPosition(vector<Position> MyPotentialPos, vector<Position> EnemyPotentialPos) {

};

Position CheckPosAvailable(vector<Position> enemyPos, Gravy myBot) {
    /*
    todo :
    x - check les positions autour de moi que je peux prendre
    x - check les positions à eviter dans posis
    - voir les positions restantes puis :
        . Soit une position est disponible et j'y vais : this->moveTo();
        . Soit auccune position safe n'est disponible dans ce cas :
            / Je vérifie tous les combatants autour de moi (ptet modif
            le posis pour qu'il stocke l'ennemi)
            / Et je cherche celui contre lequel j'ai le plus de chances de
            gagner et je me dirige vers lui (puique je n'ai pas d'autres choix)
    */

    // Calcul des positions que mon bot peut prendre
    vector<Position> MyPotentialPos;
    MyPotentialPos = CalculatePotentialPositions(myBot);

    // Calcul des positions que peuvent prendre les ennemis encore présents
    // dans l'arene
    vector<Position> EnemyPotentialPos;
    EnemyPotentialPos = CalculatePotentialPositions(enemyPos);

    // Je compare les résultat des 2 fonctions précédentes pour décider
    // de la position la plus optimale à la survie de mon bot
    Position bestPosition;
    bestPosition = CalculateBestPosition(MyPotentialPos, EnemyPotentialPos);

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
        Position pos = CheckPosAvailable(AvoidPositions, *this);
    }
}

Fighter Gravy::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    // Si j'ai plus beaucoup de vie je change de tactique
    if(this->getLife() <= 25) {
        /* 
        J'ai décidé de surcharger la fonction selectTarget ici puisque je vais
        choisir une cible mais avec une autre optique en tête :)
        */
        this->selectTarget(arena, this->getX(), this->getY());
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
