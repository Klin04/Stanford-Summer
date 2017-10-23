//This program is made by Kaijun Lin.
//It is used to compress text files into smaller files.
//This part does the main work.

#include "encoding.h"
#include "simpio.h"
#include "vector.h"
#include "pqueue.h"
#include "strlib.h"
#include "filelib.h"

void buildEncodingMapHelper(HuffmanNode* root, Map<int, string>& result, string curr = "");
void decodeDataHelper(ibitstream& input, HuffmanNode* encodingTree, ostream& output, HuffmanNode* root);

//This function builds a map that uses the characters as keys
//and their frequencies as corresponding value.
//It takes in a input file as parameter.
//It returns the frequency map.
Map<int, int> buildFrequencyTable(istream& input) {
    Map<int, int> freqTable;
    while(!input.fail()){
        int character = input.get();
        if(character != -1){//do not add -1 in the map
            freqTable[character] += 1;//count the frequency
        }
    }
    freqTable[PSEUDO_EOF]++;//instead, add 256
    return freqTable;//return
}

//HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable);
//This fuction accepts a frequency map and returns a pointer
//that points to the root of the encoding tree.
//It will use a priority queue to keep track of the data.
HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    PriorityQueue<HuffmanNode*> priqueue;
    Vector<int> keys = freqTable.keys();//get the keys
    for(int key : keys){
        HuffmanNode* nodehelp = new HuffmanNode(key, freqTable[key]);//create new Node
        priqueue.enqueue(nodehelp, freqTable[key]);//add the pointer inside the priority queue
    }
    while(priqueue.size() > 1){
        HuffmanNode* node1 = priqueue.dequeue();//node that will be the left child
        HuffmanNode* node2 = priqueue.dequeue();//node that will be the right child
        HuffmanNode* nodeToInsert = new HuffmanNode(NOT_A_CHAR, node1->count + node2->count);//new node that will be the parent and inserted
        nodeToInsert->zero = node1;//assign value
        nodeToInsert->one = node2;
        priqueue.enqueue(nodeToInsert, nodeToInsert->count);//insert the new node
    }
    HuffmanNode* root = priqueue.dequeue();//the last one is the return value
    return root;
}

//Map<int, string> buildEncodingMap(HuffmanNode* encodingTree);
//This function accepts the root of a binary tree.
//It returns the ecodingmap which uses the character as key and their binary expressions as corresponding value.
//Here, if a charater's position is found after left->right->left, then its new binary expression will be 010.
//On the path to find a character, go left means 0, go right means 1.
Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    buildEncodingMapHelper(encodingTree, encodingMap);
    return encodingMap;
}

//void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output);
//This function takes in an input file, a map indicating the rules of compression,
//and an output file.
//It modifies the output file to compress the input file into binary bits of 0 and 1.
//It has no return value.
void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    rewindStream(input);
    while(!input.fail()){//go through every character
        string Out = encodingMap[input.get()];
        for(int i = 0;i < Out.length(); i++){
            if(Out[i] == '0'){//0
                output.writeBit(0);
            }
            else{//1
                output.writeBit(1);
            }
        }
    }
    string end = encodingMap[PSEUDO_EOF];//add the EOF character
    for(int i = 0; i < end.length();i++){
        if(end[i] == '0'){//0
            output.writeBit(0);
        }
        else{//1
            output.writeBit(1);
        }
    }
}

//void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output);
//This function takes in a input file(compressed), a pointer pointing to the root of the encoding tree,
//and a output file.
//It has no return value.
//It reads the input bit file and transforms it into output file which consists of normal characters.
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* root = encodingTree;//keep the very root of the tree
    decodeDataHelper(input, encodingTree, output, root);
}

//void compress(istream& input, obitstream& output);
//This function takes in an input file and compresses it, then storing it in the output file as binary codes.
//It has no return value.
void compress(istream& input, obitstream& output) {
    Map<int, int> freqTable = buildFrequencyTable(input);
    output << freqTable;
    HuffmanNode* root = buildEncodingTree(freqTable);
    Map<int, string> encodingMap = buildEncodingMap(root);
    rewindStream(input);
    encodeData(input, encodingMap, output);
    freeTree(root);//avoid memory leak
}

//void decompress(ibitstream& input, ostream& output);
//This function takes in an input bit file and decompresses it, then storing the decompressed file
//which consists of characters in the output file.
//It has no return value.
void decompress(ibitstream& input, ostream& output) {
    Map<int, int> freqTable;
    input >> freqTable;
    HuffmanNode* rootOfTree = buildEncodingTree(freqTable);
    decodeData(input, rootOfTree, output);
    freeTree(rootOfTree);//avoid memory leak
}

//void freeTree(HuffmanNode* node);
//This function takes in a root node of an encoding tree
//and releases all allocated memory of this tree.
//It has no return value.
void freeTree(HuffmanNode* node) {
    if(node->isLeaf()){//base case
        delete node;
    }
    else if(!node->isLeaf() && node != NULL){//recursive case
        freeTree(node->zero);
        freeTree(node->one);
    }//NULL case : else do nothing
}

//void buildEncodingMap(HuffmanNode* root, Map<int, string>& result);
//This function helps the buildEncodingMap function.
//It reveices a root pointer and a map by reference.
//It has no return value.
void buildEncodingMapHelper(HuffmanNode* root, Map<int, string>& result, string curr){
    if(root == NULL){//base case : NULL
        return;
    }
    else if(!root->isLeaf()){//recursive case
        buildEncodingMapHelper(root->zero, result, curr + "0");
        buildEncodingMapHelper(root->one, result, curr + "1");
    }
    else if(root->isLeaf()){//base case : Leaf
        result[root->character] += curr;
    }
}

//void decodeDataHelper(ibitstream& input, HuffmanNode* encodingTree, ostream& output, HuffmanNode* root);
//This function helps the decodeData function.
//It takes in an input file, a pointer pointing to a node, an output file;
//the additional parameter helps the function start from the root when it succeeds in writing a character.
//The additional parameter is never modified.
//It has no return value.
//It recursively traverses the tree and write a character when meeting a leaf node.
void decodeDataHelper(ibitstream& input, HuffmanNode* encodingTree, ostream& output, HuffmanNode* root){
    if(encodingTree->isLeaf()){//base case
        if(encodingTree->character != PSEUDO_EOF){//no need to have EOF in the output file
           output.put(encodingTree->character);
           HuffmanNode* front = root;//go from the very top again
           decodeDataHelper(input, front, output, root);
        }
        else{
            return;//EOF character, stop recursion and return
        }
    }
    else{
        int oneBit = input.readBit();//store
        if(oneBit != -1){//recursive case while the file is good
            if(oneBit == 0){//0
                decodeDataHelper(input, encodingTree->zero, output, root);
            }
            else if(oneBit == 1){//1
                decodeDataHelper(input, encodingTree->one, output, root);
            }
            else if(encodingTree == NULL){//NULL
                return;
            }
        }
        else{
            return;
        }
    }
}

