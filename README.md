# Triangular N-queens problem

A triangular N-queens problem solver built with C++ for a university project.

## Description

This program finds the first possible solution to the N-queens problem on a triangular chess board. The solution to this problem is the first possible distribution of N number of queens on an M size triangular chess board, where none of the queens are attacking eachother.

This program utilizes backtracking to find the first possible solution. The result gets printed to an external text file, "output.txt" by default, which can be modified inside of script.h.

## Usage

Provide the name of your data file inside of script.h. By default, the program reads data from "data.txt"

Currently, the data file structure is as follows:

```
Valdovių skaičius N = #
Lentos dydis M = #
```

where N represents the amount of queens and M represents the size of the board. Replace the # with the desired numbers, both of which are limited to 15. The text can be changed, as long as it remains as two words.

Then, open a terminal window and navigate to the folder containing the program files. Enter "make run" to launch the program. All possible commands:
* make build - This will build an executable file for the program
* make run - This will re-build an executable and also launch it
* make clean - This will clean any existing object (.o) files ("make cleanLin" does the same on Linux)


## Notes

The text output of the program is written in Lithuanian. All of the text the program outputs can be edited inside of script.h and script.cpp.

Comments inside of the program are currently written in Lithuanian.
