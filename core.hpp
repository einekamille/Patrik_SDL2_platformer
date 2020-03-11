#ifndef CORE_H
#define CORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "map.hpp"
#include "player.hpp"

using namespace std;

class eCore
{
private:
    SDL_Window * window;
    SDL_Renderer* rendr;
    SDL_Event* mainEvent;

    long frameTime;
    static const int MIN_FRAME_TIME = 16;

    unsigned long FPSTime;
    int iNumOfFPS, iFPS;

    bool keyRight, keyLeft, keyUp, keyDown;

    int offsetX;

public:

    bool quitGame;

    eCore(void);
    ~eCore(void);

    void mainLoop();
    void Update();
    void Draw();
    void Input();
};

#endif // CORE_H
