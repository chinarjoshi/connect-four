#ifndef GAME_H
#define GAME_H

typedef enum
{
    kWinningNumber = 4
} GlobalVals;

int WinCheck (int x, int y, int dirx, int* board[], int* turn);
int Checker (int recurse, int x, int y, int dirx, int diry, int* board[]);
void Printer (int usecase, int recurse, int dimx, int dimy, int* board[]);

#endif