#include <algorithm>
#include <iostream>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Alexandre.h"

using namespace std;

Alexandre::Alexandre() : FighterBot("Alexandre", 60, 0, 0)
{
    this->targetId = "";
}

Fighter Alexandre::selectTarget(Arena arena)
{
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    // Si pas de cible enregistrer on en choisit une
    if (this->targetId == "")
    {
        target = fighters[rand() % fighters.size()];
        for (Fighter fighter : fighters)
        {
            if (fighter.getLife() < target.getLife()&& fighter.isMe(this)==0)//on choisit la personne avec le moins de vie
            {
                target = fighter;
            }
        }
        this->targetId = target.getId();
        this->display(" désigne comme cible " + target.getNameId());

        // Sinon, on trouve notre cible dans l'arène
    }
    else
    {
        bool found = false;
        for (Fighter fighter : fighters)
        {
            if (fighter.getId() == this->targetId)
            {
                target = fighter;
                found = true;
            }
        }
        // Si on ne l'a pas trouvé (il est sorti, visiblement)
        if (!found)
        {
            // ...On l'oublie
            this->targetId = "";
            // ...Et on en choisit un nouveau
            target = this->selectTarget(arena);
        }
    }



return target;
}

Action *Alexandre::choose(Arena arena)
{
    Action *action = nullptr;

    // On retrouve notre cible
    Fighter target = this->selectTarget(arena);

    // Sommes-nous sur la case de la cible ?
    if (target.isHere(this))
    {
        action = new ActionAttack(target);

        // Sinon, allons-y !
    }
    else
    {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }

    return action;
}
