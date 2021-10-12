#ifndef BATTLEROYALE_FIGHTERBOT_H
#define BATTLEROYALE_FIGHTERBOT_H

#include <iostream>

#include "Action.h"
#include "Arena.h"
#include "Fighter.h"

using namespace std;

/** FighterBot abstrait
 * Déclinaison du Fighter qui peur prendre des décisions */
class FighterBot : public Fighter {
private:
    /** Le round de KO */
    int koRound;
    /** le statut*/

public:
    /** Constructeur */
    FighterBot(string name, int attack, int defense, int speed);

    /** Accesseurs (getters) / mutateurs (setters) */
    int getKoRound();
    void setKoRound(int koRound);

    /** Méthode abstraite de choix de l'action */
    virtual Action* choose(Arena arena) = 0;
};

#endif //BATTLEROYALE_FIGHTERBOT_H
