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

#include "TileNode.h"
#include <sstream>
using namespace std;

TileNode::TileNode(int x, int y, int width, int height,
         string color, TileNode* next) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
    this->next = next;
}

bool TileNode::contains(int x, int y) const {
    return this->x <= x && x < this->x + this->width &&
            this->y <= y && y < this->y + this->height;
}

void TileNode::draw(GWindow& window) const {
    window.setColor(color);
    GRect* rect = new GRect(x, y, width, height);
    rect->setColor(0x0);   // black
    rect->setFillColor(color);
    rect->setFilled(true);
    window.add(rect);
    rect->sendToBack();
}

string TileNode::toString() const {
    ostringstream out;
    out << *this;
    return out.str();
}

ostream& operator <<(ostream& out, const TileNode& node) {
    return out << "Tile@0x" << &node
            << "{x=" << node.x << ",y=" << node.y
            << ",w=" << node.width << ",h=" << node.height
            << ",color=\"" << node.color << "\""
            << ",next=0x" << node.next << "}";
}
