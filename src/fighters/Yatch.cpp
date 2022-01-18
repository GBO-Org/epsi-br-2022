#include <algorithm>
#include <iostream>
#include <math.h>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Yatch.h"

using namespace std;

// Principe du bot Yatch :
// tout les Yatchs se regroupent et attendent qu'un autre fighter vienne sur eux
// une fois un autre fighter sur eux ils l'attaquent
// si ils ne font pas d'actions depuis 50 tours alors il se dirigent vers la cible la plus proche et l'attaquent
// et une fois qu'il ne reste plus que des Yatchs ils s'attaquent entre eux pour qu'il ne reste plus qu'un Yatch !

Yatch::Yatch() : FighterBot("Yatch", 25, 5, 0) 
{
    this->targetId = "";
}

Fighter Yatch::selectTarget(Arena arena) 
{
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    int DistanceFighterCloser = 1000;
    int DistanceFighterCurrent = 0;

    //si nous avons pas de cible nous en choisissons une
    if (this->targetId == "")
    {
        //si notre bot répète des actions nulles
        if (actionnull == 50)
        {
            DistanceFighterCloser = 1000;

            for (int i = 0; i < fighters.size(); i++)
            {
                DistanceFighterCurrent = sqrt(pow((this->getX() - fighters[i].getX()), 2) + pow((this->getY() - fighters[i].getY()), 2));

                //alors nous sélectionnons le fighter le plus proche qui n'est pas un Yatch comme cible
                if(DistanceFighterCloser > DistanceFighterCurrent && fighters[i].getName() != "Yatch" && !fighters[i].isMe(this))
                {
                    DistanceFighterCloser = DistanceFighterCurrent;
                    target = fighters[i];
                }
            }
            
        } else
        {
            DistanceFighterCloser = 1000;

            for (int i = 0; i < fighters.size(); i++)
            {
                DistanceFighterCurrent = sqrt(pow((this->getX() - fighters[i].getX()), 2) + pow((this->getY() - fighters[i].getY()), 2));
                
                //sinon nous sélectionnons un Yatch comme cible
                if(DistanceFighterCloser > DistanceFighterCurrent && fighters[i].getName() == "Yatch" && !fighters[i].isMe(this)) 
                {
                    DistanceFighterCloser = DistanceFighterCurrent;
                    target = fighters[i];
                }
            }
        }

        //on retiens l'id de notre cible
        this->targetId = target.getId();
    
    //si nous avons déjà une cible nous regardons si elle est encore présente dans l'arène
    } else
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
        //si il n'est plus dans l'arène
        if (!found) 
        {
            //on l'oublie
            this->targetId = "";
            //et on choisi une nouvelle cible
            target = this->selectTarget(arena);
        }
    }
    
    return target;
}

Action* Yatch::choose(Arena arena) 
{
    Action* action = nullptr;
    vector<Fighter> fighters = arena.get();

    //nous retrouvons notre cible
    Fighter target = this->selectTarget(arena);

    //si nous avons atteind notre cible
    if (target.isHere(this))
    {
        //est-ce qu'il reste autre chose que des Yatch dans l'arène
        bool onlyYatch = true;
        for (Fighter fighter : fighters) 
        {
            if (fighter.getName() != "Yatch") 
            {
                onlyYatch = false;
                break;
            }
        }

        //si oui nous nous attaquons entre nous
        if (onlyYatch)
        {
            for (Fighter fighter : fighters)
            {
                action = new ActionAttack(target);
            }
        
        //sinon si il reste d'autres bots
        } else
        {
            //nous oublions notre cible
            this->targetId = "";

            for (Fighter fighter : fighters)
            {
                //et si un autre fighter qu'un Yatch nous atteind
                if (fighter.isHere(this) && fighter.getName() != "Yatch")
                {
                    //nous l'attaquons
                    action = new ActionAttack(fighter);
                } 
            } 
        }

    //sinon nous nous dirigeons vers notre cible
    } else 
    {
        action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    }
    
    //si notre action est nulle
    if (action == nullptr)
    {
        //alors nous ajoutons +1 dans le compteur d'action nulle
        actionnull ++;
    }
    
    return action;
}
