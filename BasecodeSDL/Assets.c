#include "Assets.h"

typedef struct TextureSpec_s
{
    SDL_Texture **ptr;
    char *path;
} TextureSpec;

Assets *Assets_New(SDL_Renderer *renderer)
{
    Assets *self = (Assets *)calloc(1, sizeof(Assets));
    AssertNew(self);

    // -------------------------------------------------------------------------
    // Chargement des textures

    TextureSpec texSpecs[] = {
        { &self->grid, "../Assets/grid.png" },
        { &self->red, "../Assets/red.png"},
        { &self->yellow, "../Assets/yellow.png"},
        {&self->Rarr, "../Assets/flecheR.png"},
        {&self->Varr, "../Assets/flecheV.png"},
        {&self->butjcj, "../Assets/JcJb.png"},
        {&self->butjco, "../Assets/JcOb.png"},
        {&self->butmenu, "../Assets/menub.png"},
        {&self->menubkg, "../Assets/bkg.png"},
        {&self->happy, "../Assets/hap.png.png.png.png"},
        {&self->sad, "../Assets/sad.png.png.png.png"},
        {&self->mute, "../Assets/muted.png"},
        {&self->unmute, "../Assets/on.png"},
        {&self->replay, "../Assets/replay.png"},
        {&self->newmod, "../Assets/new_mod.png"}

    };
    int texSpecCount = sizeof(texSpecs) / sizeof(TextureSpec);

    for (int i = 0; i < texSpecCount; i++)
    {
        SDL_Texture **texPtr = texSpecs[i].ptr;
        char *path = texSpecs[i].path;

        *texPtr = IMG_LoadTexture(renderer, path);
        if (*texPtr == NULL)
        {
            printf("ERROR - Loading texture %s\n", path);
            printf("      - %s\n", SDL_GetError());
            assert(false);
            abort();
        }
    }

    return self;
}

void Assets_Delete(Assets *self)
{
    if (!self) return;

    // -------------------------------------------------------------------------
    // Libère les textures

    SDL_Texture** texPointers[] = {
        &self->grid,
        &self->red,
        &self->yellow,
        &self->butjcj,
        &self->butjco,
        &self->butmenu,
        &self->menubkg,
        &self->happy,
        &self->sad,
        &self->mute,
        &self->unmute,
    };
    int count = sizeof(texPointers) / sizeof(SDL_Texture **);

    for (int i = 0; i < count; i++)
    {
        if (*texPointers[i])
            SDL_DestroyTexture(*(texPointers[i]));
    }

    free(self);
}