#include "displaymanager.h"

DisplayManager::DisplayManager(Board *board)
{
    if (board == nullptr)
    {
        // TODO Way to notify (should throw exception?)
        throw std::exception();
    }

    this->board = board;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        // TODO Way to notify (should throw exception?)
        throw std::exception();
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("Forest Fire v0.2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, board->getWidth(), board->getHeight(), SDL_WINDOW_SHOWN);
        if(window == nullptr)
        {
            // printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            // TODO Way to notify (should throw exception?)
            throw std::exception();
        }
        else
        {
            //renderBoard();
        }
    }
}

DisplayManager::~DisplayManager()
{
    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}

bool DisplayManager::renderBoard()
{
    if (board == nullptr)
    {
        // TODO Way to notify (should throw exception?)
        throw std::exception();
    }

    if (window == nullptr)
    {
        // TODO Way to notify (should throw exception?)
        throw std::exception();
    }

    //Get window surface
    screenSurface = SDL_GetWindowSurface(window);

    // Lock the surface for efficient pixel painting
    if(SDL_MUSTLOCK(screenSurface))
    {
        SDL_LockSurface(screenSurface);
    }

    // render the board (one pixel per Board Cell)
    for (unsigned int yIndex = 0; yIndex < board->getHeight(); ++yIndex)
    {
        for (unsigned int xIndex = 0; xIndex < board->getWidth(); ++xIndex)
        {
            Cell *currentCell = board->getCell(xIndex, yIndex);
            switch (currentCell->getCellState())
            {
            case CellState::Empty:
                putEmpty_nolock(screenSurface, xIndex, yIndex);
                break;

            case CellState::Tree:
                putTree_nolock(screenSurface, xIndex, yIndex);
                break;

            case CellState::Fire:
                putFire_nolock(screenSurface, xIndex, yIndex);
                break;

            default:
                // TODO Way to notify (should throw exception?)
                throw std::exception();
            }
        }
    }

    // Unlock the surface
    if(SDL_MUSTLOCK(screenSurface))
    {
        SDL_UnlockSurface(screenSurface);
    }

    //Update the surface
    SDL_UpdateWindowSurface(window);

    // Handle any SDL Events we get
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }
    }

    // return true since we didn't get a SDL_QUIT event
    return true;
}

void DisplayManager::putPixel32_nolock(SDL_Surface *surface, int x, int y, Uint32 color)
{
    Uint8 *pixel = (Uint8*)surface->pixels;
    pixel += (y * surface->pitch) + (x * sizeof(Uint32));
    *((Uint32*)pixel) = color;
}

void DisplayManager::putEmpty_nolock(SDL_Surface *surface, int x, int y)
{
    putPixel32_nolock(surface, x, y, 0x000000); // black
}

void DisplayManager::putTree_nolock(SDL_Surface *surface, int x, int y)
{
    putPixel32_nolock(surface, x, y, 0x00FF00); // green
}

void DisplayManager::putFire_nolock(SDL_Surface *surface, int x, int y)
{
    putPixel32_nolock(surface, x, y, 0xFF0000); // red
}


