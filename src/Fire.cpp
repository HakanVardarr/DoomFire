#include <stdexcept>
#include <format>
#include <thread>
#include <vector>

#include "Fire.h"

DoomFire::DoomFire(SDL_Renderer *renderer, int width, int height) : mWidth(width), mHeight(height)
{
    mTexture = SDL_CreateTexture(renderer, SDL_PixelFormat::SDL_PIXELFORMAT_ARGB32, SDL_TextureAccess::SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);
    if (mTexture == NULL)
    {
        std::string errorMessage = std::format("Failed to create texture: {}", SDL_GetError());
        throw std::runtime_error(errorMessage);
    }

    mFirePixels = new uint32_t[mWidth * mHeight]();
    for (int i = 0; i < mWidth; ++i)
    {
        mFirePixels[(mHeight - 1) * mWidth + i] = 36;
    }
}

DoomFire::~DoomFire()
{
    SDL_DestroyTexture(mTexture);
    delete[] mFirePixels;
}

struct ThreadData
{
    int startX, endX;
    int width, height;
    uint32_t *firePixels;
};

int updateFire(void *data)
{
    ThreadData *threadData = static_cast<ThreadData *>(data);

    int startX = threadData->startX;
    int endX = threadData->endX;
    int width = threadData->width;
    int height = threadData->height;
    uint32_t *firePixels = threadData->firePixels;

    for (int x = startX; x < endX; ++x)
    {
        for (int y = 1; y < height; ++y)
        {
            int src = y * width + x;
            uint32_t pixel = firePixels[src];

            if (pixel == 0)
            {
                firePixels[src - width] = 0;
            }
            else
            {
                int randIdx = rand() % 3;
                int dst = src - randIdx + 1;
                firePixels[dst - width] = pixel - (randIdx & 1);
            }
        }
    }

    return 0;
}

void DoomFire::Update()
{
    const uint threadCount = std::thread::hardware_concurrency();
    int chunkSize = mWidth / threadCount;

    std::vector<SDL_Thread *> threads(threadCount);
    std::vector<ThreadData> threadDataList(threadCount);

    for (int i = 0; i < threadCount; ++i)
    {
        int startX = chunkSize * i;
        int endX = (i == threadCount - 1) ? mWidth : startX + chunkSize;

        threadDataList[i] = {startX, endX, mWidth, mHeight, mFirePixels};
        threads[i] = SDL_CreateThread(updateFire, "FireThread", &threadDataList[i]);
    }

    for (auto thread : threads)
    {
        if (thread)
        {
            SDL_WaitThread(thread, nullptr);
        }
    }
}

void DoomFire::Render(SDL_Renderer *renderer, SDL_FRect *destRect)
{
    SDL_LockTexture(mTexture, NULL, &mPixels, &mPitch);

    uint32_t *pixels = static_cast<uint32_t *>(mPixels);
    for (int x = 0; x < mWidth; ++x)
    {
        for (int y = 0; y < mHeight; ++y)
        {
            pixels[y * mWidth + x] = COLOR_PALETTE[mFirePixels[y * mWidth + x]];
        }
    }

    SDL_UnlockTexture(mTexture);
    SDL_RenderTexture(renderer, mTexture, NULL, destRect);
}