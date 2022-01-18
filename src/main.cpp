#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include "Arena.h"
#include "BattleRoyale.h"

#include "Alexandre.h"
#include "Altaryss.h"
#include "Amaury.h"
#include "Antoine.h"
#include "AxelBot.h"
#include "Bambouzelle.h"
#include "Dumb.h"
#include "Eline.h"
#include "Erwann.h"
#include "Ghislain.h"
#include "Gravy.h"
#include "Ines.h"
#include "LoussouBot.h"
#include "Mael.h"
#include "MagalieContant.h"
#include "Mathurin.h"
#include "Megapoi2.h"
#include "Pakbo.h"
#include "QuentinD.h"
#include "Romain.h"
#include "Texier.h"
#include "Thomas.h"
#include "Valentin.h"
#include "Yatch.h"
#include "Yohane.h"

#include "log.h"

using namespace std;

string bots[25] = { "Alexandre", "Altaryss", "Amaury", "Antoine", "Axel", "Bambouzelle", "Dumb", "Eline", "Erwann", "Ghislain", "Gravy", "Ines", "LoussouBot", "Mael", "Magalie", "Mathurin", "Megapoi2", "Pakbo", "QuentinD", "Romain", "Texier", "Thomas", "Valentin", "Yatch", "Yohane" };
int scores[25] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int nbexaequo = 0;

int main(int argc, char *argv[])
{
    loginit();
    srand(time(NULL));

    cout << "Battle Royale 2022" << endl;

    BattleRoyale* b;
    int nbTest = 1;
    int nbBot = 1;

    log("Combien de tours ? ", GREEN);
    // cin >> nbTest;
    nbTest = stoi(argv[1]);
    logln(nbTest);
    log("Combien de chaque bot ? ", GREEN);
    // cin >> nbBot;
    nbBot = stoi(argv[2]);
    logln(nbBot);
    logln("");

    int nbHumain = 0;
    int nbGhislain = 0;
    int nbDumb = 0;
    BattleRoyale* br;

    for (int i = 0; i < nbTest; i++) {
        br = new BattleRoyale(10, 1000, nbTest == 1);
        for (int j = 0; j < nbBot; j++) {
            // if (nbTest == 1) { br->recruit(new Humain); }
            br->recruit(new Alexandre);
            br->recruit(new Altaryss);
            // br->recruit(new Amaury);
            br->recruit(new Antoine);
            br->recruit(new Axel);
            br->recruit(new Bambouzelle);
            br->recruit(new Dumb);
            br->recruit(new Eline);
            br->recruit(new Erwann);
            br->recruit(new Ghislain);
            br->recruit(new Gravy);
            br->recruit(new Ines);
            // br->recruit(new LoussouBot);
            br->recruit(new Mael);
            br->recruit(new Magalie);
            br->recruit(new Mathurin);
            br->recruit(new Megapoi2);
            br->recruit(new Pakbo);
            br->recruit(new QuentinD);
            br->recruit(new Romain);
            br->recruit(new Texier);
            br->recruit(new Thomas);
            //br->recruit(new Valentin);
            br->recruit(new Yatch);
            br->recruit(new Yohane);
        }
        br->run();

        for (Fighter fighter : br->getArena().get()) {
            if (!fighter.isKO()) {
                for (int i = 0; i < 25; i++) {
                    if (fighter.getName() == bots[i]) {
                        scores[i]++;
                    }
                }
            }
        }
        if (br->getWinner() == nullptr) {
            nbexaequo++;
        }
    }

    logln("");
    logln("");
    logln("");
    logln("EX AEQUO: " + to_string(nbexaequo), GREEN);
    for (int i = 0; i < 25; i++) {
        logln(bots[i] + ": " + to_string(scores[i]), GREEN);
    }

    return 0;
}
