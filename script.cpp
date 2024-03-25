#include <fstream>
#include <vector>
#include <iostream>
#include "script.h"

void printScript(std::ofstream& output) {
    output <<"PIRMA DALIS" <<std::endl;

    output <<"Užduoties sąlyga: Rasti N valdovių išdėstymą M trikampėje lentoje, kad jos viena kitos nekirstų. (Triangular N-queens problem)" <<std::endl <<std::endl;

    output <<"Sprendimo eiga: " <<std::endl;
    output <<"Sprendinio ieškojimas pradedamas nuo viršaus į apačią, valdoves statant pradedant nuo kairės į dešinę." <<std::endl;
    output <<"Prieš padedant valdovę lentoje, patikrinama, ar ji nebūtų kertama kitų, jau pastatytų, valdovių." <<std::endl;
    output <<"Jei valdovė būtų kertama, tikrinamos kitos laisvos lentos vietos toje pačioje eilutėje, eilutę užbaigus einama viena eilute žemyn." <<std::endl;
    output <<"Jei valdovė nebūtų kertama, ji padedama lentoje. Jei liko daugiau nepadėtų valdovių, tikrinimas vyksta toliau, pradedant viena eilute žemiau." <<std::endl;
    output <<"Neradus tinkamos vietos valdovei, gryžtama atgal ir bandoma valdoves išdelioti kitaip (vykdomas BACKTRACKING)." <<std::endl;
    output <<"Suradus tinkamas vietas visoms karalienėms, sprendimas užbaigiamas." <<std::endl <<std::endl;
}

void printInfoStart(std::ofstream& output, int queenCount, int boardSize) {
    output <<"Pradiniai duomenys: " <<std::endl;
    output <<"Testų rinkinys: " <<dataFile <<std::endl;
    output <<"Valdovių skaičius N =  " <<queenCount <<"." <<std::endl;
    output <<"Lentos dydis M = " <<boardSize <<"." <<std::endl <<std::endl;
    output <<"Lentos išsidėstymas: " <<std::endl;
}

void printProtocolStart(std::ofstream& output) {
    output <<"Antra dalis - Protokolas: " <<std::endl;
}

void printAttemptMessage(std::ofstream& output, int queenNumber) {
    output <<"Bandome valdove " <<queenNumber <<". ";
}

void printPlacementSuccess(std::ofstream& output, int row, int col, int remainingQueens, int boardSize, std::vector<std::vector<int>>& coords) {
    output <<"Pastatyta langelyje " <<row + 1 <<", " <<coords[row][col] <<", likes valdovių skaičius: " <<remainingQueens <<std::endl;
}

void printPlacementFailure(std::ofstream& output, int row, int col, int remainingQueens, int boardSize, std::vector<std::vector<int>>& coords) {
    output <<"Kertama langelyje " <<row + 1 <<", " <<coords[row][col] <<", likes valdovių skaičius: " <<remainingQueens <<std::endl;
}

void printResultMessage(std::ofstream& output) {
    output <<std::endl <<"Trečia dalis - Rezultatai: " <<std::endl <<std::endl;
}

void printSolutionFound(std::ofstream& output, int calls) {
    output <<"Sprendimas rastas! Atlikta " <<calls <<" bandymų." <<std::endl <<std::endl;
    output <<"Sprendimas pavaizduotas lentoje: " <<std::endl;
}

void printSolutionNotFound(std::ofstream& output, int calls) {
    output <<"Sprendinio nerasta! Atlikta " <<calls <<" bandymų." <<std::endl;
}

void printNotEnoughRows(std::ofstream& output) {
    output <<"Gryžtama, kadangi karalienių skaičius viršija netikrintų eilučių skaičių." <<std::endl;
}

void printBacktracking(std::ofstream& output) {
    output <<"Gryžtama, kadangi tokiu išdėliojimu sprendimas nerastas." <<std::endl;
}

void fillCoords(std::vector<std::vector<int>>& board, int boardSize) {
    for(int i = 0; i < boardSize; ++i) {
        int counter = 1;
        int spacer = 0;
        // Lentai nepriklausančios vietos užpildomos nuliais
        for(int j = 0; j < boardSize - i - 1; ++j) {
            board[i][j] = 0;
            spacer++;
        }

        // Pasiekus sachmatų lentos pradžią, kas antras langelis užpildomas 1, taip suformuojant trikampę sachmatų lentą.
        for(int k = 0; k < 2 * i + 1; ++k) {
            if(k % 2 == 0) {
                board[i][spacer + k] = counter;
                counter++;
            } else {
                board[i][spacer + k] = 0; 
            }
        }
    }
}