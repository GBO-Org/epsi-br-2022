#ifndef BATTLEROYALE_BATTLEROYALE_H
#define BATTLEROYALE_BATTLEROYALE_H

#include <iostream>
#include <vector>

#include "Arena.h"
#include "FighterBot.h"

using namespace std;

/** BattleRoyale
 * Le système qui manipule tout !
 */
class BattleRoyale {
private:
    /** Le conteneurs de fighers... On en a plein, parce qu'il faut : */
    /** Une liste complète et officielle de tous les fighters en jeu */
    vector<FighterBot*> bots;
    /** Une liste de tous les fighters KO dans leur ordre de KO. Pour les statistiques à posteriori */
    vector<FighterBot*> kos;
    /** Un fighter winner pour les stats */
    FighterBot* winner;

    /** L'arène de jeu */
    Arena* arena;

    /** Taille de BR (pour tailler l'arène) */
    int size;
    /** Un nombre de round limite (1000 par défaut) */
    int roundLimit;
    /** Un flag qui indique si on pause le jeu après chaque round */
    bool pause;

    /** Méthodes non destinées à être utilisées à l'extérieur... Donc en private */

    /** Jouer un round */
    void runRound();
    /** Jouer le tour d'un Fighter dans le round */
    void runRoundFighter(FighterBot* bot);
    /** Nettoyer l'arène à la fin du round */
    void cleanArena(int round);

public:
    /** Les constructeurs */
    BattleRoyale(int size);
    BattleRoyale(int size, int round);
    BattleRoyale(int size, int round, bool pause);
    /** Le destructeur (parce qu'on new des trucs dans le constructeur) */
    ~BattleRoyale();

    /** Accesseurs (getters) / mutateurs (setters) */
    Arena getArena();
    vector<FighterBot*> getKos();
    FighterBot* getWinner();

    /** Recruter un Fighter dans le BR */
    void recruit(FighterBot* fighter);
    /** Retourner le nombre de Fighter encore debout */
    int nbFighterAlive();

    /** Lancer le jeu complet */
    void run();
};

#endif //BATTLEROYALE_BATTLEROYALE_H
