#include "stdexcept"
#include "format"

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

void DoomFire::Update()
{
    for (int x = 0; x < mWidth; ++x)
    {
        for (int y = 1; y < mHeight; ++y)
        {
            int src = y * mWidth + x;
            uint32_t pixel = mFirePixels[src];

            if (pixel == 0)
            {
                mFirePixels[src - mWidth] = 0;
            }
            else
            {

                int randIdx = rand() % 3 & 3;
                int dst = src - randIdx + 1;
                mFirePixels[dst - mWidth] = pixel - (randIdx & 1);
            }
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