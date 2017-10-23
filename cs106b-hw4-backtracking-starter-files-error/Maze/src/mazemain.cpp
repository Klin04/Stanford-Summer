/*
 * CS 106B Maze Solver
 * This instructor-provided file contains the main program and user interface
 * for running your anagram solver.
 *
 * Please DO NOT MODIFY this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: 2016/07/12 Tue
 * Author : Marty Stepp
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include "Maze.h"
using namespace std;

// constant for default dictionary file name to use if the user leaves it blank
static const string MAZE_FILE_DEFAULT = "maze1.txt";
static const int ANIMATION_DELAY = 400;

// function prototype declarations
bool escapeMaze(Maze& maze, int row, int col);   // written by you, in mazesolver.cpp
string promptForMazeFile();
bool tryToEscape(Maze& maze);

int main() {
    cout << "Welcome to the CS 106B Maze Solver!" << endl;
    bool animation = getYesOrNo("Do you want animation? (Y/N)");

    // read dictionary of words from a file
    string mazeFile = promptForMazeFile();
    cout << "Reading maze ..." << endl;
    string fileText = readEntireFile(mazeFile);
    Maze maze(fileText);
    if (animation) {
        maze.setDelay(ANIMATION_DELAY);
    }
    cout << maze << endl;

    while (tryToEscape(maze)) {
        maze.clearMarks();
    }

    cout << "Have a nice day." << endl;
    return 0;
}

/*
 * Repeatedly prompts the user until they type a dictionary file name for
 * a file that exists in the res/ folder, then returns that file name.
 * Or if the user types a blank line, the default file is returned.
 */
string promptForMazeFile() {
    string mazeFile;
    while (mazeFile.empty() || !fileExists(mazeFile)) {
        mazeFile = trim(getLine("Maze file name (blank for "
                                             + MAZE_FILE_DEFAULT + ")? "));
        if (mazeFile.empty()) {
            mazeFile = MAZE_FILE_DEFAULT;
        } else if (!stringContains(mazeFile, ".")) {
            mazeFile += ".txt";   // default .txt extension
        }
    }
    return mazeFile;
}

/*
 * Performs one anagram search, prompting for the phrase and max words,
 * and then printing all anagrams along with a count of how many were printed.
 * Returns true if the user wants to keep going or false to quit.
 */
bool tryToEscape(Maze& maze) {
    // prompt for starting location to escape from
    cout << endl;
    int row = getInteger("Start row?");
    int col = getInteger("Start col?");

    // call student's function to try to escape the maze
    bool result = escapeMaze(maze, row, col);

    if (!maze.isAnimated()) {
        cout << maze << endl;
    }

    if (result) {
        cout << "You escaped!" << endl;
    } else {
        cout << "No path was found. :-(" << endl;
    }

    return getYesOrNo("Try again? (Y/N)");
}
