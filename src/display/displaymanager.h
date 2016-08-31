#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <SDL2/SDL.h>

#include "src/board/board.h"

class DisplayManager
{
public:
    DisplayManager(Board *board);
    ~DisplayManager();

    bool renderBoard();

private:
    Board *board;

    int screenWidth;
    int screenHeight;

    SDL_Window *window;
    SDL_Surface *screenSurface;

    void putPixel32_nolock(SDL_Surface *surface, int x, int y, Uint32 color);
    void putEmpty_nolock(SDL_Surface *surface, int x, int y);
    void putTree_nolock(SDL_Surface *surface, int x, int y);
    void putFire_nolock(SDL_Surface *surface, int x, int y);
};

#endif // DISPLAYMANAGER_H
