//This program is made by Kaijun Lin.
//It will show how a tiny guy walks out the maze given.
//I will use backtracking technique to solve this problem.

#include "Maze.h"

//bool escapeMaze(Maze& maze, int row, int col);
//This function takes in a Maze object by reference
//and the starting row and column indicated by two integers.
//It returns true when there is a way to go out.
//It returns false when the man cannot find a way out.
bool escapeMaze(Maze& maze, int row, int col) {
    if(!maze.inBounds(row, col)){//base case
        return true;
    }
    else if(maze.isOpen(row, col)){//recursive case
        maze.mark(row, col);
//        bool one = escapeMaze(maze, row + 1, col);
//        if(one == true){//each of the four function returns true
//            return true;//means we have a path
//        }               //All the returns here try to end the function.

//        bool two = escapeMaze(maze, row, col + 1);
//        if(two == true){
//            return true;
//        }
//        bool three = escapeMaze(maze, row, col - 1);
//        if(three == true){
//            return true;
//        }
//        bool four = escapeMaze(maze, row - 1, col);
//        if(four == true){
//            return true;
//        }
        if(escapeMaze(maze, row + 1, col) || escapeMaze(maze, row, col + 1) || escapeMaze(maze, row, col - 1) || escapeMaze(maze, row - 1, col)){
            return true;
        }
        maze.unmark(row, col);//If there are no if statements above
        }                     //When one function returns
    return false;             //All paths will be unmarked(sad face)
}

