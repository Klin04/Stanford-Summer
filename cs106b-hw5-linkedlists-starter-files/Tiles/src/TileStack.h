//This program is made by Kaijun Lin.
//This is the TileStack.h file for the tilestack class.
//Here we define the tilestack class, defining the variables inside the class and different methods.
//We will include it in the TileStack.cpp to help us.
//We add a private variable which is a pointer pointing to the front of the list.

#ifndef _tilestack_h
#define _tilestack_h

#include <iostream>
#include <string>
#include "gobjects.h"
#include "gwindow.h"
#include "TileNode.h"
using namespace std;

class TileStack {
public:
    TileStack();
    ~TileStack();
    void pushTile(int x, int y, int width, int height, string color);
    void drawAll(GWindow& window) const;
    void highlight(int x, int y);
    void raise(int x, int y);
    void remove(int x, int y);
    void clear();

private:
    TileNode* front;
};

#endif
