#include <iostream>
#include <cstdlib>
#include <ctime>
#include "main.h"
#include "function.h"
#include "graphics.h"

using namespace std;
int main(int argc, char* argv[]){
    int level;
    cin >> level;
    switch (level){
        case 0:
            khoitao(3,3,1);
            break;
        case 1:
            khoitao(9,9,10);
            break;
        case 2:
            khoitao(16,16,40);
            break;
        case 3:
            khoitao(16,30,99);
            break;
    }
    Graphics graphics;
    graphics.init();
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                quit = true;
            }
            graphics.handleMouseEvents(event);
            if (graphics.gameover){
                SDL_Delay(2000);
                quit = true;
                return 0;
            }
            if(checkWin()){
                graphics.winTexture(graphics.youwin);
                SDL_Delay(2000);
                quit = true;
                return 0;
            }
        }
    graphics.prepareScene(graphics.background);
    graphics.renderGame();
    }
    graphics.quit();
    return 0;
}
