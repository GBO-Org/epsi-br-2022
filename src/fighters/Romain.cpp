#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Romain.h"

using namespace std;

Romain::Romain() : FighterBot("Romain", 15, 15, 0) {
    this->targetId = "";
}





Action* Romain::choose(Arena arena) {
    srand (time(NULL));
    Action* action = nullptr;
    vector<Fighter> figthersCase = arena.get(this->getX(),this->getY());


    if (figthersCase.size() > 1){//detection si quelqun est dans ma case

        for (int i = 0; i < figthersCase.size() ; i++)
        {
            if (!figthersCase[i].isMe(this))
            {
                action = new ActionAttack(figthersCase[i]);
            }
            
        }
      
    }
    else {
    do
    {
        action = new ActionMove(rand() % 3 - 1,rand() % 3 - 1);//deplacment aleatoire
        action->setArena(&arena);
        action->setFighter(this);
    } while (!action->isValid());//verification si le deplacement ne fait pas sortir de l'arene

    }
 

    return action;
}
