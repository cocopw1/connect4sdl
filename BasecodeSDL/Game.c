#include "Game.h"

Game* Game_New()
{
    Game* self = (Game*)calloc(1, sizeof(Game));
    AssertNew(self);

    self->state = GAME_IN_PROGRESS;
    self->playerID = PLAYER_1;

    return self;
}

void Game_Delete(Game* self)
{
    if (!self) return;
    free(self);
}

Game* Game_Copy(Game* self)
{
    /////////
    // TODO : Allouez une nouvelle partie puis copiez les membres de self
    Game* res = malloc(sizeof(Game));
    res->playerID = self->playerID;
    res->state = self->state;
    for (int i = 0; i < GRID_H; i++) {
        for (int j = 0; j < GRID_W; j++) {
            res->grid[i][j] = self->grid[i][j];
        }
    }
    return res;
}

/// @brief Met à jour l'état de la partie.
/// Cette méthode est appelée par Game_PlayTurn().
/// @param self la partie.
void Game_UpdateState(Game* self)
{
    bool istied = true;
    //On regarde si le jeu a été gagné par le joueur actuel

    //Horizontales
    for (int i = 0; i < GRID_W - 3; i++) {
        for (int j = 0; j < GRID_H; j++) {
            if (((self->grid[j][i] == self->grid[j][i + 1]) && ((self->grid[j][i + 1] == self->grid[j][i + 2]) && (self->grid[j][i + 2] == self->grid[j][i + 3]))) && (self->grid[j][i] != CELL_EMPTY)) {
                self->state = self->grid[j][i];
                return;
            }
        }
    }
    //Verticales
    for (int i = 0; i < GRID_W; i++) {
        for (int j = 0; j < GRID_H - 3; j++) {
            if (((self->grid[j][i] == self->grid[j + 1][i]) && ((self->grid[j + 1][i] == self->grid[j + 2][i]) && (self->grid[j + 2][i] == self->grid[j + 3][i]))) && (self->grid[j][i] != CELL_EMPTY)) {
                self->state = self->grid[j][i];
                return;
            }
        }
    }
    //Diagonales SW-NE
    for (int i = 0; i < GRID_W - 3; i++) {
        for (int j = 0; j < GRID_H - 3; j++) {
            if (((self->grid[j][i] == self->grid[j + 1][i + 1]) && ((self->grid[j + 1][i + 1] == self->grid[j + 2][i + 2]) && (self->grid[j + 2][i + 2] == self->grid[j + 3][i + 3]))) && (self->grid[j][i] != CELL_EMPTY)) {
                self->state = self->grid[j][i];
                return;
            }
        }
    }
    //Diagonales SE-NW
    for (int i = 3; i < GRID_W; i++) {
        for (int j = 0; j < GRID_H - 3; j++) {
            if (((self->grid[j][i] == self->grid[j + 1][i - 1]) && ((self->grid[j + 1][i - 1] == self->grid[j + 2][i - 2]) && (self->grid[j + 2][i - 2] == self->grid[j + 3][i - 3]))) && (self->grid[j][i] != CELL_EMPTY)) {
                self->state = self->grid[j][i];
                return;
            }
        }
    }



    //On vérifie si il y a égalité
    for (int i = 0; i < GRID_W; i++) {
        if (self->grid[GRID_H - 1][i] == CELL_EMPTY) {
            istied = false;
            break;
        }
    }
    if (istied) {
        self->state = GAME_IS_TIED;
        return;
    }
    self->state = GAME_IN_PROGRESS;
}
void Game_UpdateStateNMOD(Game* self)
{
    bool istied = true;
    //On regarde si le jeu a été gagné par le joueur actuel

    //Horizontales
    for (int i = 0; i < GRID_W - 3; i++) {
        for (int j = 0; j < GRID_H; j++) {
            if (((self->grid[j][i] == self->grid[j][i + 1]) && ((self->grid[j][i + 1] == self->grid[j][i + 2]) && (self->grid[j][i + 2] == self->grid[j][i + 3]))) && (self->grid[j][i] != CELL_EMPTY)) {
                self->state = self->grid[j][i];
                return;
            }
        }
    }
    //Verticales
    for (int i = 0; i < GRID_W; i++) {
        for (int j = 0; j < GRID_H - 3; j++) {
            if (((self->grid[j][i] == self->grid[j + 1][i]) && ((self->grid[j + 1][i] == self->grid[j + 2][i]) && (self->grid[j + 2][i] == self->grid[j + 3][i]))) && (self->grid[j][i] != CELL_EMPTY)) {
                self->state = self->grid[j][i];
                return;
            }
        }
    }
    //Diagonales SW-NE
    for (int i = 0; i < GRID_W - 3; i++) {
        for (int j = 0; j < GRID_H - 3; j++) {
            if (((self->grid[j][i] == self->grid[j + 1][i + 1]) && ((self->grid[j + 1][i + 1] == self->grid[j + 2][i + 2]) && (self->grid[j + 2][i + 2] == self->grid[j + 3][i + 3]))) && (self->grid[j][i] != CELL_EMPTY)) {
                self->state = self->grid[j][i];
                return;
            }
        }
    }
    //Diagonales SE-NW
    for (int i = 3; i < GRID_W; i++) {
        for (int j = 0; j < GRID_H - 3; j++) {
            if (((self->grid[j][i] == self->grid[j + 1][i - 1]) && ((self->grid[j + 1][i - 1] == self->grid[j + 2][i - 2]) && (self->grid[j + 2][i - 2] == self->grid[j + 3][i - 3]))) && (self->grid[j][i] != CELL_EMPTY)) {
                self->state = self->grid[j][i];
                return;
            }
        }
    }



    //On vérifie si il y a égalité
    for (int i = 0; i < GRID_W; i++) {
        for (int j = 0; j < GRID_H; j++) {
            if (self->grid[j][i] == CELL_EMPTY) {
                istied = false;
                break;
            }
        }
    }
    if (istied) {
        self->state = GAME_IS_TIED;
        return;
    }
    self->state = GAME_IN_PROGRESS;
}

