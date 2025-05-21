#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "main.h"
#include "function.h"


Graphics::Graphics() {
    window = nullptr;
    renderer = nullptr;
    normalTexture = nullptr;
    bombTexture = nullptr;
    flagTexture = nullptr;
    gameover = false;
    Gameover = nullptr;
    youwin = nullptr;
}

Graphics::~Graphics() {
    quit();
}

void Graphics::logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
            logErrorAndExit("CreateWindow", SDL_GetError());
    }

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit("SDL_image error:", IMG_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
            logErrorAndExit("CreateRenderer", SDL_GetError());
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


    normalTexture = loadTexture("normal.png");
    bombTexture = loadTexture("bomb.png");
    flagTexture = loadTexture("flag.png");
    numberTextures[0] = loadTexture("0.png");
    numberTextures[1] = loadTexture("1.png");
    numberTextures[2] = loadTexture("2.png");
    numberTextures[3] = loadTexture("3.png");
    numberTextures[4] = loadTexture("4.png");
    numberTextures[5] = loadTexture("5.png");
    numberTextures[6] = loadTexture("6.png");
    numberTextures[7] = loadTexture("7.png");
    numberTextures[8] = loadTexture("8.png");
    background = loadTexture("background.png");
    Gameover = loadTexture("Gameover.png");
    youwin = loadTexture("youwin.png");
}

SDL_Texture* Graphics::loadTexture(const char* filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
    if (texture == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
    }
    return texture;
}

void Graphics::renderTexture(SDL_Texture* texture, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture,nullptr , nullptr, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

void Graphics::prepareScene(SDL_Texture* background) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
}

void Graphics::presentScene() {
    SDL_RenderPresent(renderer);
}

void Graphics::renderTile(int x, int y, int number, bool isBomb, bool isFlagged) {
    SDL_Rect dest;
    dest.x = leNgang + (x * TILE_SIZE);
    dest.y = leDoc + (y * TILE_SIZE);
    SDL_QueryTexture(normalTexture, nullptr, nullptr, &dest.w, &dest.h);

    if (!isBomb) {
        SDL_RenderCopy(renderer, normalTexture, nullptr, &dest);
    }

    if (isBomb) {
        SDL_RenderCopy(renderer, bombTexture, nullptr, &dest);
    }

    if (isFlagged) {
        SDL_RenderCopy(renderer, flagTexture, nullptr, &dest);
    }

    if (!isBomb && number >= 0) {
        SDL_RenderCopy(renderer, numberTextures[number], nullptr, &dest);
    }
}
void Graphics::renderGame() {
    for (int i = 0; i < bang.dong; ++i) {
        for (int j = 0; j < bang.cot; ++j) {
            int number = motO[i][j].sobomlienke;
            bool isBomb = motO[i][j].ocobom;
            bool isFlagged = motO[i][j].ocamco;
            bool isOpened = motO[i][j].odamo;
                if (isOpened) {
                    renderTile(j, i, number, isBomb, isFlagged);
                }else {
                    renderTile(j, i, -1, false, isFlagged);
                }
        }
    }
    SDL_RenderPresent(renderer);
}

void Graphics::quit() {
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(background);
    SDL_Quit();
}

void Graphics::handleMouseEvents(SDL_Event& event) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    int tileX = (x - leNgang) / TILE_SIZE;
    int tileY = (y - leDoc) / TILE_SIZE;
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (!motO[tileY][tileX].odamo && !motO[tileY][tileX].ocamco) {
                    moO(motO, bang, tileX, tileY);
                    if (motO[tileY][tileX].ocobom) {
                        SDL_RenderCopy(renderer , Gameover , nullptr , nullptr);
                        SDL_RenderPresent(renderer);
                        gameover = true;
                    }
                }
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                if (!motO[tileY][tileX].odamo) {
                    motO[tileY][tileX].ocamco = !motO[tileY][tileX].ocamco;
                }
            }
            break;
        case SDL_QUIT:
            quit();
            break;
        default:
            break;
    }
}
void Graphics::winTexture(SDL_Texture* youwin){
    SDL_RenderCopy(renderer , youwin , nullptr , nullptr);
    SDL_RenderPresent(renderer);
}

