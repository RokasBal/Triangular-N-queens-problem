#include <iostream>
#include <vector>

using namespace std;

void printBoard(int boardSize);
void printAnswer(vector<vector<int>>& board, int boardSize);
void fillBoard(vector<vector<int>>& board, int boardSize);
bool solveProblem(vector<vector<int>>& board, int col, int boardSize);
bool isSafe(vector<vector<int>>& board, int row, int col, int boardSize);
void printVector(vector<vector<int>>& board, int boardSize);

int calls = 0;
int queensRemaining = 0;

int main() {
    system("clear");
    
    int queens, boardSize;

    cout << "Įrašykite karalienių skaičiu: ";
    cin >> queens;
    queensRemaining = queens;
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

    if(solveProblem(board, 0, boardSize)) {
        cout << "Sprendimas rastas!" << endl;
        printVector(board, boardSize);
        printAnswer(board, boardSize);
    } else {
        cout << "Sprendinio nerasta!" << endl;
    }

    cout <<"Calls: " <<calls <<endl;

    return 0;

}

void fillBoard(vector<vector<int>>& board, int boardSize) {
    for(int i = 0; i < boardSize; ++i) {
        int spacer = 0;
        for(int j = 0; j < boardSize - i - 1; ++j) {
            board[i][j] = 0;
            spacer++;
        }

        for(int k = 0; k < 2 * i + 1; ++k) {
            if(k % 2 == 0) {
                board[i][spacer + k] = 1;
            } else {
                board[i][spacer + k] = 0;
            }
        }
    }
}   

bool solveProblem(vector<vector<int>>& board, int row, int boardSize) {
    calls++;

    if (row >= boardSize)
        return true;

    // Iterate through all columns in the current row
    for (int i = 0; i < boardSize * 2 - 1; i++) {
        if (board[row][i] == 1 && isSafe(board, row, i, boardSize)) {
            board[row][i] = 2; // Place queen
            queensRemaining--;
            if (queensRemaining == 0) {
                return true;
            }

            printVector(board, boardSize);

            // Recur to the next row or any row below
            for (int nextRow = row + 1; nextRow < boardSize; nextRow++) {
                if (solveProblem(board, nextRow, boardSize))
                    return true;
            }

            board[row][i] = 1; // Backtrack
            queensRemaining++;
        }
        printVector(board, boardSize);
    }

    return false;
}

bool isSafe(vector<vector<int>>& board, int row, int col, int boardSize) {
    // Check if there's a queen in the same row
    for (int i = 0; i < boardSize * 2 - 1; ++i) {
        if (board[row][i] == 2 && i != col) // Check for queens in the same row, except the current column
            return false;
    }

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 2)
            return false;
    }

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < boardSize * 2 - 1; --i, ++j) {
        if (board[i][j] == 2)
            return false;
    }

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

void printVector(vector<vector<int>>& board, int boardSize) {
    for(int i = 0; i < boardSize; i++) {
        for(int j = 0; j < boardSize * 2 - 1; j++) {
            cout << board[i][j];
        }
        cout <<endl;
    }
    cout <<endl;
}

void printAnswer(vector<vector<int>>& board, int boardSize) {
    for(int i = 0; i < boardSize; ++i) {
        for(int j = 0; j < boardSize * 2 - 1; ++j) {
            if(board[i][j] == 0) {
                cout << " ";
            } else if(board[i][j] == 1) {
                cout << "*";
            } else {
                cout << "Q";
            }
        }
        cout <<endl;
    }
}