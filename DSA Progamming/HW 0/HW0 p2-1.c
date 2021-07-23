#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define EMPTY 0
#define WHITE 1
#define BLACK 2


struct nanogram {
    int r;
    int c;
    int **board;
    int **limit_r;
    int **limit_c;
};
typedef struct nanogram Nanogram;

bool recur(Nanogram *mynanogram, int* cell);
bool filled(Nanogram *mynanogram, int* cell);
bool valid(Nanogram *mynanogram);
void printboard(Nanogram *mynanogram);
void paint_black(int *cell);
void paint_white(int *cell);
void empty(int *cell);


int main(void){
    int r, c;
    scanf("%d%d", &r, &c);
    int array[r][c];  /* to record the size of array and the limit condition*/
    int *board[r];
    /*initialize the board array*/
    for (int i = 0; i < r; i++){
        board[i] = array[i];
        for (int j = 0; j < c; j++){
            array[i][j] = EMPTY; 
        }
    }
    int condition_r[r][c + 1];
    int *limit_r[r];

    /*save the limit condition to the array*/
    for (int i = 0; i < r; i++){
        int number;
        scanf("%d", &number);
        condition_r[i][0] = number;
        limit_r[i] = condition_r[i];
        for (int j = 0; j < number; j++)
            scanf("%d", &(condition_r[i][j + 1]));
    }
    int condition_c[c][r + 1];
    int *limit_c[c];
    for (int j = 0; j < c; j ++){
        int number;
        scanf("%d", &number);
        condition_c[j][0] = number;
        limit_c[j] = condition_c[j];
        for (int i = 0; i < number; i++)
            scanf("%d", &(condition_c[j][i + 1]));
    }

    Nanogram mynanogram;
    Nanogram *ptr = &(mynanogram);
    ptr->r = r;
    ptr->c = c;
    ptr->board = &(board[0]);
    ptr->limit_r = &(limit_r[0]);
    ptr->limit_c = &(limit_c[0]);
    recur(ptr, &(board[0][0]) - 1);

    system("pause");
    return 0;
}

bool recur(Nanogram *mynanogram, int* cell){
    if (filled(mynanogram, cell)){
        if (valid(mynanogram)){
            printboard(mynanogram);
            return true;
        }else
            return false;
    }else{
        cell++;
        
        /* try to paint it black */
        paint_black(cell);
        bool succeed = recur(mynanogram, cell);
        if (succeed)
            /*once succeed, we can stop trying*/ 
            return true;

        /*try to paint it white*/
        paint_white(cell);
        succeed = recur(mynanogram, cell);
        if (succeed)
            /*once succeed, we can stop trying*/
            return true;

        empty(cell);
        return false;
    }
}

bool filled(Nanogram *mynanogram, int* cell){
    int r = mynanogram->r;
    int c = mynanogram->c;
    int **board = mynanogram->board;
    if (cell == &(board[r - 1][c - 1]))
        return true;

    return false;    
}

bool valid(Nanogram *mynanogram){
    int r = mynanogram->r;
    int c = mynanogram->c;
    int **board = mynanogram->board;
    int **limit_r = mynanogram->limit_r;
    int **limit_c = mynanogram->limit_c;
    /*check the condition of row*/
    for (int i = 0; i < r ; i++){
        int index = 0, count = 0;
        for (int j = 0; j < c; j++){
            if (board[i][j] == BLACK)
                count++;
            if (count != 0 &&
                (board[i][j] == WHITE || j == c - 1)){
                if (count != limit_r[i][index + 1])
                    return false;
                count = 0;
                index++;
            }
        }
        if (index != limit_r[i][0])
            return false;
    }
    /*check the condition of column*/
    for (int j = 0; j < c; j++){
        int index = 0, count = 0;
        for (int i = 0; i < r; i++){
            if (board[i][j] == BLACK)
                count++;
            if (count != 0 &&
                (board[i][j] == WHITE || i == r - 1)){
                if (count != limit_c[j][index + 1])
                    return false;
                count = 0;
                index++;
            }
        }
        if (index != limit_c[j][0])
            return false;
    }
    return true;
}

void printboard(Nanogram *mynanogram){
    int r = mynanogram->r;
    int c = mynanogram->c;
    int **board = mynanogram->board;
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            if (board[i][j] == BLACK)
                printf("o");
            else if (board[i][j] == WHITE)
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