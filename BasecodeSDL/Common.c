#include "Common.h"

Timer *g_time = NULL;

void App_Init(int sdlFlags, int imgFlags,int mixFlags)
{
    // Initialise la SDL2
    if (SDL_Init(sdlFlags) < 0)
    {
        printf("ERROR - SDL_Init %s\n", SDL_GetError());
        assert(false);
        abort();
    }

    // Initialise la SDL2 image
    if (IMG_Init(imgFlags) != imgFlags)
    {
        printf("ERROR - IMG_Init %s\n", IMG_GetError());
        assert(false);
        abort();
    }
    if (TTF_Init() < 0) {
        printf("ERROR - TTF_Init %s\n", SDL_GetError());
        assert(false);
        abort();
    }
    if (Mix_Init(mixFlags) != mixFlags){
        printf("ERROR - MIX_init %s\n", SDL_GetError());
        assert(false);
        abort();

    }
}

void App_Quit()
{
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}
