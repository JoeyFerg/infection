/**
 * @file main.cpp
 * @brief Contains the main function that starts the infection simulation.
 *
 * @author Joey Ferguson
 * @date March 2016
 **/

#include <iostream>
#include "Board.h"

using namespace std;

/**
 * @fn main()
 * @brief main function that starts the simulation running
 * The main function creates a board object that is 50 rows, 100 columns, 100 humans
 * and starts the simulation running by calling the board's run function.
 **/
 
int main() {
    Board board(50, 100, 100);
    board.run();
    board.endScreen();

    return 0;
}
