/**
 *  @author: Chirayu.A.Joshi
 *
 *
 *      %e%%%%%%%%%
 *      %...%.%...%
 *      %.%.%.%.%%%
 *      %.%.......%
 *      %.%%%%.%%.%
 *      %.%.....%.%
 *      %%%%%%%%%x%
 *
 *  given location is x, find path to reach e.
*/

#include<iostream>
using namespace std;

// to finds number of rows in a given string (board).
int find_rows(string board) {
    int rows = 1;
    for (int i = 0; i < board.length(); i++) {
        if (board[i] == '\n') {
            ++rows;
        }
    }
    return rows;
}

// to finds number of columns in a given string (board).
int find_cols(string board) {
    int cols = 0, i = 0;
    while (board[i] != '\n') {
        ++cols;
        ++i;
    }
    return cols;
}

// to convert string into 2d array with number of rows and cols passed as an argument.
char** get_matrix(string board, const int NO_OF_ROWS, const int NO_OF_COLS) {
    char** board_matrix = new char*[NO_OF_ROWS]; // array of pointers.
    for (int i = 0; i < NO_OF_ROWS; i++) {
        board_matrix[i] = new char[NO_OF_COLS];
        for (int j = 0; j < NO_OF_COLS; j++) {
            board_matrix[i][j] = board[(i * NO_OF_COLS) + j + i];
        }
    }
    return board_matrix;
}

// to print 2d array.
void print_matrix(char** matrix, const int NO_OF_ROWS, const int NO_OF_COLS) {
    for (int i = 0; i < NO_OF_ROWS; i++) {
        for (int j = 0; j < NO_OF_COLS; j++) {
            cout << matrix[i][j];
        }
        cout << "\n";
    }
}

// to find a given character in an 2d array.
int* find_char(char ch, char** matrix, const int NO_OF_ROWS, const int NO_OF_COLS) {
    int* x_y = new int[2];
    for (int i = 0; i < NO_OF_ROWS; i++) {
        for (int j = 0; j < NO_OF_COLS; j++) {
            if (matrix[i][j] == ch) {
                x_y[0] = i;
                x_y[1] = j;
            }
        }
    }
    return x_y;
}

// this functions recursively checks UP, RIGHT, DOWN & LEFT.
/*
    UP    : find_path(CURRENT_POS_X + 1, CURRENT_POS_Y)
    RIGHT : find_path(CURRENT_POS_X, CURRENT_POS_Y + 1)
    DOWN  : find_path(CURRENT_POS_X - 1, CURRENT_POS_Y)
    LEFT  : find_path(CURRENT_POS_X, CURRENT_POS_Y - 1)
*/
bool find_path(char** board_matrix,
               const int* starting_point,
               const int* ending_point,
               const int NO_OF_ROWS,
               const int NO_OF_COLS) {
    // value must be within matrix.
    if (starting_point[0] > NO_OF_ROWS - 1 || starting_point[1] > NO_OF_COLS - 1 ||
        starting_point[0] < 0 || starting_point[1] < 0) {
        return false;
    }
    // end-point found.
    if (starting_point[0] == ending_point[0] && starting_point[1] == ending_point[1]) {
        return true;
    }
    // value must not be same as that of obstacle or previous itself.
    if (board_matrix[starting_point[0]][starting_point[1]] == '%' ||
        board_matrix[starting_point[0]][starting_point[1]] == '+') {
        return false;
    }
    // Mark the current spot.
    board_matrix[starting_point[0]][starting_point[1]] = '+';
    print_matrix(board_matrix, NO_OF_ROWS, NO_OF_COLS);
    cout << "\n\n\n";
    // recursion.
    // if path exists, move forward.
    int left[2] = {starting_point[0], starting_point[1] - 1};
    int right[2] = {starting_point[0], starting_point[1] + 1};
    int top[2] = {starting_point[0] - 1, starting_point[1]};
    int bottom[2] = {starting_point[0] + 1, starting_point[1]};
    if (find_path(board_matrix, left, ending_point, NO_OF_ROWS, NO_OF_COLS) ||
        find_path(board_matrix, right, ending_point, NO_OF_ROWS, NO_OF_COLS) ||
        find_path(board_matrix, top, ending_point, NO_OF_ROWS, NO_OF_COLS) ||
        find_path(board_matrix, bottom, ending_point, NO_OF_ROWS, NO_OF_COLS)) {
        return true;
    }
    // if nothing happens keep as it is and return false.
    board_matrix[starting_point[0]][starting_point[1]] = '.';
    return false;
}

/*
    Steps to complete the task:
    1. Generate the map.
    2. Find starting point and ending point by creating a
       function called findChar().
    3. Create a function print_matrix() which prints the matrix which it receives from input.
    4. Create a function find_path() which takes starting point and ending point
       and finds path.
*/
int main() {

    // to-do: assign board from a outside file.
    // this is the above given map which has to be solved.
    string board = "%e%%%%%%%%%\n%...%.%...%\n%.%.%.%.%%%\n%.%.......%\n%.%%%%.%%.%\n%.%.....%.%\n%%%%%%%%%x%";
    const int NO_OF_ROWS = find_rows(board);
    const int NO_OF_COLS = find_cols(board);
    // to convert string named board into a 2d matrix.
    char** board_matrix = get_matrix(board, NO_OF_ROWS, NO_OF_COLS);
    const int* starting_point = find_char('x', board_matrix, NO_OF_ROWS, NO_OF_COLS);
    const int* ending_point = find_char('e', board_matrix, NO_OF_ROWS, NO_OF_COLS);

    find_path(board_matrix, starting_point, ending_point, NO_OF_ROWS, NO_OF_COLS);

    return 0;
}
