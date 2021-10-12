#ifndef BATTLEROYALE_LOG_H
#define BATTLEROYALE_LOG_H

#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

/** Gestion des couleurs de sortie console
 * Basée sur un extrait de arene_couleur.cpp */



#ifdef _WIN32
  #define BLUE 9
  #define WHITE 15
  #define RED 12
  #define GREEN 10
#else
  #define BLUE 34
  #define WHITE 0
  #define RED 31
  #define GREEN 32
#endif

void setcolor(int color);

void loginit();

/** Ecrire du texte sans retour chariot avec une éventuelle couleur */
void log(int text);
void log(string text);
void log(int text, int color);
void log(string text, int color);

/** Ecrire du texte avec retour chariot avec une éventuelle couleur */
void logln(int text);
void logln(string text);
void logln(int text, int color);
void logln(string text, int color);

#endif //BATTLEROYALE_LOG_H
