/*
time complexity: O(n)
solution to Knight's tour problem using Warnsdorff’s algorithm

Warnsdorff’s Rule: 
1) We can start from any initial position of the knight on the board.
2) We always move to an adjacent, unvisited square with minimal degree (minimum number of unvisited adjacent).
*/

//TODO algorithm works perfectly, just make better return
//TODO handle small N (2, 3, 4)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#define N 8


const int EMPTY_NUM = -1;
const int MOVE_ROW[N] = {2, 1, -1, -2, -2, -1, 1, 2};
const int MOVE_COL[N] = {1, 2, 2, 1, -1, -2, -2, -1};


int KTmain(char *pos, int n);
bool solveKnightTour(int row, int col, int n, int board[n][n], int count);
void print_out(int n, int board[n][n]);


int main(void)
{
    while (true) {
        int n;
        char *pos = malloc(5);  
        if (pos == NULL) return 1;
        printf("\nEnter N: ");  
        scanf("%d", &n);
        while (strcmp(pos, "x") != 0) {
            printf("\n(press x to assign new N value)\nEnter starting position of the Knight: ");  
            scanf("%s", pos);
            KTmain(pos, n);
        }
    }
}


int KTmain(char *pos, int n) 
{
    clock_t t = clock();
    int board[n][n];
    memset(board, EMPTY_NUM, sizeof(board));
    int col = pos[0] - 97; 
    pos++;
    int pos_num = atoi(pos);
    if (pos_num == 0) return 0;
    int row = n - pos_num;
    int count = 0;
    board[row][col] = count;
    if (solveKnightTour(row, col, n, board, count+1)) {
        t = clock() - t;
        double run_time = (double)t/CLOCKS_PER_SEC;
        printf("\nFinished in %.3fs\n", run_time);
        print_out(n, board);
        return 0;
    }
    printf("No solutions found.\n");
    return 0;
}


int min(int arr[N])
{
    int index, degree = 9;
    for (int i = 0; i < N; i++) if (arr[i] < degree) index = i, degree = arr[i];
    return index;
}


bool isSafe(int row, int col, int n, int board[n][n])
{
    return (row >= 0 && row < n && col >= 0 && col < n && board[row][col] == EMPTY_NUM);
}


int getDegree(int row, int col, int n, int board[n][n])
{
    int degree = 0;
    for (int i = 0; i < 8; i++) {
        int newRow = MOVE_ROW[i] + row;
        int newCol = MOVE_COL[i] + col;
        if (isSafe(newRow, newCol, n, board)) degree++;
    } 
    return degree;
}


bool solveKnightTour(int row, int col, int n, int board[n][n], int count)
{
    if (count == n*n) return true;
    int degrees[N] = {9, 9, 9, 9, 9, 9, 9, 9};
    int newRow, newCol;
    for (int i = 0; i < 8; i++) {
        newRow = MOVE_ROW[i] + row;
        newCol = MOVE_COL[i] + col;
        if (isSafe(newRow, newCol, n, board)) degrees[i] = getDegree(newRow, newCol, n, board);
        else degrees[i] = 9;
    }
    int i = min(degrees);
    newRow = MOVE_ROW[i]+row;
    newCol = MOVE_COL[i]+col;
    board[newRow][newCol] = count;
    return solveKnightTour(newRow, newCol, n, board, count+1);
}


void print_out(int n, int board[n][n])
{
    for (int i = 0; i < n; i++) printf("   %c ", 'a' + i%26);
    printf("\n");
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) printf("%4d ", board[i][j]);
        printf("|%i\n", n - i);
    }
}
