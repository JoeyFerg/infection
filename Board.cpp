/**
 * @file Board.cpp
 * @brief The Board class implementation file.

 * @author Joey Ferguson
 * @date March 2016
 */

#include <iostream>
#include <unistd.h>
#include "Board.h"
#include "conio.h"

/**
 * @brief The Board class constructor, responsible for initializing a Board object.
 * The Board constructor is responsible for initializing all the Board object variables.
 *
 * @param rows The number of rows to make the board.
 * @param cols The number of columns to make the board.
 * @param numberOfHumans The number of humans to place on the board.
 */
Board::Board(int rows, int cols, int numberOfHumans) {
    numHumans = numberOfHumans;
    numRows = rows;
    numCols = cols;
    currentTime = 0;
    numInfected = 0;
    numNurses = 0;
    numDead = 0;
    numHealed = 0;
}

/**
 * @brief The Board class destructor.
 * The Board destructor is responsible for any last-minute cleaning 
 * up that a Board object needs to do before being destroyed. In this case,
 * it needs to return all the memory borrowed for creating the Human objects.
 */
Board::~Board() {
    for(int pos=0; pos<numHumans; ++pos) {
	    delete humans[pos];
    }
}

/**
 * @brief function that runs the end screen
 * Prints out credits after the simulation ends.
 */
void Board::endScreen() {
    cout << conio::clrscr();
    cout << conio::gotoRowCol((numRows/2)-5,(numCols/2)-10);
    cout << "Infection Simulation!";
    cout << conio::gotoRowCol((numRows/2)-3,(numCols/2)-10);
    cout << "  By Joey Ferguson" << endl;
    cout << conio::gotoRowCol((numRows/2)+1,(numCols/2)-20);
    cout << "      Thank you for participating      " << endl;
    cout << conio::gotoRowCol((numRows/2)+2,(numCols/2)-20);
    cout << "      in the infection simulation.     " << endl;
    cout << conio::gotoRowCol((numRows/2)+5,(numCols/2)-20);
    cout << "      Some interesting statistics:     " << endl;
    cout << conio::gotoRowCol((numRows/2)+8,(numCols/2)-20);
    cout << "   Number of humans to start with = " << numHumans << endl;
    cout << conio::gotoRowCol((numRows/2)+10,(numCols/2)-20);
    cout << "      Number of ending nurses = " << numNurses << endl;
    cout << conio::gotoRowCol((numRows/2)+12,(numCols/2)-20);
    cout << "       Number of dead people = " << numDead << endl;
    cout << conio::gotoRowCol((numRows/2)+14,(numCols/2)-20);
    cout << "      Number of healed people = " << numHealed << endl;
    cout << conio::gotoRowCol(numRows,0);
}

/**
 * @brief function that runs the simulation
 * Creates human objects, infects one human, makes one human a nurse, then runs simulation until all are infected.
 */
void Board::run() {
    int row, col;

    // Creates 'Human' objects and sets the array pointers to point at them.
    for(int pos=0; pos<numHumans; ++pos) {
    	row = pos%numRows;       // row will be in range(0, numRows-1)
    	col = rand()%numCols;  // col will be in range(0, numCols-1)
    	// Create and initialize another Human. 
    	// Parameters are row on board, col on board, initially infected,
    	// and a pointer to this board object ('this').
    	humans[pos] = new Human(row, col, false, this); 
    }

    // Infect a random human in the range 0 to numHumans-1
    humans[rand()%numHumans]->setInfected();

    // Makes one human a nurse in the range 0 to numHumans-1
    humans[rand()%numHumans]->setNurse();

    for(currentTime=0; !allHealed(); ++currentTime) {
    	
        // Clear screen before every new time unit
    	cout << conio::clrscr() << flush;

    	// Tell each human to try moving
    	for(int pos=0; pos<numHumans; ++pos) {
            if (!humans[pos]->isDead()) {
    	       humans[pos]->move();
            }
    	}

    	// Deal with infection propagation.
    	processInfection();

    	// Tell each human to draw itself on board with updated infection status
    	for(int pos=0; pos<numHumans; ++pos) {
    	    humans[pos]->draw();
    	}

    	// Print statistics.
    	cout << conio::gotoRowCol(numRows+3, 1); 
        cout << "Simulation Time: " << conio::fgColor(conio::YELLOW) << currentTime << conio::resetAll() << endl;
        cout << "Total " << conio::bgColor(conio::LIGHT_GREEN) << conio::fgColor(conio::BLACK) << "Humans" << conio::resetAll() << ": " << numHumans << endl;
        cout << "Total " << conio::bgColor(conio::RED) << "Infected" << conio::resetAll() << ": " << numInfected  << endl;
        cout << "Total " << conio::bgColor(conio::LIGHT_BLUE) << "Nurses" << conio::resetAll() << ": " << numNurses << endl;
        cout << "Total " << conio::bgColor(conio::GRAY) << "Dead" << conio::resetAll() << ": " << numDead << endl;
        cout << "Total " << conio::bgColor(conio::GREEN) << "Healed" << conio::resetAll() << " (Now Immune): " << numHealed  << endl << flush;

    	// Sleep specified microseconds
    	sleep(1);
    }

    // Position the cursor so prompt shows up on its own line
    cout << endl;
}

