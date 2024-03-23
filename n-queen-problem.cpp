#include <iostream>
#include <vector>
#include <fstream>
#include "string.h"

using namespace std;

#define dataFile "data.txt"

void printBoard(int boardSize, ofstream& output);
void printAnswer(vector<vector<int>>& board, int boardSize, ofstream& output);
void fillBoard(vector<vector<int>>& board, int boardSize);
bool solveProblemUtil(vector<vector<int>>& board, int row, int boardSize, ofstream& output);
void solveProblem(int queenCount, int boardSize);
bool isSafe(vector<vector<int>>& board, int row, int col, int boardSize);
void printVector(vector<vector<int>>& board, int boardSize);
void printScript(ofstream& output);
void printInfo(ofstream& output);

int calls = 0;
int queensRemaining = 0;
int queenCount = 0;
int boardSize = 0;
int backtrackDepth = 0;

int main() {
    system("clear");

    cout << "Įrašykite karalienių skaičiu: ";
    cin >> queenCount;
    queensRemaining = queenCount;
    cout << "Įrašykite lentos dydį: ";
    cin >> boardSize;

    solveProblem(queenCount, boardSize);

    cout <<"Calls: " <<calls <<endl;

    return 0;

}

void solveProblem(int queenCount, int boardSize) {
    vector<vector<int>> board(boardSize, vector<int>(boardSize * 2 - 1));
    fillBoard(board, boardSize);

    ofstream output("output.txt");
    if (!output.is_open()) {
        cerr << "Klaida atidarant faila!" <<endl;
        exit(1);
    }

    printScript(output);
    printInfo(output);

    if(solveProblemUtil(board, 0, boardSize, output)) {
        output <<endl <<"Trečia dalis - Rezultatai: " <<endl <<endl;
        output <<"Sprendimas rastas! Atlikta " <<calls <<" bandymų." <<endl <<endl;
        output <<"Sprendimas pavaizduotas lentoje: " <<endl;
        printAnswer(board, boardSize, output);
    } else {
        output <<endl <<"Trečia dalis - Rezultatai: " <<endl <<endl;
        output << "Sprendinio nerasta! Atlikta " <<calls <<" bandymų." << endl;
    }
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

bool solveProblemUtil(vector<vector<int>>& board, int row, int boardSize, ofstream& output) {
    // Jei eilutės skaičius viršija lentos dydį, sprendinio nėra
    if (row >= boardSize)
        return false;

    // Praeinama pro visas vietas eilutėje
    for (int col = 0; col < boardSize * 2 - 1; col++) {
        if(board[row][col] == 1 || board[row][col] == 2) {
            calls++;
            for(int i = 0; i < backtrackDepth; i++) output <<"-";
            output <<"Bandome valdove " <<queenCount - queensRemaining + 1 <<". ";
        }

        if (board[row][col] == 1 && isSafe(board, row, col, boardSize)) {
            // Padėti karalienę
            board[row][col] = 2;
            queensRemaining--;
            backtrackDepth++;

            output <<"Pastatyta langelyje " <<row + 1 <<", " <<col + 1 <<", likes valdovių skaičius: " <<queensRemaining <<endl;

            if(queensRemaining == 0) {
                return true;
            }

            // Bandoma rasti, ar galima padėti likusias karalienes
            if (solveProblemUtil(board, row + 1, boardSize, output)) {
                return true;
            }

            // Jei nepavyko rasti vietos kitoms karalienėms, vykdome BACKTRACK
            board[row][col] = 1; // Sugražiname lentos vertę į 1 (tuščias kvadratėlis lentoje)
            queensRemaining++;
            backtrackDepth--;
        } else if(board[row][col] == 1 && !isSafe(board, row, col, boardSize)) {
            output <<"Kertama langelyje " <<row + 1 <<", " <<col / 2 + 1 <<", likes valdovių skaičius: " <<queensRemaining <<endl;
        }
    }

    // Jei sprendinys nerastas, bandyti pradedant kitoje eilutėje
    return solveProblemUtil(board, row + 1, boardSize, output);
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

void printBoard(int boardSize, ofstream& output) {
    output <<" Y \\/ ";
    for(int i = 0; i < boardSize * 2 - 1; ++i) {
        output <<"-";
    }
    output <<"> X" <<endl;
    for(int i = 0; i < boardSize; ++i) {
        if(boardSize > 10) output <<i + 1 <<" | ";
        else output <<" " <<i + 1 <<" | ";;
        for (int j = 0; j < boardSize - i - 1; ++j) {
            output << " ";
        }

        int counter = 1;
        for (int k = 0; k < 2 * i + 1; ++k) {
            if(k % 2 == 0) {
                output <<counter;
                counter++;
            } else {
                output <<" ";
            }
        }
        output <<endl;
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

void printAnswer(vector<vector<int>>& board, int boardSize, ofstream& output) {
    for(int i = 0; i < boardSize; ++i) {
        for(int j = 0; j < boardSize * 2 - 1; ++j) {
            if(board[i][j] == 0) {
                output << " ";
            } else if(board[i][j] == 1) {
                output << "~";
            } else {
                output << "Q";
            }
        }
        output <<endl;
    }
}

void printInfo(ofstream& output) {
    output <<"Pradiniai duomenys: " <<endl;
    output <<"Testų rinkinys: " <<dataFile <<endl;
    output <<"Valdovių skaičius N =  " <<queenCount <<"." <<endl;
    output <<"Lentos dydis M = " <<boardSize <<"." <<endl <<endl;
    output <<"Lentos išsidėstymas: " <<endl;
    printBoard(boardSize, output);
    output <<endl;
    output <<"Antra dalis - Protokolas: " <<endl;
}