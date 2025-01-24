#include "stdexcept"
#include "format"

#include "Window.h"

Window::Window(const char *title, int width, int height) : mWidth(width), mHeight(height)
{
    mSDL_Window = SDL_CreateWindow(title, width, height, 0);
    if (mSDL_Window == NULL)
    {
        std::string errorMessage = std::format("Failed to create window: {}", SDL_GetError());
        throw std::runtime_error(errorMessage);
    }
}

Window::~Window()
{
    SDL_DestroyWindow(mSDL_Window);
}

SDL_Renderer *Window::CreateRenderer() const
{
    SDL_Renderer *renderer = SDL_CreateRenderer(mSDL_Window, NULL);
    if (renderer == NULL)
    {
        std::string errorMessage = std::format("Failed to create renderer: {}", SDL_GetError());
        throw std::runtime_error(errorMessage);
    }
    return renderer;
}