#include <algorithm>
#include <iostream>
#include <vector>

#include "Action.h"
#include "BattleRoyale.h"
#include "Fighter.h"
#include "log.h"

using namespace std;

/** Les constructeurs et leur valeurs par défaut */
BattleRoyale::BattleRoyale(int size) : BattleRoyale(size, 1000, false) {}
BattleRoyale::BattleRoyale(int size, int roundLimit) : BattleRoyale(size, roundLimit, false) {}
BattleRoyale::BattleRoyale(int size, int roundLimit, bool pause) {
    this->size = size;
    this->roundLimit = roundLimit;
    this->pause = pause;
    this->winner = nullptr;
    this->arena = new Arena(size, size);
}

/** Le desctructeur nettoie le this->arena et tous les bots !! */
BattleRoyale::~BattleRoyale() {
    delete this->arena;
    for (FighterBot* bot : this->bots) {
        delete bot;
    }
}

Arena BattleRoyale::getArena() { return (*this->arena); }
vector<FighterBot*> BattleRoyale::getKos() { return this->kos; }
FighterBot* BattleRoyale::getWinner() { return this->winner; }

void BattleRoyale::recruit(FighterBot* fighter) {
    // On positionne aléatoirement notre Fighter dans l'arène
    fighter->moveTo(rand() % this->size, rand() % this->size);
    // ...Et on l'ajoute dans toutes nos listes ^_^'
    this->arena->add(fighter);
    this->bots.push_back(fighter);
}

int BattleRoyale::nbFighterAlive() {
    int count = 0;
    for (int i = 0; i < this->bots.size(); i++) {
        if (this->bots[i]->getLife() > 0) {
            count++;
        }
    }
    return count;
}

void BattleRoyale::run() {
    int round = 1;
    // On fait autant de round qu'il est possible d'en faire (le roundLimit est notre limite)
    while (this->nbFighterAlive() > 1 && round < this->roundLimit) {
        logln("");
        log("#####  ROUND ", GREEN);
        log(round, WHITE);
        logln("  #####", GREEN);
        // Affichage de l'arène avant le ROUND
        this->arena->display();
        // On joue le ROUND
        this->runRound();
        // On sort les Fighter KO de l'arène
        this->cleanArena(round);
        // Enfin : Incrémentons du round...
        round++;
        if (this->pause) {
            // ...Puis petite pause pour l'être humain qui regarde.
            log("Appuyez sur entrée . . . ", BLUE);
            cin.ignore();
        }
    }

    // Déclaration de victoire du dernier survivant
    logln("");
    logln("");
    logln("#####  FIN DE LA BATAILLE !  #####", GREEN);
    logln("");
    for (FighterBot* bot : this->bots) {
        if (!bot->isKO()) {
            bot->display("", false);
            logln(" est déclaré vainqueur en " + to_string(round-1) + " rounds !!", BLUE);
            logln("");
            logln("");
            // On retient le winner
            this->winner = bot;
            break;
        }
    }
}

void BattleRoyale::runRound() {
    // On retrie notre liste de bot à chaque tour :
    random_shuffle(this->bots.begin(), this->bots.end());
    sort(this->bots.begin(), this->bots.end(), Fighter::compare);

    for (FighterBot* bot : this->bots) {
        // Ne jouent que les bots non KO
        if (!bot->isKO()) {
            this->runRoundFighter(bot);
        }
    }
}

void BattleRoyale::runRoundFighter(FighterBot* bot) {
    // Demandons à notre bot ce qu'il veut faire . . . 
    Action* action = bot->choose(this->getArena());
    // Il renvoie nullptr : il ne veut visiblement rien faire
    if (action == nullptr) {
        bot->display(" ne fait rien . . .");
    } else {
        bot->display(" choisit " + action->getDisplay());
        // On construit la liste des fighters non KO
        vector<Fighter*> fighters;
        for (FighterBot* bot : this->bots) {
            if (!bot->isKO()) {
                fighters.push_back(bot);
            }
        }
        // On remplit l'action avec tout le nécessaire à son execution
        action->setArena(this->arena);
        action->setFighters(fighters);
        action->setFighter(bot);
        // On vérifie que le choix est valide
        if (action->isValid()) {
            // Et on l'exécute !
            action->perform();
        } else {
            // ...Sinon, on indique qu'on exécutera pas l'action
            logln("Action interdite !!", RED);
        }
        delete action;
    }
}

void BattleRoyale::cleanArena(int round) {
    for (FighterBot* bot : this->bots) {
        // Les bots KO et toujours dans l'arène
        if (bot->isKO() && this->arena->contains(bot)) {
            // ...sont retirés
            bot->display("", false);
            logln(" est évacué de l'arène...", RED);
            this->arena->remove(bot);
            // Gestion de la liste des KO
            bot->setKoRound(round);
            this->kos.push_back(bot);
        }
    }
}