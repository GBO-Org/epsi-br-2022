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
    bool goodPos;
};

// TODO faire la doc sur mes fonctions et classes, surtout class Enemy et 
// fonction selectTarget(Arena arena, int x, int y)

/*
La fonction CalculatePotentialPossitions(Gravy myBot) permet de retourner un vector contenant les positions potentielles de mon bot ^^
Je me base sur le carré de 9 cases autour de la position de mon bot dans l'arene ainsi je peux savoir quelles positions il peut prendre pour le prochain tour ça 
nous servira plus tard ;) 
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
La fonction CalculatePotentialPossitions(vector<Position> enemyPositions) va quant à elle effectuer la même fonction que la fonction décrite ci-dessus à l'exception près 
que cette dernière va prendre en argument des positions dans un vector au lieu d'un bot de la classe Gravy. En l'occurrence ici les positions de tous les ennemis de l'arène
encore présents. Le fonctionnement logique étant le même que la fonction décrite ci-dessus je vous laisse remonter sur les commentaires présents sur la fonction sus-metionée pour
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

 
// Dans cette fonction je compare les 2 vectors afin de return une position faisant partie du vector "MyPotentialPos" mais ne faisant pas partie du vector "EnemyPotentialPos"
void CalculateBestPosition(vector<Position> MyPotentialPos, vector<Position> EnemyPotentialPos) {
    // J'ai ici décidé de réaliser une double boucle for qui va comparer les positions contenus dans les 2 vectors et ainsi marquer les positions viables à la survie de mon bot :) 
    for (int i = 0; i < MyPotentialPos.size(); i++)
    {
        for (int y = 0; y < EnemyPotentialPos.size(); y++)
        {
            if (MyPotentialPos[i].x != EnemyPotentialPos[y].x && MyPotentialPos[i].y != EnemyPotentialPos[y].y)
            {
                MyPotentialPos[i].goodPos = true;
            }
        }
    }
    
};

Position ChooseBestPosition(vector<Position> MyPossiblePositions) {
    for(int i = 0; i < MyPossiblePositions.size(); i++) {
        if (MyPossiblePositions[i].goodPos == true) {
            return MyPossiblePositions[i];
        }
    }
};

Fighter Gravy::findTarget (Fighter target, vector<Fighter> fighters, bool friendInArena) {

    target = randFighter(friendInArena, fighters, target);
                
    // On "scanne" l'ennemi désigné pour voir si l'on a nos chances ou pas contre lui
    while (target.getAttack() > this->getAttack() || target.getAttack() > this->getDefense() * 1.5) {
        target = randFighter(friendInArena, fighters, target);
    }

    // ...On retient son Id
    this->targetId = target.getId();
    // ...Et on le dit :)
    this->display(" désigne comme cible " + target.getNameId());
};

bool checkFriends(vector<Fighter> fighters) {
    // bool pour pas tapper les coupains
    bool Axebita = false;
    bool Teyir = false;
    bool Cam = false;
    bool Mathurin = false;

    for (Fighter fighter : fighters) {
        if (fighter.getName() != "Axebita") {
            Axebita = true;
        }
        else if (fighter.getName() != "Teyir") {
            Teyir = true;
        }
        else if (fighter.getName() != "Cam") {
            Cam = true;
        }
        else if (fighter.getName() != "Mathurin") {
            Mathurin = true;
        }
    }

    bool friendInArena;

    if (Axebita || Teyir || Mathurin || Cam) {
        friendInArena = true;
    }
}

Position Gravy::CheckPosAvailable(vector<Position> enemyPos, Gravy myBot, vector<Fighter> fighters) {
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
    
    CalculateBestPosition(MyPotentialPos, EnemyPotentialPos);

    // Maintenant que j'ai "marqué" les positions qui m'interessent je vais décider dans la fonction suivante du comportement de mon bot
    Position optimalPosition;
    optimalPosition = ChooseBestPosition(MyPotentialPos);
    
    // Dans le cas ou aucune position optimale (ou je peux me déplacer et ou l'ennemi ne peut aller) je prend une position aléatoire autour de moi ^^'
    if ((optimalPosition.x && optimalPosition.y) == NULL) {
        optimalPosition.x = MyPotentialPos[rand() % MyPotentialPos.size()].x;
        optimalPosition.y = MyPotentialPos[rand() % MyPotentialPos.size()].y;
    }

    return optimalPosition;
}

Gravy::Gravy() : FighterBot("HowBaka", 0, 0, 30) {
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
Position Gravy::selectTarget(Arena arena, int x, int y) {
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
    }
    return CheckPosAvailable(AvoidPositions, *this, fighters);
}

Fighter Gravy::randFighter (bool friendInArena, vector<Fighter> fighters, Fighter target) {
    // On ne choisit pas un coupain dans l'arene
    if (friendInArena) {
        while (target.isMe(this) || (target.getName() == "HowBaka") || (target.getName() == "Axebita") || (target.getName() == "Teyir") || (target.getName() == "Cam") || (target.getName() == "Mathurin")) {
            target = fighters[rand() % fighters.size()];
        }
    }
    else {
        target = fighters[rand() % fighters.size()];
    }
    return target;
}

Fighter Gravy::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;
        // Pas de cible retenu, on en choisit une !
        if (this->targetId == "") {
            // Reste-t-il autre chose que des Ghislain dans l'arene ?
            // Parce que bon, on va d'abord viser les autres avant de se taper dessus ^_^'
            bool onlyGravy = true;
            for (Fighter fighter : fighters) {
                if (fighter.getName() != "HowBaka") {
                    onlyGravy = false;
                    break;
                }
            }

            bool friendsInArena = 0;
            friendsInArena = checkFriends(fighters);
            findTarget(target, fighters, friendsInArena);

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

Action* Gravy::choose(Arena arena) {
    Action* action = nullptr;
    Position SafePosition;

    if (this->getLife() < 25) {
        SafePosition = this->selectTarget(arena, this->getX(), this->getY());
        this->moveTo(SafePosition.x, SafePosition.y);
    }

    else {
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
    
}