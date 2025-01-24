#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "SDL3/SDL.h"
#include "Window.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

class Application
{
public:
    Application();
    ~Application();

    void Run();

private:
    bool mSuccess, mIsRunning = true;
    Window mWindow;
    SDL_Renderer *mRenderer = nullptr;
};

#endif