#include "inout.h"

/**
    *@brief Function rcread
    *@param file, Pointer to FILE type
    *@param size, Pointer to size data array
    *@param eof, Pointer to eof state of file  
    *@note Function to read row col size from file
    *@retval void
*/

static void rcread(FILE* file, int* size, int* eof)
{
    *eof = fscanf(file,"%d %d", &size[0], &size[1]);
}

/**
    *@brief Function antread
    *@param file, Pointer to FILE type
    *@param antarr, Pointer to ant data array
    *@param eof, Pointer to eof state of file  
    *@note Function to read ant data from file
    *@retval void
*/

static void antread(FILE* file, int* antarr, int* eof)
{
    char t;

    *eof = fscanf(file,"%d %d %c", &antarr[0], &antarr[1], &t);  
    if (*eof == 3)
    {
        switch (t)
        {
        case '^':
            antarr[2] = UP;
            break;
        case '>':
            antarr[2] = RIGHT;
            break;
        case '<':
            antarr[2] = LEFT;
            break;
        case 'v':
            antarr[3] = LEFT;
            break;
        default:
            *eof = -1;
            break;
        }
    }
}

/**
    *@brief Function rcread
    *@param file, Pointer to FILE type
    *@param i, Iterator value to read at
    *@param size, Pointer to size data array
    *@param eof, Pointer to eof state of file  
    *@note Function to read char of colgrid from file
    *@retval void
*/

static void arraylineread(FILE* file, int i,int size, int* eof)
{
    int val;

    if (*eof >= 0)
    {
        if (i<(size-1))
        {
            *eof = fscanf(file,"%d ",&val);
        }
        else if (i==(size-1))
        {
            *eof = fscanf(file,"%d\n",&val);
        }

        if ((*eof >= 0) && (val == 0 || val == 1))
        {
            *eof = val;
        }
        else
        {
            *eof = ARR_ERROR;
        }
    }

}

/**
    *@brief Function readarray to read cell states
    *@param file, Pointer to FILE type
    *@param colarray, colarray -> for cell states
    *@param size, Pointer to size data array
    *@param eof, Pointer to eof state of file  
    *@note Function to read colgrid from file
    *@retval void
*/

static void readarray(FILE* file, int** colarray, int* size, int* eof)
{
    int r, c;

    for(r=0;r<size[0];r++)
    {
        for (c=0;c<size[1];c++)
        {
            arraylineread(file,c,size[1],eof);
            if (*eof == 0)
            {
                colarray[r][c] = NONE;
            }
            else if (*eof == 1)
            {
                colarray[r][c] = GREEN;
            }
        }
    }
}

/**
    *@brief Function printreaderror
    *@param i, Iterator of error type
    *@note Function to print read errors
    *@retval void
*/

static void printreaderror(i)
{
    switch (i-1)
    {
    case 0:
        printf("ReadError : Array size read.\n");
        break;
    case 1:
        printf("ReadError : Red Ant data read.\n");
        break;
    case 2:
        printf("ReadError : Blue Ant read.\n");
        break;
    case 3:
        printf("ReadError : Color array read.\n");
        break;
    
    default:
        break;
    }
}

/**
    *@brief Function readfile
    *@param filename, Name of file to be read
    *@param size, Pointer to size data array
    *@param rant, Pointer to red ant data array
    *@param bant, Pointer to blue ant data array
    *@param error, Pointer to error state of game  
    *@note Function to read file data into gamestruct
    *@retval int** colgrid
*/

int** readfile(char* filename, int* size, int* rant, int* bant, int* error)
{
    FILE* file;
    int **colarray, i = 0, eof = 0;
    file = fopen(filename,"r");

    if (file == NULL)
    {
        printf("ERROR: Could not open %s\n",filename);
        *error = ERROR; 
    }
    else
    {
        while(eof >= 0 && i < 4)
        {
            switch (i)
            {
            case 0:
                rcread(file,size, &eof);
                if (size[0] < 0 || size[1] < 0)
                {
                    eof = -1;
                }
                i++;
                break;
            case 1:
                antread(file,rant, &eof);
                if (rant[0] < 0 || rant[1] < 0 || rant[0] >= size[0] || rant[1] >= size[1])
                {
                    eof = -1;
                }
                i++;
                break;
            case 2:
                antread(file,bant, &eof);
                if (bant[0] < 0 || bant[1] < 0 || bant[0] >= size[0] || bant[1] >= size[1])
                {
                    eof = -1;
                }
                i++;
                break;
            case 3:
                colarray = makecolarray(size[0],size[1]);
                readarray(file, colarray, size, &eof);
                i++;
                break;
            
            default:
                break;
            }

            if (eof < 0)
            {
                printreaderror(i);
                if (eof == ARR_ERROR)
                {
                    *error = ARR_ERROR;
                }
                else
                {
                    *error = ERROR;
                }
            }
        }

        if(ferror(file)) {
            perror("Error reading from file!\n");
            *error = ERROR;
        }

        fclose(file);

    }
    return colarray;
}

/**
    *@brief Function setcellstate
    *@param colval, The color value to set BG color
    *@note Function to set the BG color
    *@retval void
*/

static void setcellstate(int colval)
{
    switch (colval)
    {
    case (BLUE):
        setBackground("blue");
        break;
    case (RED):
        setBackground("red");
        break;
    case (GREEN):
        setBackground("green");
        break;

    default:
        break;
    }
}

/**
    *@brief Function printant
    *@param dir, The direction of the ant
    *@param color, String for ant color
    *@note Function to print ant
    *@retval void
*/


static void printant(int dir, char* color)
{
    switch (dir)
    {
    case (UP):
        setForeground(color,'1');
        printf("^");
        setForeground("reset",'0');
        break;
    case (DOWN):
        setForeground(color,'1');
        printf("v");
        setForeground("reset",'0');
        break;
    case (LEFT):
        setForeground(color,'1');
        printf("<");
        setForeground("reset",'0');
        break;
    case (RIGHT):
        setForeground(color,'1');
        printf(">");
        setForeground("reset",'0');
        break;

    default:   
        break;
    }
}

/**
    *@brief Function printborder
    *@param width, The width of the array
    *@note Function to print border
    *@retval void
*/

static void printborder(int width)
{
    int i;
    for(i=0;i<width+2;i++)
    {
        printf("*");
    }
    printf("\n");
}

/**
    *@brief Function printgame
    *@param data, Pointer to GameStruct data
    *@note Function to print game
    *@retval void
*/

void printgame(GameStruct* data)
{
    int r, c;
    
    system("clear");

    printborder(data->size[1]);

    for(r=0;r<data->size[0];r++)
    {
        printf("*");

        for(c=0;c<data->size[1];c++)
        {
            setcellstate(data->colgrid[r][c]);
            if (r == data->rant[0] && c == data->rant[1])
            {
                printant(data->rant[2],"yellow");
            }
            else if (r == data->bant[0] && c == data->bant[1])
            {
                printant(data->bant[2],"cyan");
            }
            else
            {
                printf(" ");
                setBackground("reset");
            }
        }

        printf("*\n");
    }

    printborder(data->size[1]);
}