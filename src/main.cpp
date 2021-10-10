#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include "Arena.h"
#include "BattleRoyale.h"

#include "Dumb.h"
#include "Ghislain.h"
#include "Humain.h"
#include "log.h"

using namespace std;

struct Stat {
    string botName;
    int nbWin = 0;
};

int main()
{
    loginit();
    srand(time(NULL));

    cout << "Battle Royale 2022" << endl;

    BattleRoyale* b;
    int nbTest = 1;
    int nbBot = 1;

    log("Combien de BattleRoyale ? ", GREEN);
    cin >> nbTest;
    logln("");
    log("Combien d'instance de chaque bot ? ", GREEN);
    cin >> nbBot;
    logln("");
    logln("");

    bool found;
    BattleRoyale* br;
    vector<Stat> stats;

    for (int i = 0; i < nbTest; i++) {
        br = new BattleRoyale(10, 100, nbTest == 1);
        for (int j = 0; j < nbBot; j++) {
            // br->recruit(new Humain);
            br->recruit(new Ghislain);
            br->recruit(new Dumb);
        }
        br->run();

        // Calcul des statistiques
        found = false;
        for (int i = 0; i < stats.size(); i++) {
            if (stats[i].botName == br->getWinner()->getName()) {
                stats[i].nbWin++;
                found = true;
                break;
            }
        }
        if (!found) {
            Stat stat;
            stat.botName = br->getWinner()->getName();
            stat.nbWin = 1;
            stats.push_back(stat);
        }

        // Affichage des statistiques
        logln("");
        logln("");
        log("Statistiques après ", GREEN);
        log(i + 1, BLUE);
        logln(" BR :", GREEN);
        for (Stat stat : stats) {
            log(stat.botName, BLUE);
            log(" = ");
            log(stat.nbWin, RED);
            logln(" victoires !");
        }
        delete br;
    }

    return 0;
}
