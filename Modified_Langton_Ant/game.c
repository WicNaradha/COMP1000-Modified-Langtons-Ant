#include "game.h"

/**
    *@brief Function main
    *@note  main function of the game
    *@retval int
*/

int main(int argc, char *argv[])
{
    int step = 0; /* Steps counter -> number of steps to run */
    int error = FALSE; /* Error state of game */
    GameStruct* data = makegamestruct(); /* Game data struct */
    initRandom(); /* Initialise random functions */

    if (argc != 4) /* Checking for invalid args */
    {
        error = ERROR;
        printf("ERROR: Insufficient Arguments for game!");
    }
    else
    {
        if (atoi(argv[2]) < 0) /* Checking for valid step count */
        {
            error = ERROR;
            printf("ERROR: Step count is of an invlid value \n");
        }
        if (atof(argv[3]) < 0) /* Checking for valid sleep time */
        {
            error = ERROR;
            printf("ERROR: Sleep time is of an invlid value \n");
        }
    }

    if (error != ERROR) /* Reading file if valid number of args are give */
    {
        data->colgrid = readfile(argv[1], data->size, data->rant, data->bant, &error);
    }

    if (error == FALSE) /* Run game */
    {
        printgame(data); /* Print initial frame */
        newSleep(atof(argv[3])); /* Wait sleep time */
        while(step <= atoi(argv[2]) && error != TRUE)
        {
            updategame(data); /* Update game data */
            printgame(data); /* Print updated frame */
            newSleep(atof(argv[3])); /* Wait sleep time */
            step++; /* Step = Step + 1 */
        }
    }
    else /* Game Error Case */
    {
        printf("ERROR : Usage ./ant <filename> <steps_amount> <sleep_length>"); 
    }
    
    freegamestruct(data, &error); /* Free Game Struct Data*/

    return 0;
}