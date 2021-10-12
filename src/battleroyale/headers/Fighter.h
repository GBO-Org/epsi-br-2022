#ifndef BATTLEROYALE_FIGHTER_H
#define BATTLEROYALE_FIGHTER_H

#include <iostream>

using namespace std;

/** Fighter
 * Le combattant de base */
class Fighter {
private:
    /** Nom / identifiants du combattant */
    string name;
    string id;
    string shortId;

    /** Statisitques réglables par les héritiers */
    int attack;
    int defense;
    int speed;

    /** Attributs gérés par le moteur de jeu */
    /** Niveau de vie du combattant */
    int life;

    /** Position */
    int x, y;

    /** Le statut (moyen de communication ?) */
    string status;

public:
    /** Constructeurs */
    Fighter(string name, int attack, int defense, int speed);
    virtual ~Fighter();

    /** Accesseurs (getters) / mutateurs (setters) */
    string getName();
    string getNameId();
    string getId();
    string getShortId();
    int getAttack();
    int getDefense();
    int getSpeed();
    int getLife();
    int getX();
    int getY();
    void setStats(int attack, int defense, int speed);
    string getStatus();
    void setStatus(string status);

    /** Affichage */
    void display();
    void display(string message);
    void display(string message, bool newLine);

    /** Test sur la position */
    bool isHere(int x, int y);
    bool isHere(Fighter* fighter);

    /** Test d'identité : pour savoir si le Fighter en paramètre est le même de this
     * La comparaison se fera sur l'ID */
    bool isMe(Fighter* fighter);
    bool isMe(Fighter fighter);

    /** Déplacer le Fighter à la position cible */
    void moveTo(int x, int y);

    /** Indiquer si le Fighter est KO ou pas */
    bool isKO();

    /** Méthode de comparaison de Fighter : basée sur la rapidité du Fighter et un peu d'aléa
     * La méthode est statique : elle peut être invoquée sans instance associée.
     * C'est une contrainte de la fonction sort utilisée dans BattleRoyale */
    static bool compare(Fighter* a, Fighter* b);

    /** Attaquer et subir des dégâts */
    void assault(Fighter* fighter);
    void suffer(int damage);
};

#endif //BATTLEROYALE_FIGHTER_H
