#ifndef __WINDOW_H
#define __WINDOW_H

#include "SDL3/SDL.h"

class Window
{
public:
    Window(const char *title, int width, int height);
    ~Window();

    SDL_Renderer *CreateRenderer() const;
    SDL_Window *GetWindowHandle() const;

private:
    SDL_Window *mSDL_Window = nullptr;
    int mWidth, mHeight;
};

#endif