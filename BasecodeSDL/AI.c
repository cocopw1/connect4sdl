#include "AI.h"

INLINE int Int_Max(int a, int b) { return a > b ? a : b; }
INLINE int Int_Min(int a, int b) { return a < b ? a : b; }

int Game_Eval(Game* self, int playerID)
{
    /////////
    // TODO : Implémentez votre fonction d'évaluation ici.
    // Si la partie est en faveur du joueur playerID, le score est positif.
    // Si elle est en faveur de l'autre joueur, le score est négatif.
    // Cette fonction est appelée par AINode_NewMinMax() pour initialiser
    // les scores des feuilles de l'arbre MinMax.


    int scoreFinal = rand() % 20;
    int IAID = playerID;

    //3 verticales avec espace vide
    for (int i = 0; i < GRID_W; i++) {
        for (int j = 0; j < GRID_H - 3; j++) {
            if (self->grid[j][i] != CELL_EMPTY) {
                if (((self->grid[j][i] == self->grid[j + 1][i]) && ((self->grid[j + 1][i] == self->grid[j + 2][i]) && (self->grid[j + 3][i] == CELL_EMPTY)))) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
            }
        }
    }

    //3 horizontales avec espace vide
    for (int i = 0; i < GRID_W - 3; i++) {
        for (int j = 0; j < GRID_H; j++) {
            if (self->grid[j][i + 1] != CELL_EMPTY) {
                if ((self->grid[j][i] == self->grid[j][i + 1]) && ((self->grid[j][i + 1] == self->grid[j][i + 2]) && ((self->grid[j][i + 3] == CELL_EMPTY))) && (j == 0 || self->grid[j - 1][i + 3])) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
                if (((self->grid[j][i + 1] == self->grid[j][i + 2]) && ((self->grid[j][i + 2] == self->grid[j][i + 3]) && ((self->grid[j][i] == CELL_EMPTY)))) && (j == 0 || self->grid[j - 1][i])) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
                if ((self->grid[j][i] == self->grid[j][i + 1]) && ((self->grid[j][i + 1] == self->grid[j][i + 3]) && ((self->grid[j][i + 2] == CELL_EMPTY))) && (j == 0 || self->grid[j - 1][i + 2])) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
                if ((self->grid[j][i] == self->grid[j][i + 2]) && ((self->grid[j][i + 2] == self->grid[j][i + 3]) && ((self->grid[j][i + 1] == CELL_EMPTY))) && (j == 0 || self->grid[j - 1][i + 1])) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
            }
        }
    }

    //Diagonales SW-NE
    for (int i = 1; i < GRID_W - 3; i++) {
        for (int j = 1; j < GRID_H - 3; j++) {
            if (self->grid[j][i] != CELL_EMPTY) {
                if (((self->grid[j][i] == self->grid[j + 1][i + 1]) && ((self->grid[j + 1][i + 1] == self->grid[j + 2][i + 2]) && ((self->grid[j + 3][i + 3] == CELL_EMPTY) && (self->grid[j + 2][i + 3] != CELL_EMPTY))))) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
                if (((self->grid[j][i] == self->grid[j + 1][i + 1]) && ((self->grid[j + 1][i + 1] == self->grid[j + 2][i + 2]) && ((self->grid[j - 1][i - 1] == CELL_EMPTY) && ((j - 2 == 0) || (self->grid[j - 2][i - 1])))))) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
                if (((self->grid[j][i] == self->grid[j + 1][i + 1]) && ((self->grid[j + 1][i + 1] == self->grid[j + 3][i + 3]) && ((self->grid[j + 2][i + 2] == CELL_EMPTY) && (self->grid[j + 1][i + 2] != CELL_EMPTY))))) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
                if (((self->grid[j][i] == self->grid[j + 2][i + 2]) && ((self->grid[j + 2][i + 2] == self->grid[j + 3][i + 3]) && ((self->grid[j + 1][i + 1] == CELL_EMPTY) && (self->grid[j][i + 1] != CELL_EMPTY))))) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
            }
        }
    }

    //Diagonales SE-NW
    for (int i = 3; i < GRID_W - 1; i++) {
        for (int j = 1; j < GRID_H - 3; j++) {
            if (self->grid[j][i] != CELL_EMPTY) {
                if (((self->grid[j][i] == self->grid[j + 1][i - 1]) && ((self->grid[j + 1][i - 1] == self->grid[j + 2][i - 2]) && ((self->grid[j + 3][i - 3] == CELL_EMPTY) && (self->grid[j + 2][i - 3] != CELL_EMPTY))))) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
                if (((self->grid[j + 1][i - 1] == self->grid[j + 2][i - 2]) && ((self->grid[j + 2][i - 2] == self->grid[j + 3][i - 3]) && ((self->grid[j][i] == CELL_EMPTY) && ((self->grid[j - 2][i + 1])))))) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
                if (((self->grid[j][i] == self->grid[j + 1][i - 1]) && ((self->grid[j + 1][i - 1] == self->grid[j + 3][i - 3]) && ((self->grid[j + 2][i - 2] == CELL_EMPTY) && (self->grid[j + 1][i - 2] != CELL_EMPTY))))) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
                if (((self->grid[j][i] == self->grid[j + 2][i - 2]) && ((self->grid[j + 2][i - 2] == self->grid[j + 3][i - 3]) && ((self->grid[j + 1][i - 1] == CELL_EMPTY) && (self->grid[j][i - 1] != CELL_EMPTY))))) {
                    if (self->grid[j][i] == IAID)
                        scoreFinal = scoreFinal + 1000;
                    else
                        scoreFinal = scoreFinal - 100000;
                }
            }
        }
    }
    if (Game_GetState(self) == playerID) {
        scoreFinal = 10000000 - (rand() % 20);
    }
    if (Game_GetState(self) == PlayerID_GetOther(playerID)) {
        scoreFinal = -10000000 - (rand() % 20);
    }

    //printf("%d\n", scoreFinal);


    return scoreFinal;
}

