#include "grids.h"

/**
    *@brief Function turn_clockwise
    *@param ant: Array describing ant position and direction
    *@note Function to turn the ant clockwise
    *@retval void
*/

static void turn_clockwise(int* ant)
{
    switch (ant[2]) /* ant[2] -> stands for ant direction */
    {
    case UP:
        ant[2]++;
        break;
    case RIGHT:
        ant[2]++;
        break;
    case DOWN:
        ant[2]++;
        break;
    case LEFT:
        ant[2] = UP;
        break;
    default:
        break;
    }
}

/**
    *@brief Function turn_anticlockwise
    *@param ant: Array describing ant position and direction
    *@note Function to turn the ant anitclockwise
    *@retval void
*/

static void turn_anticlockwise(int* ant)
{
    switch (ant[2]) /* ant[2] -> stands for ant direction */
    {
    case LEFT:
        ant[2]--;
        break;
    case DOWN:
        ant[2]--;
        break;
    case RIGHT:
        ant[2]--;
        break;
    case UP:
        ant[2] = LEFT;
        break;
    default:
        break;
    }
}

/**
    *@brief Function turn_clockwise
    *@param color: pointer to value with cell color
    *@param rant: Array describing red ant position and direction
    *@note Function to turn the red ant clockwise
    *@retval void
*/

static void turnredant(int* color, int* rant)
{
    switch (*color)
    {
    case RED:
        turn_anticlockwise(rant);
        *color = NONE;
        break;
    case BLUE:
        turn_anticlockwise(rant);
        *color = NONE;
        break;
    case GREEN:
        turn_anticlockwise(rant);
        *color = NONE;
        break;
    default:
        turn_clockwise(rant); 
        *color = RED;
        break;
    }
}

/**
    *@brief Function turn_clockwise
    *@param color: pointer to value with cell color
    *@param bant: Array describing red ant position and direction
    *@note Function to turn the blue ant clockwise
    *@retval void
*/

static void turnblueant(int* color, int* bant)
{
    bant[2] = random(0,3);

    if (*color == NONE)
    {
        *color = BLUE;
    }
    else
    {
        *color = NONE;
    }
}

/**
    *@brief Function move ant
    *@param size: Array describing red ant position and direction
    *@param mant: Array describing moving ant position and direction
    *@param oant: Array describing other ant position and direction
    *@note Function to turn the move an ant
    *@retval void
*/

static void antmove(int* size, int* mant, int* oant)
{
    int np[2];

    np[0] = mant[0]; /* ant original row position */
    np[1] = mant[1]; /* ant original col position */

    switch (mant[2]) /* Moving ant forward based on direction it faces */
    {
    case UP:
        np[0] = mant[0]-1;
        break;
    case DOWN:
        np[0] = mant[0]+1;
        break;
    case LEFT:
        np[1] = mant[1]-1;
        break;
    case RIGHT:
        np[1] = mant[1]+1;
        break;
    default:
        break;
    }

    if (np[0] < 0) /* Checking for out of border row */
    {
        np[0] = 0;
    }
    else if (np[0] >= size[0])
    {
        np[0] = size[0]-1;
    }

    if (np[1] < 0) /* Checking for out of border col */
    {
        np[1] = 0;
    }
    else if (np[1] >= size[1])
    {
        np[1] = size[1]-1;
    }

    if (np[0] != oant[0] && np[1] != oant[1]) /* Checking if new ant pos and old ant pos is the same */
    {
        mant[0] = np[0];
        mant[1] = np[1];
    }
}

/**
    *@brief Function updategame
    *@param data: Game Struct describing data
    *@note Function to update the game every instance
    *@retval void
*/

void updategame(GameStruct* data)
{
    turnredant(&(data->colgrid[data->rant[0]][data->rant[1]]), data->rant); /* Turn red ant */
    turnblueant(&(data->colgrid[data->bant[0]][data->bant[1]]), data->bant); /* Turn Blue ant */

    antmove(data->size, data->rant, data->bant); /* Move red ant */
    antmove(data->size, data->bant, data->rant); /* Move Blue ant */
}