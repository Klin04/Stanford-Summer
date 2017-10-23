//This program is made by Kaijun Lin.
//It creates a queue of elements which have priority.
//When dequeued, the queue outputs high priority elements first.
//Linked list will be implemented in the program.
//The higher priority is, the smaller the integer priority is.

#include "LinkedPriorityQueue.h"

//LinkedPriorityQueue::LinkedPriorityQueue();
//This is the constructor of the class.
//It initializes a new PQNode structure and assigns front to point to it.
//No input and output.
//O(1)
LinkedPriorityQueue::LinkedPriorityQueue() {
    front = NULL;//initialization
}

//LinkedPriorityQueue::~LinkedPriorityQueue();
//This is the destructor of the class.
//It clears every ListNode object in the queue.
//It also free the allocated memory of the linked list.
//No input and output.
//O(N)
LinkedPriorityQueue::~LinkedPriorityQueue() {
    PQNode* temp;
    while(front != NULL){
        temp = front;
        front = front->next;
        delete temp;
    }
}

//void LinkedPriorityQueue::changePriority(string value, int newPriority);
//This function modifies the priority of the given string value.
//It takes in the string to modify and its new priority.
//It will make teh string more urgent.
//If the string is more urgent or not existing, it will throw an exception.
//No output.
//O(N)
void LinkedPriorityQueue::changePriority(string value, int newPriority) {
    if(front == NULL){
        throw "No element so the value doesn't exist!";
    }
    if(front->value == value){
        if(front->priority >= newPriority){
            front->priority = newPriority;
        }
        else{
            throw "priority is more urgent";
        }
    }
    else{
        PQNode* temp = front;
        PQNode* curr = NULL;//if found, curr will not be NULL, used to check
        while(temp->next != NULL){
            if(temp->next->value == value){//find value
                if(temp->next->priority < newPriority){
                    throw "priority is more urgent";
                }
                else{//assign curr to point to the node and make sure no other pointer is pointing
                    curr = temp->next;
                    curr->priority = newPriority;
                    temp->next = temp->next->next;
                    curr->next = NULL;
                    break;
                }
            }
            else{
                temp = temp->next;
            }
        }
        if(curr == NULL){
            throw "value not found";
        }
        else if((*front) > (*curr)){//exam the front node
            curr->next = front;
            front = curr;
        }
        else{
            PQNode* help = front;
            while(help->next != NULL && (*help->next) < (*curr)){//find out the right place to insert
                help = help->next;
            }
                PQNode* now = help->next;//insert the changed Node
                help->next = curr;
                curr->next = now;
                return; //stop after inserting
        }
        //PQNode* curr = temp->next;
        //PQNode* help = temp->next->next;
        //temp->next = help;
        //curr->next = NULL;
        //enqueue(value, newPriority);
        //delete curr;
        //return;
        //method 2 that calls the enqueue function after finding the target
    }
}


//void LinkedPriorityQueue::clear();
//This function removes all the PQNode structure in the linked list.
//NO input and output.
//O(N)
void LinkedPriorityQueue::clear() {
    while(front != NULL){
        PQNode* temp = front;
        front = front->next;
        delete temp;
    }
}

//string LinkedPriorityQueue::dequeue();
//This function removes and returns the string value which has the highest priority,
//which means the int priority in this structure is the smallest.
//If there are many, it returns the toppest one, which is sorted due to ASCII code, and removes it.
//It has no input.
//O(1)
string LinkedPriorityQueue::dequeue() {
    string target = "";
    if(front == NULL){//NULL
        throw "NO element!";
    }
    else{//Not NULL, get the first one out
        PQNode* temp = front;
        front = front->next;
        target = temp->value;
        delete temp;
        return target;
    }
    return target;
}

//void LinkedPriorityQueue::enqueue(string value, int priority);
//This function adds new element according to the given order.
//It takes in a string and a priority.
//No output.
//O(N)
void LinkedPriorityQueue::enqueue(string value, int priority) {
    PQNode* newNode = new PQNode(value, priority);
    if(front == NULL){//No element.
        front = newNode;
    }
    else if((*front) > (*newNode)){
        newNode->next = front;
        front = newNode;
    }
    else{
        PQNode* temp = front;
        while(temp->next != NULL && (*temp->next) < (*newNode)){//find out the spot
            temp = temp->next;
        }
        if(temp->next == NULL){
            temp->next = newNode;
        }
        else{//not NULL
            PQNode* curr = temp->next;
            temp->next = newNode;
            newNode->next = curr;
        }
    }
}

//bool LinkedPriorityQueue::isEmpty() const;
//This function tests if there is no element in the linked list.
//It returns true if the list is empty, false if there are elements inside.
//No input.
//O(1)
bool LinkedPriorityQueue::isEmpty() const {
    if(front == NULL){
        return true;
    }
    return false;
}

//string LinkedPriorityQueue::peek() const；
//This function returns the string value which has the highest priority.
//But it did not modify the list.
//It throws an exception if there is no element in the linked list.
//NO input.
//O(N)
string LinkedPriorityQueue::peek() const {
    if(front == NULL){
        throw "No elements!";
    }
    else{//find out the max priority one and assign its string value to the output string
        int maxPriority = front->priority;
        string highest = front->value;
        PQNode* temp = front->next;
        while(temp != NULL){//go through every node
            if(temp->priority < maxPriority){
                maxPriority = temp->priority;
                highest = temp->value;
            }
            temp = temp->next;
        }
        return highest;
    }
    return "";
}

//int LinkedPriorityQueue::peekPriority() const;
//This function returns the highest priority, which is and integer.
//It throws an exception if there is no element in the list.
//No input.
//O(N)
int LinkedPriorityQueue::peekPriority() const {
    if(front == NULL){
        throw "No elements!";
    }
    else{
        int maxPriority = front->priority;//only need to find out the max priority
        PQNode* temp = front;
        while(temp != NULL){//go through every node
            if(temp->priority < maxPriority){
                maxPriority = temp->priority;
            }
            temp = temp->next;
        }
        return maxPriority;
    }
    return 0;
}

//int LinkedPriorityQueue::size() const;
//This function returns the total number of elements in the linked list.
//It does not modify the linked list.
//No input.
//O(N)
int LinkedPriorityQueue::size() const {
    int size = 0;
    PQNode* temp = front;
    while(temp != NULL){//go through every node
        size++;
        temp = temp->next;
    }
    return size;
}

//void LinkedPriorityQueue::getFront(PQNode*& temp) const;
//This is the private member function of the class.
//It assigns a given pointer the value of the front pointer.
//It helps overload the "<<" operation.
//O(1)
void LinkedPriorityQueue::getFront(PQNode*& temp) const{
    temp = front;
}

//ostream& operator <<(ostream& out, const LinkedPriorityQueue& queue);
//This overloads the "<<" operator in the class.
//O(N)
ostream& operator <<(ostream& out, const LinkedPriorityQueue& queue) {
    out << "{";
    PQNode* temp;
    queue.getFront(temp);//the helper function
    while(temp != NULL){
        out << *temp;//call the overloaded operator for PQNodes
        if(temp->next != NULL){
            out << "," << " ";
        }
        temp = temp->next;
    }
    out << "}";
    return out;
}