bool Game_CanPlayAt(Game* self, int column)
{
    assert(self);
    if (column < GRID_W) {
        if (self->grid[GRID_H - 1][column] == CELL_EMPTY) {
            return true;
        }
    }
    /////////
    // TODO : Implémentez cette fonction.

    return false;
}
bool Game_CanPlayAtnewmod(Game* self, int column,int row)
{
    int raw = GRID_H-1 - row;
    assert(self);
    if ((column < GRID_W)&&(raw>=0)) {
        if (self->grid[raw][column] == CELL_EMPTY) {
            return true;
        }
    }
    /////////
    // TODO : Implémentez cette fonction.

    return false;
}

void Game_PlayTurn(Game* self, int column)
{
    assert(self);
    assert(Game_CanPlayAt(self, column));
    int i = 0;
    while (self->grid[i][column] != CELL_EMPTY) {
        i++;
    }
    if (self->playerID == 1) {
        self->grid[i][column] = CELL_P1;
    }
    else {
        self->grid[i][column] = CELL_P2;
    }
    /////////
    // TODO : Effectuez l'action du joueur self->playerID

    // Met à jour l'état de la partie
    Game_UpdateState(self);

    // Change le joueur courant
    self->playerID = PlayerID_GetOther(self->playerID);
}
void Game_PlayTurnNewmod(Game* self, int column,int row)
{
    assert(self);

    int raw = GRID_H - 1 - row;
    assert(Game_CanPlayAtnewmod(self, column,row));
    self->grid[raw][column] = self->playerID;
    /////////
    // TODO : Effectuez l'action du joueur self->playerID

    // Met à jour l'état de la partie
    Game_UpdateStateNMOD(self);

    // Change le joueur courant
    self->playerID = PlayerID_GetOther(self->playerID);
}

void Game_UndoTurn(Game* self, int column)
{
    assert(self);
    int i = 0;
    while (self->grid[i][column] != CELL_EMPTY) {
        i++;
    }
    self->grid[i][column] = CELL_EMPTY;
    /////////
    // TODO : Effectuez l'action du joueur self->playerID

    // Met à jour l'état de la partie
    Game_UpdateState(self);

    // Change le joueur courant
    self->playerID = PlayerID_GetOther(self->playerID);
}
#define ccell 124
void Game_Print(SDL_Renderer* renderer,Game* self,SDL_Texture* red, SDL_Texture* yellow)
{
    int h = 0;
    for (int i = GRID_H-1; i >=0; i--) {
        int l = 0;
        for (int j = 0; j < GRID_W; j++) {
            SDL_FRect dstRect;
            switch (self->grid[i][j]) {
                case CELL_EMPTY:
                    l += ccell;
                    break;
                case CELL_P1:
                    dstRect.x = l;
                    dstRect.y = h;
                    dstRect.w = ccell;
                    dstRect.h = ccell;
                    SDL_RenderCopyF(renderer, red, NULL, &dstRect);
                    l += ccell;
                    break;
                case CELL_P2:
                    dstRect.x = l;
                    dstRect.y = h;
                    dstRect.w = ccell;
                    dstRect.h = ccell;
                    SDL_RenderCopyF(renderer, yellow, NULL, &dstRect);
                    l += ccell;
                    break;
            }
        }
        h += ccell;

        
    }
    /////////
    // TODO : Implémentez un bel affichage de la partie
}