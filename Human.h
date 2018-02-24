/**
 * @file Human.h
 * @brief The Human class declaration file.
 *
 * @author Joey Ferguson
 * @date March 2016
 */

#include "Board.h"

#ifndef HUMAN_H
#define HUMAN_H

using namespace std;

/**
 * @class Human
 * @brief The Human class declaration.
 */
class Human {
    public:
        Human(int initRow, int initCol, bool initInfected, Board* thisBoard);
	virtual ~Human();
	virtual void move();
	virtual void draw();

	// "Setters" and "getters"
	virtual void getLocation(int& row, int& col);
	virtual void setLocation(int row, int col);
	virtual void setInfected();
	virtual bool isInfected();
	virtual void setNurse();
	virtual bool isNurse();
	virtual void setDead();
	virtual bool isDead();
	virtual void setHealed();
	virtual bool isHealed();

    protected:
    bool infected;		// Tracks whether or not this human is infected.
    bool nurse;			// Tracks whether or not this human is a nurse.
    bool dead;			// Tracks whether or not this human is dead.
    bool healed;    	// Tracks whether or not this human is healed.
	int row, col;      	// The row and column where this human is on the board.

	Board *board;      	// Pointer to the board so the human can ask the board whether
	                   	// the human can move to a given location on the board.
};

#endif // HUMAN_H
