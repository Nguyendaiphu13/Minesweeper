#ifndef _MAIN_H
#define _MAIN_H
#include <iostream>

using namespace std;

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800 ;
#define WINDOW_TITLE "Minesweeper"

const int TILE_SIZE = 40;

struct cautrucBang {
    int dong = 0;
    int cot = 0;
    int bom = 0;
    int co = 0 ;
    int soodamo = 0;

};

struct cautrucO {
    bool ocobom = false;
    bool ocamco = false;
    bool odamo = false;
    int sobomlienke = 0;
};
#endif
