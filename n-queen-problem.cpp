#include <iostream>
#include <vector>
#include <fstream>
#include "script.h"

using namespace std;

#define outputFile "output.txt"

void printBoard(int boardSize, ofstream& output);
void printAnswer(vector<vector<int>>& board, int boardSize, ofstream& output);
void fillBoard(vector<vector<int>>& board, int boardSize);
bool solveProblemUtil(vector<vector<int>>& board, int row, int boardSize, ofstream& output, vector<vector<int>>& coords);
void solveProblem(int queenCount, int boardSize);
bool isSafe(vector<vector<int>>& board, int row, int col, int boardSize);
void printVector(vector<vector<int>>& board, int boardSize, ofstream& output);
void printScript(ofstream& output);
void printInfo(ofstream& output);

int calls = 0;
int queensRemaining = 0;
int queenCount = 0;
int boardSize = 0;
int backtrackDepth = 0;
int rowTracker = 1;

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
    vector<vector<int>> coords(boardSize, vector<int>(boardSize * 2 - 1));
    fillBoard(board, boardSize);
    fillCoords(coords, boardSize);

    ofstream output(outputFile);
    if (!output.is_open()) {
        cerr <<errorOpeningFile <<endl;
        exit(1);
    }

    printScript(output);
    printInfo(output);

    if(solveProblemUtil(board, 0, boardSize, output, coords)) {
        printResultMessage(output);
        printSolutionFound(output, calls);
        printAnswer(board, boardSize, output);
    } else {
        printResultMessage(output);
        printSolutionNotFound(output, calls);
    }
}

void fillBoard(vector<vector<int>>& board, int boardSize) {
    // Sachmatų lentos vektorius užpildomas atitinkamais simboliais, formuojančiais trikampę sachmatų lentą.
    // 0 atvaizduoja tuščią vietą, nepriklausančią sachmatų lentai
    // 1 - laisvą sachmatų lentos vietą, į kurią galimą statyti valdovę.
    
    for(int i = 0; i < boardSize; ++i) {
        int spacer = 0;

        // Lentai nepriklausančios vietos užpildomos nuliais
        for(int j = 0; j < boardSize - i - 1; ++j) {
            board[i][j] = 0;
            spacer++;
        }

        // Pasiekus sachmatų lentos pradžią, kas antras langelis užpildomas 1, taip suformuojant trikampę sachmatų lentą.
        for(int k = 0; k < 2 * i + 1; ++k) {
            if(k % 2 == 0) {
                board[i][spacer + k] = 1;
            } else {
                board[i][spacer + k] = 0;
            }
        }
    }
}   

bool solveProblemUtil(vector<vector<int>>& board, int row, int boardSize, ofstream& output, vector<vector<int>>& coords) {
    // Jeigu liko daugiau karalieniu, negu nepatikrintų eilučių lentoje, sprendinys netinkamas, vykdyti BACKTRACK
    if (queensRemaining > boardSize - row) {
        printNotEnoughRows(output);
        return false;
    }
    
    // Jei eilutės skaičius viršija lentos dydį, sprendinio nėra
    if (row >= boardSize)
        return false;

    // Sprendimo ieškojimas pradedamas nuo viršutinės eilutės tikrinant horizontaliai, nuo kairės į dešinę
    for (int col = 0; col < boardSize * 2 - 1; col++) {
        
        // Tikrinama, ar langelis priklauso sachmatų lentai
        // Jeigu priklauso, užfiksuojame bandymą padėti karalienę bei formuojame protokolo išrašymą
        if(board[row][col] == 1 || board[row][col] == 2) {
            calls++;
            for(int i = 0; i < backtrackDepth; i++) output <<"-";
            printAttemptMessage(output, queenCount - queensRemaining + 1);
        }

        if (board[row][col] == 1 && isSafe(board, row, col, boardSize)) {
            // Langelis tinkamas, padedame karalienę, žymimą simboliu 2
            board[row][col] = 2;
            queensRemaining--;
            backtrackDepth++;

            printPlacementSuccess(output, row, col, queensRemaining, boardSize, coords);
            // printVector(board, boardSize, output);

            if(queensRemaining == 0) {
                return true;
            }

            // Bandoma rasti, ar galima padėti likusias karalienes
            // Tikrinimą pradedame viena eilute žemiau, kadangi ankstesnės eilutės jau patikrintos, o toje pačioje eilutėje kita valdovė bus kertama
            if (solveProblemUtil(board, row + 1, boardSize, output, coords)) {
                return true;
            }

            // Jei nepavyko rasti vietos kitoms karalienėms, vykdome BACKTRACK
            // printBacktracking(output);
            board[row][col] = 1; // Sugražiname lentos vertę į 1 (tuščias kvadratėlis lentoje)
            queensRemaining++;
            backtrackDepth--;
        } else if(board[row][col] == 1 && !isSafe(board, row, col, boardSize)) {
            printPlacementFailure(output, row, col, queensRemaining, boardSize, coords);
            // printVector(board, boardSize, output);
        }
    }

    // Jei sprendinys nerastas, bandome rasti sprendinį valdoves pradedant dėlioti viena eilute žemiau
    rowTracker++;
    return solveProblemUtil(board, row + 1, boardSize, output, coords);
}

