//This program is made by Kaijun Lin.
//It is a game that simulates the life of bacteria.
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
using namespace std;

void update(int r,int c,int num,Grid<char>& grid1,Grid<char>& grid2);
void describe();
void setup(Grid<char>& starting);
int count(int r,int c,Grid<char> currentGrid);
void tick(Grid<char>& nowGrid);
string Pleaseselect(Grid<char>& grid);

const int DELAY = 50;

int main()
{
    describe();
    Grid<char> mycolony;
    setup(mycolony);
    string choice = Pleaseselect(mycolony);
    while(choice != "q" && choice != "Q"){
        choice = Pleaseselect(mycolony);
    }
    cout << "Have a nice Life!" << endl;
    return 0;
}

void describe()  //This function is used to describe the game.
{
    cout<<"Welcome to the CS 106B Game of Life,"<<endl;
    cout<<"a simulation of the lifecycle of a bacteria colony."<<endl;
    cout<<"Cells (X) live and die by the following rules:"<<endl;
    cout<<"- A cell with 1 or fewer neighbors dies."<<endl;
    cout<<"- Locations with 2 neighbors remain stable."<<endl;
    cout<<"- Locations with 3 neighbors will create life."<<endl;
    cout<<"- A cell with 4 or more neighbors dies."<<endl;
    cout<<""<<endl;
}

void update(int r,int c,int num,Grid<char>& grid1,Grid<char>& grid2) //This function determine the next state of a certain square and update it.
{if(num == 2){
        grid2[r][c] = grid2[r][c];
    }
 else if(num == 3){
        grid2[r][c] = 'X';
    }
 else{
        grid2[r][c] = '-';
    }
    grid1[r][c] = grid2[r][c];
}

void setup(Grid<char>& starting)  //This function set up the initial condition.
{                                 //It receives a file name and open the file, tranforming it into a grid.
    ifstream input;
    promptUserForFile(input,"Grid input file name?");
    string line;
    string numrow;
    string numcol;
    int i = 0;
    getline(input,numrow);
    getline(input,numcol);
    int numRow = stringToInteger(numrow);
    int numCol = stringToInteger(numcol);
    starting.resize(numRow,numCol);
    while(getline(input,line)&&i<numRow){
        cout << line << endl;
            for(int j = 0;j < starting.numCols();j++){
                char ch = line[j];
                starting[i][j] = ch;
                }
        i++;
             }
   input.close();
}

int count(int r,int c,Grid<char> currentGrid) //This function finds out whether there is a cell in a certain square of a certain grid.
{                                             //If there is one, it returns 1; If there is none, it returns 0.
    int number = 0;                            //This function helps count the number of cells around a certain square.
    if(currentGrid.inBounds(r,c)){
        if(currentGrid[r][c] == 'X'){//use && here instead of two enclosed if statement
          number = 1;
        }
    }
    return number;
}

void tick(Grid<char>& nowGrid) //This function deals with how the bacteria grow in one generation.
{                              //It receives the current grid state and updates it to the next generation.
    int r;
    int c;
    Grid<char> grid = nowGrid;
    Grid<char> temp = nowGrid;
    for(r = 0;r < grid.numRows()-1;r++){
        for(c = 0;c < grid.numCols();c++){//probably use for loop inside this two for loop to do the sum
            int num = 0;
            num += count(r+1,c+1,grid);
            num += count(r+1,c,grid);
            num += count(r+1,c-1,grid);
            num += count(r,c+1,grid);
            num += count(r,c-1,grid);
            num += count(r-1,c+1,grid);
            num += count(r-1,c,grid);
            num += count(r-1,c-1,grid);
            update(r,c,num,nowGrid,grid);
            grid = temp;
        }
    }
        for(int c = 0;c < grid.numCols();c++){//as mentioned before
            int r = grid.numRows()-1;
            int num = 0;
            num += count(r-1,c+1,grid);
            num += count(r-1,c,grid);
            num += count(r-1,c-1,grid);
            num += count(r,c+1,grid);
            num += count(r,c-1,grid);
            update(r,c,num,nowGrid,grid);
            grid=temp;
    }
    for(int i = 0;i < grid.numRows();i++){
        for(int j = 0;j < grid.numCols();j++){
            cout << nowGrid[i][j];
        }
        cout << "" << endl;
    }
}

string Pleaseselect(Grid<char>& grid)  //This function asks you to select a choice to run the game.
{                                      //It receives a grid and use "tick" function to modify its state.
    string choice=getLine("a)nimate, t)ick, q)uit?");  //It returns a choice to help the main function to determine whether to end the loop.
    if(choice == "a"||choice == "A"){
        int frame=getInteger("How many frames?");
        for(int i = 0;i < frame;i++){
            pause(DELAY);
            clearConsole();
            tick(grid);
        }
    }
    else if(choice == "t"||choice == "T"){
        tick(grid);
    }
    else if(choice == "q"||choice == "Q"){
        cout << "";
    }
    else{
        cout << "Invalid choice; please try again" << endl;
        Pleaseselect(grid);
    }
    return choice;
    }
