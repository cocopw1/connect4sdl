#include "Settings.h"
#include "Common.h"
#include "Input.h"
#include "Assets.h"
#include "Game.h"
#include "AI.h"



// IMPORTANT :
// Les librairies SDL_TTF et SDL_Mixer sont configurées dans le projet mais ne
// sont pas initialisées.
// Vous devez pour cela modifier les fonctions App_Init() et App_Quit() dans
// le fichier Common.c



int main(int argc, char *argv[])
{
    // Initialisation de la SDL
    App_Init(SDL_INIT_VIDEO, IMG_INIT_PNG, MIX_INIT_MP3);

    // Crée la fenêtre et le moteur de rendu
    int sdlFlags = 0;
#ifdef FULLSCREEN
    sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif

    SDL_Window *window = SDL_CreateWindow(
        u8"Basecode SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT, sdlFlags
    );

    if (!window)
    {
        printf("ERROR - Create window %s\n", SDL_GetError());
        assert(false); abort();
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    if (!renderer)
    {
        printf("ERROR - Create renderer %s\n", SDL_GetError());
        assert(false); abort();
    }

    // Crée le temps global du jeu
    g_time = Timer_New();
    AssertNew(g_time);

    // Crée le gestionnaire des entrées utilisateur
    Input *input = Input_New();

    // Chargement des assets
    Assets *assets = Assets_New(renderer);
    Game* game = Game_New();
    bool finished = false;
    //--------------------------------------------------------------------------
    // Boucle de rendu

    // Position et vitesse du logo (exemple)
    float x = 0.0f;
    float y = 0.0f;
    float w = WINDOW_WIDTH;
    float h = WINDOW_HEIGHT;
    float vx = 200.0f;
    float vy = 200.0f;
    int easter_egg = 0;
    bool music = true;
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    Mix_Music* musica = Mix_LoadMUS("../Assets/BowlingMusic.mp3");
    Mix_PlayMusic(musica, 20000000);
    bool playing = false;
    bool ia = false;
    TTF_Font* font = TTF_OpenFont("../Assets/Roboto-Regular.ttf", 100);
    SDL_Color r;
    r.r = 0;
    r.b = 0;
    r.g = 0;
    bool newmod = false; 
    while (true)
    {
        // Met à jour le temps
        Timer_Update(g_time);

        // Met à jour les entrées
        Input_Update(input);

        if (input->quitPressed)
            break;

        // Met à jour la scène (exemple de déplacement du logo)
        /*if ((vx > 0.0f && x + w >= LOGICAL_WIDTH) || (vx < 0.0f && x < 0.0f))
            vx *= -1.0f;
        if ((vy > 0.0f && y + h >= LOGICAL_HEIGHT) || (vy < 0.0f && y < 0.0f))
            vy *= -1.0f;
        x += Timer_GetDelta(g_time) * vx;
        y += Timer_GetDelta(g_time) * vy;*/

        // Efface le rendu précédent
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        if (playing){
            if (input->mspressed) {
                if (!newmod) {
                    int tpm = input->mousx / 124;
                    if ((Game_CanPlayAt(game, tpm)) && (!finished)) {
                        Game_PlayTurn(game, tpm);
                        switch (Game_GetState(game))
                        {
                        case GAME_P1_WON:
                            printf("\n\nLe joueur 1 gagne\n");
                            finished = true;
                            break;

                        case GAME_P2_WON:
                            printf("\n\nLe joueur 2 gagne\n");
                            finished = true;
                            break;

                        case GAME_IS_TIED:
                            printf("\n\nEgalite parfaite\n");
                            finished = true;
                            break;
                        case GAME_IN_PROGRESS:

                            break;

                        default:
                            printf("ERREUR\n");
                            finished = true;
                            assert(false);
                            break;
                        }
                        if ((ia) && (GAME_IN_PROGRESS == Game_GetState(game))) {
                            Game_PlayTurn(game, AI_ComputeMove(game, 2));
                        }
                        switch (Game_GetState(game))
                        {
                        case GAME_P1_WON:
                            printf("\n\nLe joueur 1 gagne\n");
                            finished = true;
                            break;

                        case GAME_P2_WON:
                            printf("\n\nLe joueur 2 gagne\n");
                            finished = true;
                            break;

                        case GAME_IS_TIED:
                            printf("\n\nEgalite parfaite\n");
                            finished = true;
                            break;
                        case GAME_IN_PROGRESS:

                            break;

                        default:
                            printf("ERREUR\n");
                            finished = true;
                            assert(false);
                            break;
                        }
                    }
                }
                else {

                    int tpm = input->mousx / 124;
                    int t = input->mousy / 124;
                    if ((Game_CanPlayAtnewmod(game, tpm, t)) && (!finished)) {
                        Game_PlayTurnNewmod(game, tpm, t);
                        switch (Game_GetState(game))
                        {
                        case GAME_P1_WON:
                            printf("\n\nLe joueur 1 gagne\n");
                            finished = true;
                            break;

                        case GAME_P2_WON:
                            printf("\n\nLe joueur 2 gagne\n");
                            finished = true;
                            break;

                        case GAME_IS_TIED:
                            printf("\n\nEgalite parfaite\n");
                            finished = true;
                            break;
                        case GAME_IN_PROGRESS:

                            break;

                        default:
                            printf("ERREUR\n");
                            finished = true;
                            assert(false);
                            break;
                        }
                    }
                };
            }

        Game_Print(renderer, game, assets->red, assets->yellow);
        // Dessinez ici votre rendu
        SDL_FRect dstRect;
        dstRect.x = x;
        dstRect.y = y;
        dstRect.w = w;
        dstRect.h = h;

        SDL_RenderCopyF(renderer, assets->grid, NULL, &dstRect);
        if (!finished)
        {
            if (!newmod) {
            int tpm = input->mousx / 124;
            int ygrec = tpm * 124;
            SDL_Rect dtRect;
            dtRect.x = ygrec;
            dtRect.y = 0;
            dtRect.w = 124;
            dtRect.h = 124;

            if (Game_CanPlayAt(game, tpm)) {
                SDL_RenderCopy(renderer, assets->Varr, NULL, &dtRect);
            }
            else {

                SDL_RenderCopy(renderer, assets->Rarr, NULL, &dtRect);
            }
        }
        }
        if (finished) {
            TTF_Font* font = TTF_OpenFont("../Assets/Roboto-Regular.ttf", 50);
            SDL_Color r;
            r.r = 0;
            r.b = 0;
            r.g = 0;
            char* text = malloc(18);
            SDL_Rect hapysadrect;
            hapysadrect.x = 310; 
            hapysadrect.y = 372;
            hapysadrect.w = 248;
            switch (Game_GetState(game))
            {
            case GAME_P1_WON:
                if (ia) {

                    strcpy(text, "Le joueur gagne");
                    hapysadrect.h = 169;
                    SDL_RenderCopy(renderer, assets->happy, NULL, &hapysadrect);
                }
                else {

                    strcpy(text, "Le joueur 1 gagne");
                }
                break;

            case GAME_P2_WON:
                if (ia) {
                    hapysadrect.h = 253;
                    strcpy(text, "L'IA a gagné");
                    SDL_RenderCopy(renderer, assets->sad, NULL, &hapysadrect);
                }
                else {

                    strcpy(text, "Le joueur 2 gagne");
                }
                break;

            case GAME_IS_TIED:
                strcpy(text, "Egalite parfaite");
                break;
            }
            SDL_Surface* surfaceMessage =
                TTF_RenderText_Solid(font, text, r);
            free(text);
            // now you can convert it into a texture
            SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
            SDL_FreeSurface(surfaceMessage);
            SDL_Rect Message_rect; //create a rect
             // controls the rect's y coordinte
            Message_rect.h = 100;
            Message_rect.w = 300;  //controls the rect's x coordinate 
            Message_rect.y = WINDOW_HEIGHT / 2 - Message_rect.h / 2;
            Message_rect.x = WINDOW_WIDTH / 2 - Message_rect.w / 2;// controls the width of the rect
            // controls the height of the rect
            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
            SDL_DestroyTexture(Message);
            SDL_Rect men_rect;
            men_rect.h = 124;
            men_rect.w = 124;
            men_rect.x = 124*6;
            men_rect.y = 0;
            SDL_RenderCopy(renderer, assets->butmenu, NULL, &men_rect);
            SDL_Rect man_rect;
            man_rect.h = 124;
            man_rect.w = 124;
            man_rect.x = 0;
            man_rect.y = 0;
            SDL_RenderCopy(renderer, assets->replay, NULL, &man_rect);
            if (input->mspressed) {
                int tpm = input->mousx / 124;
                int t = input->mousy / 124;
                if (t == 0) {
                    if (tpm == 6) {
                        playing = false;
                        Game_Delete(game);
                        game = Game_New();
                        finished = false;
                    }
                    if (tpm == 0)
                    {
                        finished = false;
                        Game_Delete(game);
                        game = Game_New();
                    }
                }
            }
            }
        }
        else {
            SDL_Rect bkg_rect;
            bkg_rect.h = WINDOW_HEIGHT;
            bkg_rect.w = WINDOW_WIDTH;
            bkg_rect.x = 0;
            bkg_rect.y = 0;
            SDL_RenderCopy(renderer, assets->menubkg, NULL, &bkg_rect);
            SDL_Rect jcj_rect;
            jcj_rect.h = 124;
            jcj_rect.w = 124;
            jcj_rect.x = 124;
            jcj_rect.y = 124;
            SDL_RenderCopy(renderer, assets->butjcj, NULL, &jcj_rect);
            SDL_Rect jco_rect;
            jco_rect.h = 124;
            jco_rect.w = 124;
            jco_rect.x = 124 * 5;
            jco_rect.y = 124;
            SDL_RenderCopy(renderer, assets->butjco, NULL, &jco_rect);

            SDL_Rect jo_rect;
            jo_rect.h = 124;
            jo_rect.w = 124;
            jo_rect.x = 124 * 3;
            jo_rect.y = 5*124;
            SDL_RenderCopy(renderer, assets->newmod, NULL, &jo_rect);
            SDL_Rect sound_rect;
            sound_rect.h = 124;
            sound_rect.w = 124;
            sound_rect.x = 0;
            sound_rect.y = 124*5;
            if (music) {

                SDL_RenderCopy(renderer, assets->unmute, NULL, &sound_rect);
            }
            else {

                SDL_RenderCopy(renderer, assets->mute, NULL, &sound_rect);
            }

            if (input->mspressed) {
                int tpm = input->mousx / 124;
                int t = input->mousy / 124;
                if (t == 1) {
                    if (tpm == 1) {
                        playing = true;
                        ia = false;
                        newmod = false;
                    }
                    if (tpm == 5) {
                        ia = true;
                        playing = true;
                        newmod = false;
                    }
                }
                if (tpm == 3) {
                    if (t == 5) {
                        playing = true;
                        ia = false;
                        newmod = true;
                    }
                }
                if (tpm == 0) {
                    if (t == 5) {
                        easter_egg++;
                        music = !music;
                        if (music) {
                            Mix_ResumeMusic();
                        }
                        else {

                            Mix_PauseMusic();
                        }
                    }
                }
                printf("%d,%d\n", tpm, t);

            }
            char* text = malloc(61); 
            SDL_Rect Message_rect; //create a rect
             // controls the rect's y coordinte
            Message_rect.h = 100;
            Message_rect.w = 300; //controls the rect's x coordinate 
            Message_rect.y = WINDOW_HEIGHT / 2 - Message_rect.h / 2;
            Message_rect.x = WINDOW_WIDTH / 2 - Message_rect.w / 2;
            if (easter_egg < 5) {
                strcpy(text, "connect4.exe");

            }
            else {

                Message_rect.w = WINDOW_WIDTH;
                Message_rect.x = 0;
                strcpy(text, "go check bowling.exe :https://silverfox88.itch.io/bowlingexe");
                
            }
            SDL_Surface* surfaceMessage =
                TTF_RenderText_Solid(font, text, r);
            // now you can convert it into a texture
            SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
            SDL_FreeSurface(surfaceMessage);// controls the width of the rect
            // controls the height of the rect
            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
            SDL_DestroyTexture(Message);


        }
        // Affiche le nouveau rendu
        SDL_RenderPresent(renderer);
    }

    //--------------------------------------------------------------------------
    // Libération de la mémoire

    Assets_Delete(assets);
    assets = NULL;

    Input_Delete(input);
    input = NULL;

    Timer_Delete(g_time);
    g_time = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    Game_Delete(game);
    SDL_DestroyWindow(window);
    window = NULL;

    App_Quit();

    return EXIT_SUCCESS;
}