bool isSafe(vector<vector<int>>& board, int row, int col, int boardSize) {
    // Tikrinama, ar karalienė yra toje pačioje eilutėje
    for (int i = 0; i < boardSize * 2 - 1; ++i) {
        if (board[row][i] == 2 && i != col) 
            return false;
    }

    // Tikrinama kairioji įstrižainė
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 2)
            return false;
    }

    // Tikrinama dešiniąją įstrižainę
    for (int i = row - 1, j = col + 1; i >= 0 && j < boardSize * 2 - 1; --i, ++j) {
        if (board[i][j] == 2)
            return false;
    }

    return true;
}

void printBoard(int boardSize, ofstream& output) {
    // Funkcija atspausdina sachmatų lentos vaizdavimą, pagal tai, kaip vykdomas sprendinio ieškojimas (iš viršaus į apačią, nuo kairės į dešinę)
    
    // Atspausdinamas koordinačių ašių žymėjimas
    output <<" Y \\/ ";
    for(int i = 0; i < boardSize * 2 - 1; ++i) {
        output <<"-";
    }
    output <<"> X" <<endl;
    for(int i = 0; i < boardSize; ++i) {
        // Spausdinama Y ašis
        if(i >= 9) output <<i + 1 <<" | ";
        else output <<" " <<i + 1 <<" | ";;
        for (int j = 0; j < boardSize - i - 1; ++j) {
            output << " ";
        }

        // Spausdinama sachmatų lentos eilutė, numeruojama nuo kairės į dešinę
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

void printVector(vector<vector<int>>& board, int boardSize, ofstream& output) {
    // Atspausdinamas vektoriaus turinys, naudojamas testavimui
    // Spausdinamas turinys yra neapdorotas (formuojamas simboliais 0, 1 ir 2)
    for(int i = 0; i < boardSize; i++) {
        for(int j = 0; j < boardSize * 2 - 1; j++) {
            output << board[i][j];
        }
        output <<endl;
    }
    output <<endl;
}

void printAnswer(vector<vector<int>>& board, int boardSize, ofstream& output) {
    // Atspausdinamas formatuotas vektoriaus turinys
    // Naudojamas atvaizduoti atrastą problemos sprendinį
    // ~ vaizduoja tuščią vietą priklausančią sachmatų lentai
    // Q atvaizduoja tinkamą valdovės vietą sachmatų lentoje
    
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
    // Funkcija naudojama atspausdinti pradinius duomenis (Valdovių kiekį, lentos dydį, duomenų failo pavadinimą)
    printInfoStart(output, queenCount, boardSize);
    printBoard(boardSize, output);
    output <<endl;
    printProtocolStart(output);
}

