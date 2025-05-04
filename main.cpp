#include <iostream>
#include <cstdlib>
#include <ctime>
#include "main.h"
#include "function.h"
#include "graphics.h"

using namespace std;

int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();
    khoitao(10, 10, 25);
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
        }
        graphics.prepareScene(nullptr);
        graphics.renderGame();
    }
    graphics.quit();
    return 0;
}
