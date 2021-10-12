#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include "Arena.h"
#include "BattleRoyale.h"

#include "Dumb.h"
#include "Ghislain.h"
#include "Humain.h"
#include "Alexandre.h"
#include "log.h"

using namespace std;

int main()
{
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

    int nbAlexandre = 0;
    int nbDumb = 0;
    BattleRoyale* br;

    for (int i = 0; i < nbTest; i++) {
        br = new BattleRoyale(10, 100, nbTest == 1);
        for (int j = 0; j < nbBot; j++) {
            // if (nbTest == 1) { br->recruit(new Humain); }
            //br->recruit(new Ghislain);
            br->recruit(new Dumb);
        }
        br->recruit(new Alexandre);
        br->run();

        if (br->getWinner()->getName() == "Alexandre") { nbAlexandre++; }
        if (br->getWinner()->getName() == "Dumb") { nbDumb++; }
    }

    logln("");
    logln("");
    logln("");
    logln("Alexandre = " + to_string(nbAlexandre), GREEN);
    logln("Dumb = " + to_string(nbDumb), GREEN);

    return 0;
}
