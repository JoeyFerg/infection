#ifndef BOARD_H
#define BOARD_H

/**
 * @file Board.h
 * @brief The Board class declaration file.
 *
 * @author Joey Ferguson
 * @date March 2016
 */

class Board;

#include "Human.h"

using namespace std;

/**
 * @class Board
 * @brief The Board class declaration.
 */
class Board {
  public:
    Board(int numRows, int numCols, int numHumans);     // Board class constructor
    ~Board();                                           // Board class destructor
    void run();                                         // Main function that runs the simulation
    void endScreen();                                   // Function that displays the initial screen when you run the simulation
    bool tryMove(int row, int col);                     // Function that lets human know whether move is ok
    static const int MAX_HUMAN_COUNT = 100;             // Maximum humans simulation can handle

  protected:
    void processInfection();                // Go through and process infection status
    bool allHealed();                       // Tells whether all humans are infected
    bool isNextTo(Human* h1, Human* h2);    // Tells whether one human is next to another

    Human* humans[MAX_HUMAN_COUNT];
    int numHumans;                          // Number of humans
    int numInfected;                        // Number of humans infected
    int numNurses;                          // Number of nurses
    int numDead;                            // Number of infected people that died
    int numHealed;                          // Number of people that got healed by nurses
    int currentTime;                        // Current time in simulation
    int numRows;                            // Number of rows in board
    int numCols;                            // Number of cols in board
    int uSleepTime;                         // Number of microseconds to sleep between updates
};

#endif //#ifndef BOARD_H
