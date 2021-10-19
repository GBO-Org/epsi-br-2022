#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include "Arena.h"
#include "BattleRoyale.h"

#include "Dumb.h"
#include "Altaryss.h"
#include "Humain.h"
#include "log.h"

using namespace std;

int main()
{
    loginit();
    srand(time(NULL));

    cout << "Battle Royale 2022" << endl;

    BattleRoyale* b;
    int nbTest = 1;
    int nbBot = 1;

    log("Combien de tours ? ", GREEN);
    cin >> nbTest;
    logln("");
    log("Combien de chaque bot ? ", GREEN);
    cin >> nbBot;
    logln("");
    logln("");

    int nbHumain = 0;
    int nbAltaryss = 0;
    int nbDumb = 0;
    BattleRoyale* br;

    for (int i = 0; i < nbTest; i++) {
        br = new BattleRoyale(10, 100, nbTest == 1);
        for (int j = 0; j < nbBot; j++) {
            // if (nbTest == 1) { br->recruit(new Humain); }
            br->recruit(new Altaryss);
            br->recruit(new Dumb);
        }
        br->run();

        if (br->getWinner()->getName() == "Altaryss") { nbAltaryss++; }
        if (br->getWinner()->getName() == "Dumb") { nbDumb++; }
    }

    logln("");
    logln("");
    logln("");
    logln("Altaryss = " + to_string(nbAltaryss), GREEN);
    logln("Dumb = " + to_string(nbDumb), GREEN);

    return 0;
}
