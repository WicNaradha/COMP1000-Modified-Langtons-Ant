#include "grids.h"

/**
    *@brief Function makecolarray
    *@param row: row size of colarray
    *@param col: col size of colarray
    *@note Function to make colarray
    *@retval int**
*/

int** makecolarray(int row, int col)
{
    int** colarray, r;

    colarray = (int**)calloc(row,sizeof(int*));
    for(r=0;r<row;r++)
    {
        colarray[r] = (int*)calloc(col,sizeof(int));
    }

    return colarray;
}

/**
    *@brief Function freecolarray
    *@param row: row size of colarray
    *@param colarray: colarray to be freed
    *@param error: error state from game
    *@note Function to make colarray
    *@retval void
*/

static void freecolarray(int row, int** colarray, int error)
{
    int r;

    if (error == ERROR)
    {
        colarray = NULL;
    }
    else
    {
        for(r=0;r<row;r++)
        {
            free(colarray[r]);
            colarray[r] = NULL;
        }
        free(colarray);
        colarray = NULL;
    }

}

/**
    *@brief Function makegamestruct
    *@note Function to make an empty game struct
    *@retval Pointer to GameStruct
*/

GameStruct* makegamestruct()
{
    GameStruct* data = (GameStruct*)calloc(1,sizeof(GameStruct));

    data->size = (int*)calloc(2,sizeof(int));
    data->rant = (int*)calloc(3,sizeof(int));
    data->bant = (int*)calloc(3,sizeof(int));

    return data;
}

/**
    *@brief Function freegamestruct
    *@param data: GameStruct pointer to data to be freed
    *@param error: pointer to game error state
    *@note Function to free GameStruct
    *@retval void
*/

void freegamestruct(GameStruct* data, int* error)
{
    freecolarray(data->size[0], data->colgrid, *error);

    free(data->rant);
    data->rant = NULL;

    free(data->bant);
    data->bant = NULL;

    free(data->size);
    data->size = NULL;

    free(data);
    data = NULL;
}
