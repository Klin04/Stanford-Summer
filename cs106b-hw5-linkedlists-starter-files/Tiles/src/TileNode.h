/*
 * CS 106B Tiles
 * This file contains the declaration of the TileNode structure.
 *
 * Please DO NOT MODIFY this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: 2016/07/20 Wed
 * Author : Marty Stepp
 */

#ifndef _tilenode_h
#define _tilenode_h

#include <iostream>
#include <string>
#include "gobjects.h"
#include "gwindow.h"
using namespace std;

/*
 * Each Tile structure represents a single rectangular tile in the simulation.
 * A tile knows its position, size, and color.
 * It contains members that can draw itself, tell you whether it touches a
 * given x/y pixel, and print it on the console for debugging.
 */
struct TileNode {
    int x;            // (x, y) position of tile's top-left corner
    int y;
    int width;        // tile's dimensions in pixels
    int height;
    string color;     // tile's color as a hex RRGGBB string like "#ff00ff" for purple

    TileNode* next;   // next tile node pointer, if any

    /*
     * Constructor initializes all members to have the given values,
     * or zero-equivalent values if omitted.
     */
    TileNode(int x = 0, int y = 0, int width = 0, int height = 0,
             string color = "", TileNode* next = NULL);

    /* Returns true if the given x/y coordinate is found inside the tile. */
    bool contains(int x, int y) const;

    /* Draws the tile on the given window. */
    void draw(GWindow& window) const;

    /* Returns a string representation of the tile in the format of operator <<. */
    string toString() const;

    /*
     * Outputs the given tile to the given output stream (e.g. cout) in the same
     * format as returned by its toString member function.
     * The tile's memory address, data, and next pointer are all printed.
     *
     * If you have a non-NULL pointer TileNode* p, you can print the node by writing:
     * cout << *p << endl;
     */
    friend ostream& operator <<(ostream& out, const TileNode& node);
};

#endif
