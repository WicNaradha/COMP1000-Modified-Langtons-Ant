#ifndef GSTR_H
#define GSTR_H

typedef struct GameStruct{
    int *size;
    int *rant;
    int *bant;
    int **colgrid;
} GameStruct;

#include "macros.h"

/* Forward Declerations */
int** makecolarray(int row, int col);
GameStruct* makegamestruct();
void freegamestruct(GameStruct* data, int* error);

#endif