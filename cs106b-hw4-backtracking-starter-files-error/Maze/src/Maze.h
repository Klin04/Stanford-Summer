/*
 * CS 106B, Marty Stepp
 * This instructor-provided file contains the declaration of the maze class.
 * See Maze.cpp for implementation of each member.
 *
 * Please DO NOT MODIFY this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: 2016/07/12 Tue
 * Author : Marty Stepp
 */

#ifndef _maze_h
#define _maze_h

#include <iostream>
#include <string>
#include "grid.h"
using namespace std;

class Maze {
public:
    /*
     * Constructs a maze to read data from the given text.
     * Throws a string exception if the maze data format is invalid.
     */
    Maze(string mazeText);

    /*
     * Sets all squares of the maze to be unmarked.
     */
    void clearMarks();

    /*
     * Returns true if the given row/column is within the bounds of the maze.
     * This will be true for indexes (0, 0) through (rows - 1, cols - 1).
     */
    bool inBounds(int row, int col) const;

    /*
     * Returns true if the maze uses an animation delay (as per setDelay).
     * Initially a maze does not use animation.
     */
    bool isAnimated() const;

    /*
     * Returns true if the given row/column has been "marked" by the user.
     * Throws a string exception if the row or column is out of bounds of the maze.
     */
    bool isMarked(int row, int col) const;

    /*
     * Returns true if the given row/column is an unmarked open square where
     * the maze player could move.
     * Throws a string exception if the row or column is out of bounds of the maze.
     */
    bool isOpen(int row, int col) const;

    /*
     * Returns true if the given row/column contains a wall that cannot be passed.
     * Throws a string exception if the row or column is out of bounds of the maze.
     */
    bool isWall(int row, int col) const;

    /*
     * Places a mark at the given row/col position, if it is an unmarked open square.
     * Throws a string exception if the row or column is out of bounds of the maze,
     * or if the square is not an unmarked open square.
     */
    void mark(int row, int col);

    /*
     * Returns the number of columns in the maze.
     */
    int numCols() const;
    int width() const;

    /*
     * Returns the number of rows in the maze.
     */
    int numRows() const;
    int height() const;

    /*
     * Sets the maze to have an animation delay of the given number of milliseconds.
     * If the value passed is greater than 0, prints the maze and pauses that
     * many milliseconds after any call to place or remove is made.
     * The default initial state of the maze is to have a delay of 0 ms.
     */
    void setDelay(int ms);

    /*
     * Returns a 2-dimensional string representation of the maze.
     */
    string toString() const;

    /*
     * Un-places a queen from the given row/col position, if it is a marked open square.
     * If there wasn't a queen there, has no effect.
     * Throws a string exception if the row or column is out of bounds of the maze,
     * or if the square is not a marked open square.
     */
    void unmark(int row, int col);

    friend ostream& operator <<(ostream& out, const Maze& maze);

private:
    // types of characters that can appear in a maze
    enum VALID_CHARS { WALL = 'X', OPEN = ' ', MARK = '.' };

    // private member variables
    Grid<char> m_grid;   // 2d grid representing the maze
    int m_delayMS;       // delay for animation (default 0=no animation)

    // private member functions
    void checkDelay() const;   // checks and animates if necessary
    void checkIndex(int row, int col) const;   // throws an exception if row/col out of bounds
};

#endif
