#include <iostream>
#include <string>

#include "log.h"

void setcolor(int color) {
    #ifdef _WIN32
    //SetConsoleTextAttribute(hstdout, color);
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
