#ifndef INOUT_H
#define INOUT_H

#include "macros.h"
#include "gstruct.h"
#include "color.h"

/* Forward Declerations */
int** readfile(char* filename, int* size, int* rant, int* bant, int* error);
void printgame(GameStruct* data);

#endif