#pragma once

#include "Settings.h"

typedef struct Assets_s
{
    SDL_Texture* grid;
    SDL_Texture* red;
    SDL_Texture* yellow;
    SDL_Texture* Rarr;
    SDL_Texture* Varr;
    SDL_Texture* butjcj;
    SDL_Texture* butjco;
    SDL_Texture* menubkg;
    SDL_Texture* butmenu;
    SDL_Texture* happy;
    SDL_Texture* sad;
    SDL_Texture* mute;
    SDL_Texture* unmute;
    SDL_Texture* replay;
    SDL_Texture* newmod;



} Assets;

Assets *Assets_New(SDL_Renderer *renderer);
void Assets_Delete(Assets *self);
