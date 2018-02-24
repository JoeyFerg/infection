/**
 * @file Human.cpp
 * @brief The Human class implementation file.
 *
 * @author Joey Ferguson
 * @date March 2016
 */

#include <cstdlib>
#include <iostream>
#include "Human.h"
#include "conio.h"

using namespace std;

/**
 * @brief The Human class constructor.
 * This function initializes the row, col, infected, and board variables.
 *
 * @param initRow the initial human row location.
 * @param initCol the initial human column location.
 * @param initInfected whether the human is initially infected.
 * @param theBoard a pointer to the board (used to ask board whether a proposed move is ok).
 */
Human::Human(int initRow, int initCol, bool initInfected, Board* theBoard) {
    row = initRow;
    col = initCol;
    infected = initInfected;
    board = theBoard;
}

/**
 * @brief The Human class destructor.
 * The Human class destructor does nothing (so far), but is here as a placeholder to remind
 * you that it is a good idea for classes to have destructors, even if you can't think of 
 * work for destructor at this point.
 */
Human::~Human(){
    // nothing to do
}

/**
 * @brief Have the human try to move.
 * To know whether it is ok to move to some position (r,c), ask the board
 * whether the position is ok. E.g., "if( board->tryMove(r,c) ) ..."
 * If the move is ok, then update the human's row and column to reflect the move.
 */
void Human::move() {
    // Generate a +/- 2 row and column delta.
    int rowDelta=rand()%5-2, colDelta=rand()%5-2;

    // Ask the board whether you
    if(board->tryMove(row+rowDelta, col+colDelta)) {
	row+=rowDelta;
	col+=colDelta;
    }
}

/**
 * @brief Get the human's current row/col location.
 * Returns the human's current row/column location via the reference parameters.
 * @param[out] currentRow the human's current row  
 * @param[out] currentCol the human's current column
 */
void Human::getLocation(int& currentRow, int& currentCol) {
    currentRow = row;
    currentCol = col;
}

/**
 * @brief Set the human's row/col location.
 * Sets the human's current row/column location to the parameter values.
 * @param[in] newRow the human's new row location
 * @param[in] newCol the human's new column location
 */
void Human::setLocation(int newRow, int newCol) {
    row=newRow;
    col=newCol;
}

/**
 * @brief Sets this human to be infected.
 * Sets this human object's state to infected.
 */
void Human::setInfected() {
    infected = true;
    dead = false;
    nurse = false;
    healed = false;
}

/**
 * @brief reports whether this human is infected.
 * @return whether this human object is infected.
 */
bool Human::isInfected() {
    return infected;
}

/**
 * @brief Sets this human to be a nurse.
 * Sets this human object's state to nurse.
 */
void Human::setNurse() {
    nurse = true;
    infected = false;
    dead = false;
    healed = false;
}

/**
 * @brief reports whether this human is a nurse.
 * @return whether this human object is a nurse.
 */
bool Human::isNurse() {
    return nurse;
}

/**
 * @brief Sets this human to be dead.
 * Sets this human object's state to dead.
 */
void Human::setDead() {
    dead = true;
    infected = false;
    nurse = false;
    healed = false;
}

/**
 * @brief reports whether this human is dead.
 * @return whether this human object is dead.
 */
bool Human::isDead() {
    return dead;
}

/**
 * @brief Sets this human to be healed.
 * Sets this human object's state to healed.
 */
void Human::setHealed() {
    infected = false;
    healed = true;
    nurse = false;
    dead = false;
}

/**
 * @brief reports whether this human is healed.
 * @return whether this human object is healed.
 */
bool Human::isHealed() {
    return healed;
}

/**
 * @brief Draws the human.
 * Draws the human at the current row/col location on the screen.
 * Remember that the first conio row=1, and first conio col=1.
 */
void Human::draw() {
    cout << conio::gotoRowCol(row+1,col+1);
    if( infected ) {
        cout << conio::bgColor(conio::RED);
        cout << 'X';
    } 
    else if ( nurse ) {
        cout << conio::bgColor(conio::LIGHT_BLUE);
        cout << 'N';
    }
    else if ( dead ) {
        cout << conio::bgColor(conio::GRAY);
        cout << '~';
    }
    else if ( healed ) {
        cout << conio::bgColor(conio::GREEN);
        cout << conio::fgColor(conio::BLACK);
        cout << 'O';
    }
    else {
        cout << conio::bgColor(conio::LIGHT_GREEN);
        cout << conio::fgColor(conio::BLACK);
        cout << 'O';
    }
    cout << conio::resetAll() << flush;
}

