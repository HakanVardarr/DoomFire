#ifndef __FIRE_H
#define __FIRE_H

#include "SDL3/SDL.h"

class DoomFire
{
public:
    DoomFire(SDL_Renderer *renderer, int width, int height);
    ~DoomFire();

    void Update();
    void Render(SDL_Renderer *renderer, SDL_FRect *destRect);

private:
    const uint32_t COLOR_PALETTE[37] = {
        0x000000FF, 0x07071FFF, 0x070F2FFF, 0x070F47FF,
        0x071757FF, 0x071F67FF, 0x071F77FF, 0x07278FFF,
        0x072F9FFF, 0x073FAFFF, 0x0747BFFF, 0x0747C7FF,
        0x074FDFDF, 0x0757DFFF, 0x0757DFFF, 0x075FD7FF,
        0x075FD7FF, 0x0F67D7FF, 0x0FCF6FFF, 0x0FCF77FF,
        0x0FCF7FFF, 0x17CF87FF, 0x17C787FF, 0x17C78FFF,
        0x1FC797FF, 0x1FBF9FFF, 0x1FBF9FFF, 0x27BFA7FF,
        0x27BFA7FF, 0x2FAFAFFF, 0x2FB7AFFF, 0x2FB7B7FF,
        0x37B7B7FF, 0x6FCFCFFF, 0x9FDFDFFF, 0xC7EFEFFF,
        0xFFFFFFFF};

    SDL_Texture *mTexture = nullptr;
    uint32_t *mFirePixels = nullptr;
    void *mPixels = nullptr;
    int mPitch, mWidth, mHeight;
};

#endif