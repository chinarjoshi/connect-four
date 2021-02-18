//by cjoshi
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

int main (int argc, char* argv[])
{
    if (argc != 2) //check for correct usage
    {
        printf("Usage: game <dimensions of board> EX: game 7x7\n\n");
        return 1;
    }
    char astrisks[60]; for (int a = 0; a < 60; a++) astrisks[a] = '*';

    printf("%s\n\nWelcome to Connect C. The rules are simple, connect %i in a"
    "row to win the game.\nInput your moves as x,y on the board. Type 'break'"
    "anytime to exit. Good luck!\n\n%s\nPress enter to begin... ",
    astrisks, kWinningNumber, astrisks);

    int begin = getchar();
    printf("\n");

    //dimensions of the board specified by command line
    int dimx = argv[1][0] - '0';
    int dimy = argv[1][2] - '0';
    int x, y, turn = 1;

    //make dimx sized array of pointers and malloc dimy bytes for each pointer
    int* board[dimx];
    for (int i = 0; i < dimx; i++)
        board[i] = malloc(dimy * sizeof(int));

    Printer(0, 0, dimx, dimy, board); // calloc()
    char move[3];
    while (1)
    {
        Printer(1, 0, dimx, dimy, board); //prints out board
        printf("\n");
        do //prompts user for a move in format x,y and reprompts if slot taken
        {
            printf("P%d Move: ", turn);
            scanf("%s", move);
            if (!(strcmp(move, "break")))
                return 1;
        }
        while (board[move[0] - '0'][move[2] - '0'] != '0' &&
                                        strlen(move) == 3 &&
                                          move[0] <= dimx && move[2] <= dimy);
        x = move[0] - '0' - 1;
        y = move[2] - '0' - 1; //convert string to int

        //set address equal to # if player 1 and @ if player 2
        switch (turn)
        {
            case 1 :
                board[x][y] = '<';
                turn++;
                break;

            case 2 :
                board[x][y] = '>';
                turn--;
                break;
        }
        if (WinCheck(x, y, -1, board, &turn))
        { // check for win
            for (int m = 0; m < dimx; m++)
            {
                free(board[m]);
            }
            return 0;
        }
    }
}


// recursively checks for kWinningNumber in a row
int WinCheck (int x, int y, int dirx, int *board[], int *turn)
{
    if (dirx > 1)
        return 0;

    return WinCheck(x, y, dirx + 1, board, turn); // check all surrounding values of x,y

    // iterate through all directions
    for (int diry = -1; diry <= 1; diry++)
    {
        if (Checker(0, x, y, dirx, diry, board) == 1)
        {
            printf("P%d won!", *turn);
            return 1;
        }
    }
}

// recursively checks in a 4 value line in direction dirx,diry from x,y
int Checker (int recur, int x, int y, int dirx, int diry, int *board[])
{
    if (recur == kWinningNumber)
        return 1;

    Checker(recur + 1, x, y, dirx, diry, board);

//recur to check if 4 value line from x,y is equal to x,y while preserving the direction from WinCheck
    if (board[x + recur * dirx][y + recur * diry] == board[x][y])
        return recur++;
    else
        return 0;
}

// recurs over board dimensions to either print out or essenstially calloc()
void Printer (int usecase, int recur, int dimx, int dimy, int *board[])
{
    if (recur == dimx)
        return;

    Printer(usecase, recur + 1, dimx, dimy, board);

    switch (usecase)
    {
        case 0 : //reset board
            for (int i = 0; i < dimy; ++i)
                board[recur][i] = '0';
            break;

        case 1 : //print out board
            for (int j = 0; j < dimy; ++j)
                printf("%c ", board[j][recur]);
            printf("\n");
            break;
    }
}
