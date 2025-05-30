#ifndef _GRAPHICS__H
#define _GRAPHICS__H
#include <SDL.h>
#include <SDL_image.h>
#include "main.h"
#include "function.h"
struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;

    Graphics();
    ~Graphics();

    void logErrorAndExit(const char* msg, const char* error);
    void init();
    void prepareScene(SDL_Texture * background);
    void presentScene();
    void renderTexture(SDL_Texture *texture, int x, int y);
    SDL_Texture *loadTexture(const char *filename);
    void renderGame();
    void renderTile(int x, int y, int number, bool isBomb, bool isFlagged);
    void handleMouseEvents(SDL_Event& event);
    void quit();
    bool gameover;
    void winTexture(SDL_Texture* youwin);

    int leNgang = (SCREEN_WIDTH - bang.cot * TILE_SIZE) / 2;
    int leDoc = (SCREEN_HEIGHT - bang.dong * TILE_SIZE) / 2;

    SDL_Texture* normalTexture;
    SDL_Texture* bombTexture;
    SDL_Texture* flagTexture;
    SDL_Texture* numberTextures[9];
    SDL_Texture* background;
    SDL_Texture* Gameover;
    SDL_Texture* youwin;
};
#endif

