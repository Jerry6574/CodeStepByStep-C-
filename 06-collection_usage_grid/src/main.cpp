#include <iostream>
#include "console.h"
#include "ginteractors.h" // for GWindow
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector

using namespace std;

bool knightCanMove(Grid<string>& board, int r1, int c1, int r2, int c2) {

    if(board.inBounds(r2, c2) && board[r2][c2] == "" && board[r1][c1] == "knight"){
        if((r1-2 == r2 || r1+2 == r2) && (c1+1 == c2 || c1-1 == c2)){
            return true;
        } else if((r1-1 == r2 || r1+1 == r2) && (c1+2 == c2 || c1-2 == c2)){
            return true;
        } else{
            return false;
        }
    } else{
        return false;
    }
}

int crossSum(Grid<int>& grid, int row, int col) {
    int sum = 0;

    for(int i = 0; i < grid.height(); i++){
        sum += grid[i][col];
    }

    for(int i = 0; i < grid.width(); i++){
        if(i != col){
            sum += grid[row][i];
        }
    }

    return sum;
}


void rotate(Grid<int>& matrix) {

    // top ->        right
    //                  |
    //                  V
    // {{ 6,  1,  9,  4},
    // {-2,  5,  8, 12},
    // {14, 39, -6, 18},
    // {21, 55, 73, -3}}
    //  ^
    //  |
    // left         <- bottom

    int layers = matrix.width() / 2;
    int size = matrix.width();

    for(int i = 0; i < layers; i++){
        for(int j = i; j < size-i-1; j++){
            int temp = matrix[i][j];

            // left to top
            matrix[i][j] = matrix[size-j-1][i];

            // bottom to left
            matrix[size-j-1][i] = matrix[size-i-1][size-j-1];

            // right to bottom
            matrix[size-i-1][size-j-1] = matrix[j][size-i-1];

            // top to right
            matrix[j][size-i-1] = temp;
        }
    }
}

void reshape(Grid<int>& grid, int rows, int cols) {
    Vector<int> values;
    for(int num: grid){
        values.add(num);
    }

    grid.resize(rows, cols);

    if(rows != 0 || cols != 0){
        int r = 0;
        int c = 0;
        for(int v: values){
            if(c == cols){
                c = 0;
                r++;
            }
            if(r == rows){
                break;
            }

            grid[r][c] = v;
            c++;
        }
    }
}

void multTable(Grid<int>& grid, int max) {
    grid.resize(max, max);

    for(int i = 0; i < max; i++){
        for(int j = 0; j < max; j++){
            grid[i][j] = i*j;
        }
    }
}

void mirror(Grid<int>& grid) {
    for(int i = 0; i < grid.height()-1; i++){
        for(int j = i+1; j < grid.width(); j++){
            int temp = grid[i][j];
            grid[i][j] = grid[j][i];
            grid[j][i] = temp;
        }
    }
}

int main() {
    Grid<int> grid = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    cout << crossSum(grid, 1, 1) << endl;

    return 0;
}
