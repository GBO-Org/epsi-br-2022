#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include "Arena.h"
#include "BattleRoyale.h"

#include "Dumb.h"
#include "Ghislain.h"
#include "Humain.h"
#include "Texier.h"
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
    int nbGhislain = 0;
    int nbDumb = 0;
    int nbTexier = 0;
    BattleRoyale* br;

    for (int i = 0; i < nbTest; i++) {
        br = new BattleRoyale(10, 100, nbTest == 1);
        for (int j = 0; j < nbBot; j++) {
            // if (nbTest == 1) { br->recruit(new Humain); }
            //br->recruit(new Ghislain);
            br->recruit(new Dumb);
            br->recruit(new Texier);
        }
        br->run();

       // if (br->getWinner()->getName() == "Ghislain") { nbGhislain++; }
        if (br->getWinner()->getName() == "Dumb") { nbDumb++; }
        if (br->getWinner()->getName() == "Texier") { nbTexier++; }
    }

    logln("");
    logln("");
    logln("");
    //logln("Ghislain = " + to_string(nbGhislain), GREEN);
    logln("Dumb = " + to_string(nbDumb), GREEN);
    logln("Texier = " + to_string(nbTexier), GREEN);

    return 0;
}