/**
 * @brief Determines whether or not all humans are healed.
 * @return If even one human is infected, returns false. Otherwise, returns true.
 */
bool Board::allHealed() {
    for(int i=0; i<numHumans; ++i) {
	    if(humans[i]->isInfected()) {
            return false;
        }
    }
    return true;
}

/**
 * @brief The function that handles one infection cycle to determine what new infections
 *        are present.
 * For each pair of adjacent humans in the simulation, processInfection() makes sure that if 
 * one is infected, the other becomes infected as well.
 */
void Board::processInfection() {
    for( int i=0; i<numHumans; ++i ) {
        for( int j=i+1; j<numHumans; ++j ) {
    	    if( isNextTo(humans[i], humans[j]) ){
                // Code that sets healthy people to infected.
    	        if (humans[i]->isInfected() && !humans[j]->isInfected() && !humans[j]->isNurse() && !humans[j]->isDead() && !humans[j]->isHealed()) {
                    int randNum = rand() % 3;
                    if (randNum == 0 || randNum == 1) {
    		            humans[j]->setInfected();
                    }
    		    }
                if (humans[j]->isInfected() && !humans[i]->isInfected() && !humans[i]->isNurse() && !humans[i]->isDead() && !humans[i]->isHealed()) {
    		        int randNum = rand() % 3;
                    if (randNum == 0 || randNum == 1) {
                        humans[i]->setInfected();
                    }
    		    }

                // Code that sets healthy people to nurses.
                if (humans[j]->isNurse() && !humans[i]->isInfected() && !humans[i]->isHealed() && !humans[i]->isNurse() && !humans[i]->isDead()) {
                    int randNum = rand() % 12;
                    if (randNum == 1) {
                        humans[i]->setNurse();
                    }
                }
                if (humans[i]->isNurse() && !humans[j]->isInfected() && !humans[j]->isHealed() && !humans[j]->isNurse() && !humans[j]->isDead()) {
                    int randNum = rand() % 12;
                    if (randNum == 1) {
                        humans[j]->setNurse();
                    }
                }

                // Code that sets infected people to healed, and a chance of them becoming a nurse as well.
                if (humans[i]->isInfected() && humans[j]->isNurse()) {
                    int randNum = rand() % 3;
                    if (randNum == 0 || randNum == 1) {
                        humans[i]->setHealed();
                    }
                    if (randNum == 2) {
                        humans[i]->setNurse();
                    } 
                }
                if (humans[j]->isInfected() && humans[i]->isNurse()) {
                    int randNum = rand() % 3;
                    if (randNum == 0 || randNum == 1) {
                        humans[j]->setHealed();
                    }
                    if (randNum == 2) {
                        humans[j]->setNurse();
                    }  
                }

                // Code that determines whether an infected person dies or not.
                if (humans[i]->isInfected()) {
                    int randNum = rand() % 100;
                    if (randNum == 1) {
                        humans[i]->setDead();
                    }
                }
    	    }
	    }
    }

    // Reset the board 'numInfected' count and recount how many are infected.
    numInfected = 0;
    for( int i=0; i<numHumans; ++i ) {
        if( humans[i]->isInfected() ) {
            numInfected++;
        }
    }

    // Reset the board 'numNurses' count and recount how many are nurses.
    numNurses = 0;
    for( int i=0; i<numHumans; ++i ) {
        if( humans[i]->isNurse() ) {
            numNurses++;
        }
    }

    // Reset the board 'numDead' count and recount how many are dead.
    numDead = 0;
    for( int i=0; i<numHumans; ++i ) {
        if( humans[i]->isDead() ) {
            numDead++;
        }
    }

    // Reset the board 'numHealed' count and recount how many are healed.
    numHealed = 0;
    for( int i=0; i<numHumans; ++i ) {
        if( humans[i]->isHealed() ) {
            numHealed++;
        }
    }
}

/**
 * @brief The function that determines whether a particular move can happen.
 *        If the move would go off the board, or land on the same position as another
 *        human, the function returns false (do not move). Otherwise, it returns true (ok to proceed).
 * @param[in] row the row the human wishes to move to.
 * @param[in] col the col the human wishes to move to.
 * @return Whether the human calling this function may move to the specified row and column.
 */
bool Board::tryMove(int row, int col) {
    int tryRow, tryCol=-1;

    // If off board, the move is not permitted
    if( row<0 || row>=numRows || col<0 || col>=numCols ) return false;

    // Else if another human is on the same location, the move is not permitted
    for(int i=0; i<numHumans; ++i) {
        humans[i]->getLocation(tryRow, tryCol);
	    if( row==tryRow && col==tryCol ) {
            return false;
        }
    }

    // No problems, so the move is permitted
    return true;
}

/**
 * @brief The function that determines whether two humans are on adjacent squares.
 * @param h1 pointer to first human object.
 * @param h2 pointer to second human object.
 * @return Whether or not h1 and h2 are on adjacent squares.
 */
bool Board::isNextTo(Human *h1, Human* h2) {
    // Get human location information
    int h1Row, h1Col;
    h1->getLocation(h1Row, h1Col);
    int h2Row, h2Col;
    h2->getLocation(h2Row, h2Col);

    // Return whether h1 and h2 are on adjacent squares in any direction 
    // (horizontally, vertically, diagonally).
    return abs(h1Row-h2Row)<=1 && abs(h1Col-h2Col)<=1;
}

