#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define EMPTY 0
#define WHITE 1
#define BLACK 2

bool recur(int **board, int *cell);
bool filled(int **board, int* cell);
bool valid(int **board);
void printboard(int **board);
void paint_black(int *cell);
void paint_white(int *cell);
void empty(int *cell);

int main(void){
    int r, c;
    scanf("%d%d", &r, &c);
    int array[2 * r + c + 1][c];  /* to record the size of array and the limit condition*/
    int *board[2 * r + c + 1];
    array[0][0] = r;
    array[0][1] = c;
    /*initialize the borad array*/
    for (int i = 0; i < (2 * r + c + 1); i++){
        board[i] = array[i];
        for (int j = 0; j < c; j++){
            if (i >= 1)
               array[i][j] = EMPTY; 
        }
    }
    /*save the limit condition to the array*/
    for (int i = r + 1; i < 2 * r + 1; i++){
        int number;
        scanf("%d", &number);
        array[i][0] = number;
        for (int j = 0; j < number; j++)
            scanf("%d", &(array[i][j + 1]));
    }

    for (int i = 2 * r + 1; i < (2 * r + c + 1); i ++){
        int number;
        scanf("%d", &number);
        array[i][0] = number;
        for (int j = 0; j < number; j++)
            scanf("%d", &(array[i][j + 1]));
    }

    recur(board, &(board[1][0]) - 1);

    system("pause");
    return 0;
}

bool recur(int **board, int *cell){
    if (filled(board, cell)){
        if (valid(board)){
            printboard(board);
            return true;
        }else
            return false;
    }else{
        cell++;

        /* try to paint it black */
        paint_black(cell);
        bool succeed = recur(board, cell);
        if (succeed)
            /*once succeed, we can stop trying*/ 
            return true;

        /*try to paint it white*/
        paint_white(cell);
        succeed = recur(board, cell);
        if (succeed)
            /*once succeed, we can stop trying*/
            return true;

        empty(cell);
        return false;
    }
}

bool filled(int **board, int *cell){
    int r = board[0][0];
    int c = board[0][1];
    if (cell == &(board[r][c - 1]))
        return true;

    return false;    
}

bool valid(int **board){
    int r = board[0][0];
    int c = board[0][1];
    /*check the condition of row*/
    for (int i = 0; i < r ; i++){
        int index = 0, count = 0;
        for (int j = 0; j < c; j++){
            if (board[i + 1][j] == BLACK)
                count++;
            if (count != 0 &&
                (board[i + 1][j] == WHITE || j == c - 1)){
                if (count != board[i + r + 1][index + 1])
                    return false;
                count = 0;
                index++;
            }
        }
        if (index != board[i + r + 1][0])
            return false;
    }
    /*check the condition of column*/
    for (int j = 0; j < c; j++){
        int index = 0, count = 0;
        for (int i = 0; i < r; i++){
            if (board[i + 1][j] == BLACK)
                count++;
            if (count != 0 &&
                (board[i + 1][j] == WHITE || i == r - 1)){
                if (count != board[j + 2 * r + 1][index + 1])
                    return false;
                count = 0;
                index++;
            }
        }
        if (index != board[j + 2 * r + 1][0])
            return false;
    }
    return true;
}

void printboard(int **board){
    int r = board[0][0];
    int c = board[0][1];
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            if (board[i + 1][j] == BLACK)
                printf("o");
            else if (board[i + 1][j] == WHITE)
                printf("_");
        }
        printf("\n");
    }
}


void paint_black(int *cell){
    *cell = BLACK;
}

void paint_white(int *cell){
    *cell = WHITE;
}

void empty(int *cell){
    *cell = EMPTY;
}