/// @brief Détruit récursivement un noeud et tous ses sous-arbres.
/// @param self le noeud.
void AINode_DeleteRec(AINode* self)
{
    if (!self) return;
    for (int i = 0; i < GRID_W; i++) AINode_DeleteRec(self->children[i]);
    Game_Delete(self->gameState);
    free(self);
    /////////
    // TODO : Implémentez la destruction du noeud et de ses enfants
    // Pensez également à détruire la copie de la partie de chaque noeud.
}


void prit(AINode* node, int prof) {
    for (int i = 0; i < GRID_W / 2; i++) {
        if (!node->children[i]) continue;
        prit(node->children[i], prof + 1);
    }
    for (int j = 0; j < prof; j++) {
        printf("    ");
    }
    printf("%d\n", node->score);
    for (int i = GRID_W / 2; i < GRID_W; i++) {
        if (!node->children[i]) continue;
        prit(node->children[i], prof + 1);
    }
}

/// @brief Crée un noeud de l'arbre de l'algorithme MinMax.
/// Cette méthode est appelée par AITree_NewMinMax().
/// @param game la partie associée au noeud.
/// @param depth la hauteur maximale du noeud.
/// @param minLayer indique si le noeud est un noeud MIN.
/// @param playerID identifiant du joueur dont l'algorithme calcule l'action.
/// @return Le noeud créé (et initialisé).
AINode* AINode_NewMinMax(Game* game, int depth, bool minLayer, int playerID)
{
    AINode* self = (AINode*)calloc(1, sizeof(AINode));
    bool u = !minLayer;

    if (Game_GetState(game) != GAME_IN_PROGRESS)
    {
        if (Game_GetState(game) == GAME_P1_WON)
        {
            if (playerID == 1)
                self->score = 10000000;
            else
                self->score = -10000000;
        }
        if (Game_GetState(game) == GAME_P2_WON)
        {
            if (playerID == 2)
                self->score = 10000000;
            else
                self->score = -10000000;
        }
        if (Game_GetState(game) == GAME_IS_TIED)
            self->score = 0;
        return self;
    }

    if (depth == 0) {
        self->score = Game_Eval(game, playerID);
        return self;
    }
    AssertNew(self);


    if (depth != 0) {
        if (minLayer == false) {
            int maxx = -100000000;
            for (int i = 0; i < GRID_W; i++) {
                if (Game_CanPlayAt(game, i)) {
                    Game* cp = Game_Copy(game);
                    Game_PlayTurn(cp, i);

                    self->children[i] = AINode_NewMinMax(cp, depth - 1, u, playerID);
                    //eval and sort 
                   // self->children[i]->score = Game_Eval(cp, playerID);
                    if (maxx < self->children[i]->score) {
                        maxx = self->children[i]->score;
                        self->move = i;
                    }
                    Game_Delete(cp);
                    continue;

                }
                self->children[i] = NULL;
            }
            self->score = maxx;
        }
        else {
            int minn = 100000000;
            for (int i = 0; i < GRID_W; i++) {
                if (Game_CanPlayAt(game, i)) {
                    Game* cp = Game_Copy(game);
                    Game_PlayTurn(cp, i);

                    self->children[i] = AINode_NewMinMax(cp, depth - 1, u, playerID);
                    //eval and sort 
                    //self->children[i]->score = Game_Eval(cp, playerID);
                    if (minn > self->children[i]->score) {
                        minn = self->children[i]->score;
                        self->move = i;
                    }
                    Game_Delete(cp);
                    continue;

                }
                self->children[i] = NULL;
            }
            self->score = minn;
        }

    }
    /////////
    // TODO : Implémentez l'algorithme MinMax

    return self;
}

AITree* AITree_NewMinMax(Game* game, int depth, int playerID)
{
    AITree* self = (AITree*)calloc(1, sizeof(AITree));
    AssertNew(self);

    Game* curGame = Game_Copy(game);
    self->root = AINode_NewMinMax(curGame, depth, false, playerID);

    return self;
}

void AITree_Delete(AITree* self)
{
    if (!self) return;

    AINode_DeleteRec(self->root);
    free(self);
}

int AI_ComputeMove(Game* game, int playerID)
{
    /////////
    // TODO : Cette fonction représente votre IA.
    // Modifiez-la comme vous le souhaitez.


    int depth = DEPTH;
    AITree* aiTree = AITree_NewMinMax(game, depth, playerID);

    //prit(aiTree->root, 2);
    int move = aiTree->root->move;
    AITree_Delete(aiTree);

    return move;
}
