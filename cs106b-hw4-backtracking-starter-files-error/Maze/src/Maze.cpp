/*
 * CS 106B, Marty Stepp
 * This instructor-provided file contains the implementation of the Maze class.
 * See Maze.h for documentation of each member.
 *
 * Please DO NOT MODIFY this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: 2016/07/12 Tue
 * Author : Marty Stepp
 */

#include "Maze.h"
#include <iomanip>
#include <sstream>
#include "console.h"
#include "strlib.h"

Maze::Maze(string mazeText) {
    m_delayMS = 0;

    // read data from file; format is
    // # ROWS r
    // # COLS c
    // (r) lines of (c) chars each
    istringstream input(mazeText);
    string line;
    if (!getline(input, line) || !stringIsInteger(trim(line))) {
        throw "missing # of rows at start of file";
    }
    int rows = stringToInteger(line);
    if (!getline(input, line) || !stringIsInteger(trim(line))) {
        throw "missing # of cols at start of file";
    }
    int cols = stringToInteger(line);
    if (rows < 1 || cols < 1) {
        throw "illegal maze size";
    }
    m_grid.resize(rows, cols);

    // read each line
    for (int row = 0; row < rows; row++) {
        if (!getline(input, line)) {
            throw "missing data for row #" + integerToString(row);
        }

        // repair line length as needed
        line = trim(line);
        if ((int) line.length() > cols) {
            throw "wrong number of characters for row #" + integerToString(row);
        } else {
            // line might end with spaces that were stripped when saving;
            // re-add them if necessary
            while ((int) line.length() < cols) {
                line += " ";
            }
        }

        // store line's contents into grid
        for (int col = 0; col < cols; col++) {
            char ch = line[col];
            if (ch != WALL && ch != OPEN) {
                throw "invalid character in row #"
                        + integerToString(row) + ", col #"
                        + integerToString(col) + ": '" + ch
                        + "' (ASCII " + integerToString(ch) + ")";
            }
            m_grid[row][col] = ch;
        }
    }
}

void Maze::clearMarks() {
    for (int row = 0; row < m_grid.numRows(); row++) {
        for (int col = 0; col < m_grid.numCols(); col++) {
            if (isMarked(row, col)) {
                unmark(row, col);
            }
        }
    }
}

bool Maze::inBounds(int row, int col) const {
    return m_grid.inBounds(row, col);
}

bool Maze::isAnimated() const {
    return m_delayMS > 0;
}

bool Maze::isMarked(int row, int col) const {
    checkIndex(row, col);
    return m_grid[row][col] == MARK;
}

bool Maze::isOpen(int row, int col) const {
    checkIndex(row, col);
    return m_grid[row][col] == OPEN;
}

bool Maze::isWall(int row, int col) const {
    checkIndex(row, col);
    return m_grid[row][col] == WALL;
}

void Maze::mark(int row, int col) {
    checkIndex(row, col);
    checkDelay();
    if (!isOpen(row, col)) {
        throw "square at row #" + integerToString(row) + ", col #"
                + integerToString(col) + " is not an unmarked open square:\n"
                + toString();
    }
    m_grid[row][col] = MARK;
}

int Maze::numCols() const {
    return m_grid.numCols();
}
int Maze::width() const {
    return m_grid.numCols();
}

int Maze::numRows() const {
    return m_grid.numRows();
}
int Maze::height() const {
    return m_grid.numRows();
}

void Maze::setDelay(int ms) {
    if (ms < 0) {
        throw "Illegal delay MS: " + integerToString(ms);
    }
    m_delayMS = ms;
}

string Maze::toString() const {
    ostringstream out;
    out << *this;
    return out.str();
}

void Maze::unmark(int row, int col) {
    checkIndex(row, col);
    checkDelay();
    if (!isMarked(row, col)) {
        throw "square at row #" + integerToString(row) + ", col #"
                + integerToString(col) + " is not a marked square:\n"
                + toString();
    }
    m_grid[row][col] = OPEN;
}

void Maze::checkDelay() const {
    if (m_delayMS > 0) {
        clearConsole();
        cout << toString() << endl;
        cout.flush();
        pause(m_delayMS);
    }
}

void Maze::checkIndex(int row, int col) const {
    if (!inBounds(row, col)) {
        throw "illegal index: row #" + integerToString(row)
                + ", col #" + integerToString(col) + ":\n"
                + toString();
    }
}

ostream& operator <<(ostream& out, const Maze& maze) {
    // header line with column numbers
    out << "   ";
    for (int c = 0; c < maze.numCols(); c++) {
        out << c % 10;
    }
    out << endl;

    for (int r = 0; r < maze.numRows(); r++) {
        // header column with row numbers
        out << setw(2) << right << r << " ";

        // chars on each row
        for (int c = 0; c < maze.numCols(); c++) {
            out << maze.m_grid[r][c];
        }
        if (r != maze.numRows() - 1) {
            out << endl;
        }
    }
    return out;
}
