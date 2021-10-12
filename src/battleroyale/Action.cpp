#include <iostream>

#include "Action.h"
#include "log.h"

using namespace std;

Action::Action(string name) {
    this->name = name;
}

Action::~Action() { }

string Action::getName() { return this->name; }
void Action::setArena(Arena* arena) { this->arena = arena; }
void Action::setFighters(vector<Fighter*> fighters) { this->fighters = fighters; }
void Action::setFighter(Fighter* fighter) { this->fighter = fighter; }

string Action::getDisplay() { return this->getName(); }
void Action::display() { log(this->getDisplay()); }
