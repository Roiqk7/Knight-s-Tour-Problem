//  time complexity: O(n!)
//  solution to knight's tour problem using backtracking algorithm


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

const int EMPTY_NUM = -1;
const int MOVE_ROW[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int MOVE_COL[8] = {1, 2, 2, 1, -1, -2, -2, -1};

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
            printf("(press x to assign new N value)\nEnter starting position of the Knight: ");  
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


bool isSafe(int row, int col, int n, int board[n][n])
{
    return (row >= 0 && row < n && col >= 0 && col < n && board[row][col] == EMPTY_NUM);
}


bool solveKnightTour(int row, int col, int n, int board[n][n], int count)
{
    if (count == n*n) return true;
    for (int i = 0; i < 8; i++) {
        int newRow = MOVE_ROW[i] + row;
        int newCol = MOVE_COL[i] + col;
        if (isSafe(newRow, newCol, n, board)) {
            board[newRow][newCol] = count;
            if (solveKnightTour(newRow, newCol, n, board, count+1)) return true;
            else board[newRow][newCol] = EMPTY_NUM;
        }
    }
    return false;
}


void print_out(int n, int board[n][n])
{
    for (int i = 0; i < n; i++) printf(" %c ", 'a' + i%26);
    printf("\n");
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) printf("%2d ", board[i][j]);
        printf("|%i\n", n - i);
    }
}
