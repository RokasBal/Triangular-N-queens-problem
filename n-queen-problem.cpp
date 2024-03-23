#include <iostream>
#include <vector>

using namespace std;

void printBoard(int boardSize);
void fillBoard(vector<vector<int>>& board, int boardSize);

int main() {
    int queens, boardSize;

    cout << "Įrašykite karalienių skaičiu: ";
    cin >> queens;
    cout << "Įrašykite lentos dydį: ";
    cin >> boardSize;

    vector<vector<int>> board(boardSize, vector<int>(boardSize * 2 - 1));

    // Trikampes lentos spausdinimas
    printBoard(boardSize);

    // Lentos masyvo užpildymas
    fillBoard(board, boardSize);

    // Vektoriaus testavimas
    // for(int i = 0; i < boardSize; i++) {
    //     for(int j = 0; j < boardSize * 2 - 1; j++) {
    //         cout << board[i][j];
    //     }
    //     cout << endl;
    // }

    return 0;

}

void fillBoard(vector<vector<int>>& board, int boardSize) {
    for(int i = 0; i < boardSize; ++i) {
        int spacer = 0;
        for (int j = 0; j < boardSize - i - 1; ++j) {
            board[i][j] = 0;
            spacer++;
        }

        for (int k = 0; k < 2 * i + 1; ++k) {
            if(k % 2 == 0) {
                board[i][spacer + k] = 1;
            } else {
                board[i][spacer + k] = 0;
            }
        }
    }
}   

bool solveProblem(vector<vector<int>>& board, int col, int boardSize) {
    // base case: If all queens are placed
    // then return true
    if (col >= boardSize * 2 - 1)
        return true;
 
    // Consider this column and try placing
    // this queen in all rows one by one
    for (int i = 0; i < boardSize * 2 - 1; i++) {
         
        // Check if the queen can be placed on
        // board[i][col]
        if (isSafe(board, i, col, boardSize)) {
             
            // Place this queen in board[i][col]
            board[i][col] = 1;
 
            // recur to place rest of the queens
            if (solveProblem(board, col + 1, boardSize))
                return true;
 
            // If placing queen in board[i][col]
            // doesn't lead to a solution, then
            // remove queen from board[i][col]
            board[i][col] = 0; // BACKTRACK
        }
    }
 
    // If the queen cannot be placed in any row in
    // this column col  then return false
    return false;
}

// A utility function to check if a queen can
// be placed on board[row][col]. Note that this
// function is called when "col" queens are
// already placed in columns from 0 to col -1.
// So we need to check only left side for
// attacking queens
bool isSafe(vector<vector<int>>& board, int row, int col, int boardSize)
{
    int i, j;
 
    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;
 
    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;
 
    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < boardSize; i++, j--)
        if (board[i][j])
            return false;
 
    return true;
}

void printBoard(int boardSize) {
    for(int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize - i - 1; ++j) {
            cout << " ";
        }

        int counter = 1;
        for (int k = 0; k < 2 * i + 1; ++k) {
            if(k % 2 == 0) {
                cout <<counter;
                counter++;
            } else {
                cout <<" ";
            }
        }
        cout <<endl;
    }
}

