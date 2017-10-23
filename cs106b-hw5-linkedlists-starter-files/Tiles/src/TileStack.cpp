//This program is made by Kaijun Lin.
//It is going to create a little game
//about different color tiles.
//All the methods are members of tileStack classes.
//Linklists are applied the most in this homework.

#include "TileStack.h"
#include "strlib.h"

//TileStack::TileStack();
//This is the constructor of the class.
//It initializes a new linked list of tilenode structure.
//It assigns the front pointer to point at this empty list.
TileStack::TileStack() {
   this->front = NULL;//initialize
}

//TileStack::~TileStack();
//This is the deconstructor of the class.
//It deletes every object in the linkedlist
//and sets the front pointer to NULL again.
TileStack::~TileStack() {
   clear();
//   while(front != NULL){
//       TileNode* temp = front;
//       front = front->next;
//       delete temp;(
//   }(Armin's improvement)
}

//void TileStack::pushTile(int x, int y, int width, int height, string color);
//This function adds new tileNode structure to the list.
//It takes in the width, height, and the starting point as integers.
//It takes in the color as a stirng.
//It will create a new structure and add it to the front of the current linked list.
//No output.
//O(1)
void TileStack::pushTile(int x, int y, int width, int height, string color) {
   TileNode* temp;
   temp = front;
   TileNode* newTile = new TileNode(x, y, width, height, color);
   front = newTile;
   newTile->next = temp;
}

//void TileStack::drawAll(GWindow& window) const;
//This function takes in a Gwindow object by reference to modify it.
//It draws every object in the current linked list on the Gwindow.
//No output.
//O(N)
void TileStack::drawAll(GWindow& window) const {
   TileNode* temp = front;
   while(temp != NULL){//go through every node and draw them
       temp->draw(window);
       temp = temp->next;
   }
   delete temp;
}

//void TileStack::highlight(int x, int y);
//This function takes in a point by receiving it x and y as integers.
//It will highlight the toppest tileNode that contains the point.
//No output.
//O(N)
void TileStack::highlight(int x, int y) {
    TileNode* temp = front;
    while(temp != NULL){
        if(temp->contains(x, y)){
            temp->color = "yellow";//change color
            break;
        }
        else{
            temp = temp->next;//continue
        }
    }
    temp = NULL;
    delete temp;
}

//void TileStack::raise(int x, int y);
//This function takes in a point by receiving it x and y as integers.
//It will raise the toppest tileNode that contains the point,
//which means the chosen structure will be moved to the beginning of the linked list.
//No output.
//O(N)
void TileStack::raise(int x, int y) {
    //If you click on the top tile multiple times, it raises a tile below it.
    //There should be a check in order to avoid this.(by Armin)
    TileNode* temp = front;
    if(!front->contains(x,y)){
        while(temp != NULL && temp->next != NULL){//going to the node in front of the target
            if(temp->next->contains(x, y)){
                TileNode* curr = temp->next;//curr->target
                temp->next = temp->next->next;//only curr->target
                curr->next = front;//move curr
                front = curr;//move front
                break;//stop
            }
            temp = temp->next;
        }
    }
}

//void TileStack::remove(int x, int y);
//This function takes in a point by receiving it x and y as integers.
//It will remove the toppest ListNode structure.
//It should not modify others.
//No output.
//O(N)
void TileStack::remove(int x, int y) {
    if(front != NULL && front->contains(x, y)){//find the tile
        TileNode* temp = front;
        front = front->next;
        delete temp;
    }
    else if(front != NULL){
        TileNode* temp = front;
        while(temp->next != NULL){//find the tile
            if(temp->next->contains(x, y)){
                TileNode* curr = temp->next;
                temp->next = temp->next->next;
                delete curr;//remove it
                break;
            }
            temp = temp->next;
        }
    }
}

//void TileStack::clear();
//This function clears the linked list.
//Nothing is left in the linked list.
//No output.
void TileStack::clear() {
    while(front != NULL){
        TileNode* temp = front;
        front = front->next;
        delete temp;
    }
}
