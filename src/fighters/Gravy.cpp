#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Gravy.h"

using namespace std;

/*Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}*/

// TODO faire la doc sur mes fonctions et classes, surtout class Enemy et 
// fonction selectTarget(Arena arena, int x, int y)

/*
La fonction CalculatePotentialPossitions(Gravy myBot) permet de retourner un vector contenant les positions potentielles de mon bot ^^
Je me base sur le carré de 9 cases autour de la position de mon bot dans l'arene ainsi je peux savoir quelles positions il peut prendre pour le prochain tour ça 
nous servira plus tard ;) 
*/
vector<Position> CalculatePotentialPositions(Gravy myBot) {
    int tmpX = 1;
    int tmpY = 1;
    vector<Position> posAvalable;
    // J'initialise les varables dont j'ai besoin pour calculer les positions
    // que je peux prendre dans l'arene
    for (int a = 0; a < 8; a++) {
        if (myBot.getLife() == 0) {
            myBot.isKO();
        }
        Position tmpPos = {myBot.getX() - tmpX, myBot.getY() - tmpY};
        posAvalable.push_back(tmpPos);
        tmpX--;
         // ici je prend ma position en X et Y et je lui enlève un nombre entre
         // -1 et 1 afin de pouvoir calculer toutes les options s'offrant à mon
         // bot en termes de déplacements
        if (a == 2 || a == 5) {
            tmpX = 0;
            tmpY--;
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
Cette fonction permet de calculer les positions potentielles de mon bot
elle fonctionne sur le même principe que la fonction CalculateEnemyPotentialPositions
mais ici on ne calcule que les postions d'un seul bot (nous)
*/
vector<Position> CalculatePotentialPositions(Position MyPositions) {
    int tmpX = -2;
    int tmpY = -2;
    vector<Position> posAvalable;
    // Dans cette boucle je vais calculer les 9 positions que mon bot peut prendre
    for (int a = 0; a <= 8; a++) {
        int posX = MyPositions.x - tmpX;
        int posY = MyPositions.y - tmpY;
        Position tmp = {posX, posY};
        posAvalable.push_back(tmp);
        tmpX++;
        if (a == 2 || a == 5) {
            tmpX = -2;
            tmpY++;
        }
    }
    return posAvalable;
}

/*
Ici je calcule les positions potentielles des ennemis qui m'entourent
*/
vector<Position> CalculateEnemyPotentialPositions(vector<Position> Positions) {
    int tmpX = -2;
    int tmpY = -2;
    vector<Position> posAvalable;
    // Je traverse le vector contenant les positions des fighters présents dans l'arene
    for (int b = 0; b < Positions.size(); b++) {
        // Pour chacun d'entre eux je vais calculer leurs positions possibles (9 en tout)
        for (int a = 0; a <= 8; a++) {
            int posX = Positions[b].x - tmpX;
            int posY = Positions[b].y - tmpY;
            Position tmp = {posX, posY};
            posAvalable.push_back(tmp);
            tmpX++;
            // A chaque fois que j'ai fini une ligne de déplacement je vais remetre le compteur à 0 pour X et j'incrémente Y
            if (a == 2 || a == 5) {
                tmpX = -2;
                tmpY++;
            }
        }
    }
    return posAvalable;
}

 
// Dans cette fonction je compare les 2 vectors afin de return une position faisant partie du vector "MyPotentialPos" mais ne faisant pas partie du vector "EnemyPotentialPos"
void CalculateBestPosition(vector<Position>* MyPosPtr, vector<Position> MyPotentialPos, vector<Position> EnemyPotentialPos, Arena arena) {
    // J'ai ici décidé de réaliser une double boucle for qui va comparer les positions contenus dans les 2 vectors et ainsi marquer les positions viables à la survie de mon bot :) 
    vector<Position>& tmpVect = *MyPosPtr;
    for (int i = 0; i < MyPotentialPos.size(); i++)
    {
        for (int y = 0; y < EnemyPotentialPos.size(); y++)
        {
            if (MyPotentialPos[i].x != EnemyPotentialPos[y].x && MyPotentialPos[i].y != EnemyPotentialPos[y].y)
            {
                tmpVect[i].goodPos = true;
            }
            else {
                tmpVect[i].goodPos = false;
            }
        }
    }
};

Position ChooseBestPosition(vector<Position> MyPossiblePositions) {
    vector<Position> viablePositions;
    for(int tmp = 0; tmp < MyPossiblePositions.size(); tmp++) {
        if (MyPossiblePositions[tmp].goodPos == true) {
            viablePositions.push_back(MyPossiblePositions[tmp]);
        }
    }
    // Dans le cas ou aucune position viable (ou je peux me déplacer et ou l'ennemi ne peut aller) je prend une position aléatoire autour de moi ^^'
    if (viablePositions.size() == 0) {
        Position NullPos = {0, 0};
        return NullPos;
    }
    else {
        return viablePositions[rand() % viablePositions.size()];
    }
};

Fighter Gravy::randFighter (bool friendInArena, vector<Fighter> fighters, Fighter target) {
    // On ne choisit pas un coupain dans l'arene
    if (friendInArena) {
        while (target.isMe(this) || (target.getName() == "Axebita") || (target.getName() == "Teyir") || (target.getName() == "Cam") || (target.getName() == "Mathurin")) {
            target = fighters[rand() % fighters.size()];
        }
    }
    else {
        target = fighters[rand() % fighters.size()];
    }
    return target;
}

void Gravy::findTarget (Fighter target, vector<Fighter> fighters, bool friendInArena) {

    target = randFighter(friendInArena, fighters, target);
                
    // On "scanne" l'ennemi désigné pour voir si l'on a nos chances ou pas contre lui
    while (target.getAttack() > this->getAttack()) {
        target = randFighter(friendInArena, fighters, target);
    }

    if (target.getId() == this->getId()) {
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

Position Gravy::CheckPosAvailable(vector<Position> enemyPos, vector<Fighter> fighters, Arena arena) {
    // Calcul des positions que mon bot peut prendre
    vector<Position> MyPotentialPos;
    Position MyPosition = {this->getX(), this->getY()};
    MyPotentialPos = CalculatePotentialPositions(MyPosition);

    // Calcul des positions que peuvent prendre les ennemis encore présents
    // dans l'arene
    vector<Position> EnemyPotentialPos;
    EnemyPotentialPos = CalculateEnemyPotentialPositions(enemyPos);
    
    // Je compare les résultat des 2 fonctions précédentes pour décider
    // de la position la plus optimale à la survie de mon bot
    vector<Position>* MyPosPtr = &MyPotentialPos;
    CalculateBestPosition(MyPosPtr, MyPotentialPos, EnemyPotentialPos, arena);
    
    // Maintenant que j'ai "marqué" les positions qui m'interessent je vais décider dans la fonction suivante du comportement de mon bot
    Position optimalPosition;
    optimalPosition = ChooseBestPosition(MyPotentialPos);
    
    return optimalPosition;
}

Gravy::Gravy() : FighterBot("HowBaka", 10, 20, 0) {
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

// Ma fonction survive afin de donner plus de chances à mon bot
Position Gravy::survive(Arena arena, int x, int y) {
    int enemyX;
    int enemyY;
    int tmp = 0;
    vector<Enemy*> enemies;
    vector<Position> AvoidPositions;
    vector<Fighter> fighters = arena.get();
    for (int i = 0; i < fighters.size(); i++) {
        enemyX = fighters[i].getX();
        enemyY = fighters[i].getY();
        Position tmpPosition = {enemyX, enemyY};
        AvoidPositions.push_back(tmpPosition);
    }
    Position Pos = CheckPosAvailable(AvoidPositions, fighters, arena);
    return Pos;
}

Fighter Gravy::selectTarget(Arena arena) {
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;
        // Pas de cible retenu, on en choisit une !
        if (this->targetId == "") {

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
    vector<Fighter> allFighters = arena.get();

        if (this->getLife() <= 0) {
            this->isKO();
        }

        SafePosition = this->survive(arena, this->getX(), this->getY());

        // le if sert à ne pas sortir de l'arene :)
        if (SafePosition.x >= 10 || SafePosition.x < 0 || SafePosition.y >= 10 || SafePosition.y < 0) {
            SafePosition = {-SafePosition.x, -SafePosition.y};
        }

        for (int i = 0; i < allFighters.size(); i++)
        {
            if (allFighters[i].getName() != "HowBaka" && this->getLife() >= 50) {
                if (allFighters[i].getX() == this->getX() && allFighters[i].getY() == this->getY() && this->getLife() >= 50) {
                    action = new ActionAttack(allFighters[i]);
                    break;
                }
                else if (this->getLife() >= 50) {
                    action = new ActionMove(allFighters[i].getX() - this->getX(), allFighters[i].getY() - this->getY());
                    break;
                }
                else {
                    break;
                }
            }
            else {
                if (SafePosition.x == 0 && SafePosition.y == 0) {
                    // Je set la position donnée pour que je soit toujours en movement (surtout lorsque je suis encerclé ou sur la case d'un enemi
                    // je restait sur place en faisant un mouvement 0x0, j'ai alors ajouté ça pour partir loin d'un ennemi au début)
                    SafePosition.x = 1;
                    SafePosition.y = 1;
                }
                action = new ActionMove(SafePosition.x - this->getX(), SafePosition.y - this->getY());
            }
        }
    return action;
}