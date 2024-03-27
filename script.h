#ifndef SCRIPT_H
#define SCRIPT_H

#include <fstream>
#include <vector>
#include <iostream>

#define dataFile "data.txt"
#define outputFile "output.txt"

#define errorOpeningFile "Klaida atidarant failą. Programa užsidaro."

void printScript(std::ofstream& output);
void printInfoStart(std::ofstream& output, int queenCount, int boardSize);
void printProtocolStart(std::ofstream& output);
void printAttemptMessage(std::ofstream& output, int queenNumber);
void printPlacementSuccess(std::ofstream& output, int row, int col, int remainingQueens, int boardSize, std::vector<std::vector<int>>& coords);
void printPlacementFailure(std::ofstream& output, int row, int col, int remainingQueens, int boardSize, std::vector<std::vector<int>>& coords);
void printResultMessage(std::ofstream& output);
void printSolutionFound(std::ofstream& output, int calls);
void printSolutionNotFound(std::ofstream& output, int calls);
void printSolutionNotPossible(std::ofstream& output);
void printNotEnoughRows(std::ofstream& output);
void printBacktracking(std::ofstream& output);
void printNewLine(std::ofstream& output);
void printResultMessageNoSolution(std::ofstream& output);
void printTooManyQueens(std::ofstream& output);
void printBoardTooBig(std::ofstream& output);
void printDoneMessage(int calls);
void fillCoords(std::vector<std::vector<int>>& board, int boardSize);

#endif 