#include <stdexcept>
#include <format>
#include <iostream>

#include "Application.h"
#include "Fire.h"

Application::Application() : mSuccess(SDL_Init(SDL_INIT_VIDEO)), mWindow(Window("Doom Fire", WIDTH, HEIGHT)), mRenderer(mWindow.CreateRenderer())
{
    if (!mSuccess)
    {
        std::string errorMessage = std::format("Failed to initialize SDL: {}", SDL_GetError());
        throw std::runtime_error(errorMessage);
    }
}

Application::~Application()
{
    SDL_DestroyRenderer(mRenderer);
}

void Application::Run()
{
    DoomFire fireTexture(mRenderer, WIDTH / 3 * 2, HEIGHT / 3 * 2);

    SDL_Event event;
    Uint32 frameStart;
    Uint32 frameTime;

    while (mIsRunning)
    {
        frameStart = SDL_GetTicks();

        SDL_PollEvent(&event);
        if (event.type == SDL_EventType::SDL_EVENT_QUIT)
        {
            mIsRunning = false;
        }

        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mRenderer);

        fireTexture.Update();
        SDL_FRect destRect = {.h = HEIGHT, .w = WIDTH, .x = 0, .y = 0};
        fireTexture.Render(mRenderer, &destRect);

        SDL_RenderPresent(mRenderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime)
        {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
}