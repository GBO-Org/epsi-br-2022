#include <algorithm>
#include <iostream>
#include <stdlib.h>

#include "ActionMove.h"
#include "ActionAttack.h"
#include "Thomas.h"

using namespace std;

Thomas::Thomas() : FighterBot("Thomas", 15, 15, 0)
{
    this->targetId = "";
}

Action *Thomas::choose(Arena arena)
{
    vector<Fighter> fighters = arena.get();
    Action *action = nullptr;
    Fighter target = *this;
    for (Fighter fighter : fighters)
    {
        if (fighters.size() <= 2)
        {
            target = this->selectTarget(arena);
            if (!fighter.isMe(this))
            {

                if (!target.isHere(this))
                {

                    return this->goForTarget(arena);
                }
                else
                {
                    return action = new ActionAttack(target);
                }
            }
        }
        else
        {

            if ((this->getX() - 1 >= 0 && this->getX() < arena.getWidth()) && (this->getY() - 1 >= 0 && this->getY() < arena.getHeight()))
            {
                action = new ActionMove(-1, -1);
                // case x-1 y
            }
            else if ((this->getX() - 1 >= 0 && this->getX() < arena.getWidth()) && (this->getY() >= 0 && this->getY() < arena.getHeight()))
            {
                action = new ActionMove(-1, 0);
                // case x y-1
            }
            else if ((this->getX() >= 0 && this->getX() < arena.getWidth()) && (this->getY() - 1 >= 0 && this->getY() < arena.getHeight()))
            {
                action = new ActionMove(0, -1);
                // case x+1 y+1
            }
            else if ((this->getX() + 1 >= 0 && this->getX() < arena.getWidth()) && (this->getY() + 1 >= 0 && this->getY() < arena.getHeight()))
            {
                action = new ActionMove(1, 1);
                // case x+1 y
            }
            else if ((this->getX() + 1 >= 0 && this->getX() < arena.getWidth()) && (this->getY() >= 0 && this->getY() < arena.getHeight()))
            {
                action = new ActionMove(1, 0);
                // case x y+1
            }
            else if ((this->getX() >= 0 && this->getX() < arena.getWidth()) && (this->getY() + 1 >= 0 && this->getY() < arena.getHeight()))
            {
                action = new ActionMove(0, 1);
                // case x+1 y-1
            }
            else if ((this->getX() + 1 >= 0 && this->getX() < arena.getWidth()) && (this->getY() - 1 >= 0 && this->getY() < arena.getHeight()))
            {
                action = new ActionMove(1, -1);
                // case x-1 y+1
            }
            else
            {
                action = new ActionMove(this->getX() + rand() % (1 - 5) + 1, this->getY() - rand() % (1 - 5) + 1);
            }
            return action;
        }
    }
}

Action *Thomas::goForTarget(Arena arena)
{
    Action *action = nullptr;
    vector<Fighter> fighters = arena.get();
    Fighter target = fighters[rand() % fighters.size()];
    action = new ActionMove(target.getX() - this->getX(), target.getY() - this->getY());
    return action;
}

Fighter Thomas::selectTarget(Arena arena)
{
    vector<Fighter> fighters = arena.get();
    Fighter target = *this;

    for (int i = 0; i < fighters.size(); i++)
    {
        if (!fighters[i].isMe(this))
        {
            target = fighters[i];
            break;
        }
        
    }
    this->targetId = target.getId();
    this->display(" désigne comme cible " + target.getNameId());
    return target;
}