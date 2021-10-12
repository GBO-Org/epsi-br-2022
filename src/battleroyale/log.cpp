#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

#include "log.h"

#ifdef _WIN32
HANDLE hstdout;
#endif

void loginit() {
    #ifdef _WIN32
    // Passe la console en UTF8 pour ne plus avoir de problèmes d'accents
    SetConsoleOutputCP(CP_UTF8);
    // Récupère le STD_OUTPUT_HANDLE pour manipuler les couleurs de sortie
    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
}

void setcolor(int color) {
    #ifdef _WIN32
    SetConsoleTextAttribute(hstdout, color);
    #else
    cout << "\033[" + to_string(color) + "m";
    #endif
}

void log(int text) { log(to_string(text), WHITE); }
void log(string text) { log(text, WHITE); }
void log(int text, int color) { log(to_string(text), color); }
void log(string text, int color) {
    setcolor(color);
    cout << text;
}

void logln(int text) { logln(to_string(text), WHITE); }
void logln(string text) { logln(text, WHITE); }
void logln(int text, int color) { logln(to_string(text), color); }
void logln(string text, int color) {
    log(text + "\n", color);
}
