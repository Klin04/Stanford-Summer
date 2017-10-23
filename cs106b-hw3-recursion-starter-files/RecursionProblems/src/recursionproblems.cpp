//This program is made by Kaijun Lin.
//It contains several problems solved by recursive functions.
//Loops and data structures are used under certain constraints.

// Please feel free to add any other #includes you need!
#include "recursionproblems.h"
#include <cmath>
#include <iostream>
#include "hashmap.h"
#include "map.h"
#include "random.h"
#include "simpio.h"
#include "error.h"
#include "strlib.h"
using namespace std;

//bool validity(string test)
//This program checks if the string input is of our standard.
//It outputs a boolean value indicating whether the string fits our rules.
//This function helps the convert function.
bool validity(string test);
//int findPairs(string& target, string toFind);
//This function takes in a target string and finds those supposed to
//be found in that target.
//This functions finds the substrings given in the spec.pdf.
//It then erases them if founded.
//The integer returned indicates whether the string are found.
int findPairs(string& target, string toFind);
//int floodFillHelper(GBufferedImage& image, int x, int y, int color,int& total);
//It helps the floodFill function to count the total pixels painted.
//It mostly works as floodFill function(See floodFill header).
//It returns the total number of pixels painted.
//It passes total by reference to change it every time a pixel is painted.
int floodFillHelper(GBufferedImage& image, int x, int y, int color, int& total, int origin);
//void readInput(istream& input, HashMap<string ,Vector<string> >& store);
//This function reads from the input file and stores the text
//in the hashmap that is passed in by reference.
//It has no output.
//It helps the GenerateGrammar function.
void readInput(istream &input, HashMap<string,Vector<string> >& store);
//string grammarGenerateHelper(HashMap<string, Vector<string> >& rules, string symbol);
//It takes in a hashmap which shows the rule.
//It takes in a string that implies which kind of phrases we should create.
//It returns the string that it creates.
//This function helps the "grammarGenerate" function.
string grammarGenerateHelper(HashMap<string, Vector<string> >& rules, string symbol);

int countKarelPaths(int street, int avenue) {
    //TODO: write this function
    return 0;
}

//int convertStringToInteger(string exp);
//This function takes in a string representing an integer.
//It returns the integer the string represents.
int convertStringToInteger(string exp) {
    if(validity(exp) == false){
        error("Invalid integer string! (threw an exception)"); //exception case
    }
    else{
        if(exp == ""){//base case
            return 0;
        }
        else{//recursive case
            if(exp[0] == '-'){ //negative special case
                exp = exp.substr(1);
                return -convertStringToInteger(exp);
            }
            char tail = exp[exp.size() - 1];
            int last = tail - '0';//convert char into int
            return last  + convertStringToInteger(exp.substr(0,exp.size() - 1)) * 10;
        }
    }
    return 0;
}

//bool isBalanced(string exp);
//This function takes in a string as a parameter.
//It returns a boolean value indicating whether the string is balanced
//according to our rules.
bool isBalanced(string exp) {
    if(exp == ""){  //base case
        return true;
    }
    else if(exp.size() % 2 == 1){ // base case
        return false;
    }
    else{//recursive case
        int pos1 = findPairs(exp, "()");
        int pos2 = findPairs(exp, "[]");
        int pos3 = findPairs(exp, "{}");
        int pos4 = findPairs(exp, "<>");
        if(pos1 != -1 || pos2 != -1 || pos3 != -1 || pos4 != -1){
            //Make sure that not all elements are not found
            return isBalanced(exp);
        }
        else{
            if(exp.size() != 0){
                return false;
            }
        }
    }
    return false;
}

//double weightOnKnees(int row, int col, Vector<Vector<double> >& weights);
//This function takes in two integers representing a row and a column.
//It also takes in a vector of vectors showing a group of people's weights.
//It returns each weight on each person's knee.
double weightOnKnees(int row, int col, Vector<Vector<double> >& weights) {
    Vector<Vector<double> > weight;
    weight = weights;
    if(row < 0 || col < 0 || row > weight.size() - 1 || col > weight[row].size() - 1){
        return 0;//base case when reaching the edge
    }
    else{
        weight[row][col] = weight[row][col] + 0.5 * weightOnKnees(row - 1, col, weight) + 0.5 * weightOnKnees(row - 1, col - 1, weight);
        return weight[row][col]; //recursive case
    }
    return 0.0;
}

//void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order);
//This function takes in a GWindow object and draws Sierpinski triangles in it.
//This function takes in three doubles implying the starting point and the length
//of each side of the triangles.
//The order shows how many levels of the triangles we will draw.
//It has no output.
void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order) {
    if(x < 0 || y < 0 || size < 0 || order < 0){//exception case
        error("");
    }
    else if(order == 0){//base case
        cout << "";
    }
    else if(order == 1){//base case 2
        gw.drawLine(x + size, y, x, y);
        gw.drawLine(x + size / 2, y + sqrt(3) * size / 2, x, y);
        gw.drawLine(x + size / 2, y + sqrt(3) * size / 2, x + size, y);
    }
    else{//recursive case
        drawSierpinskiTriangle(gw, x + size / 2, y, size / 2, order - 1);
        drawSierpinskiTriangle(gw, x + size / 4, y + sqrt(3) * size / 4, size / 2, order - 1);
        drawSierpinskiTriangle(gw, x, y, size / 2, order - 1);
        gw.drawLine(x + size, y, x, y);
        //gw.drawLine(x + size / 2, y + sqrt(3) * size / 2, x, y);
        //gw.drawLine(x + size / 2, y + sqrt(3) * size / 2, x + size, y);
        //NO need for three statement if order == 1 is added
    }
}

//int floodFill(GBufferedImage& image, int x, int y, int color)
//This function takes in an image and two integers implying
//the starting point.
//Another integer indicates the color that needs filling in the zone.
//It returns the total pixels painted.
int floodFill(GBufferedImage& image, int x, int y, int color) {
    int total = 0;
    int origin = image.getRGB(x, y);
    if(origin != color){//recursive case
        total = floodFillHelper(image, x, y, color, total, origin);
        return total;
    }
    return 0;//base case without else statement
}

//Vector<string> grammarGenerate(istream& input, string symbol, int times)
//This function takes in an input file, a string indicating the type of grammar,
//and a integer showing how many phrases should be created.
//It returns the produced phrases in a vector.
//We apply two helper function here to separate the two parts of it.
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    Vector<string> v;
    if(symbol == ""){//exception case
        error("");
    }
    else if(times <= 0){
        return v;
    }
    else{
        HashMap<string,Vector<string> > rules;
        readInput(input, rules);//First Part
        for(int i = 0;i < times ;i++){
            string toHave = grammarGenerateHelper(rules, symbol);//Second Part
            v.add(toHave);
        }
    }
    return v;
}

//Here starts the helper or supplement functions.
//Also seen at the beginning of this file.
bool validity(string test){
    if(test.size() == 0){
        return true;
    }
    else{
        if(test[0] == '-'){//base case
            test = test.substr(1);
        }
        char ch = test[0];
        if(ch >= '0' && ch <= '9'){//recursive case
            return validity(test.substr(1));
        }
    }
    return false;
}

int findPairs(string& target, string toFind){
   int pos = target.find(toFind, 0);
   if(pos != -1){
       target.erase(pos,2);
       return pos;//pos here just indicates whether string "toFind" exists
   }
   return pos;
}

int floodFillHelper(GBufferedImage& image, int x, int y, int color, int& total,int origin){
    if(image.inBounds(x, y) && image.getRGB(x, y) == origin){                          //use only one base case that the pixel is in bound
        if(image.getRGB(x, y) != color){
            image.setRGB(x, y, color);
            total ++;//count the total pixels
        //Check every single pixel is in bounds and its color is different
        //from the one we offered.
            floodFillHelper(image, x + 1, y, color, total, origin);
            floodFillHelper(image, x - 1, y, color, total, origin);
            floodFillHelper(image, x, y + 1, color, total, origin);
            floodFillHelper(image, x, y - 1, color, total, origin);
        }
//        if(image.inBounds(x + 1, y) && image.getRGB(x + 1, y) == origin){
//            //inBounds must precede getRGB, or some value will be out of bounds
//            floodFillHelper(image, x + 1, y, color, total);
//        }
//        if(image.inBounds(x - 1, y) && image.getRGB(x - 1, y) == origin)
//            floodFillHelper(image, x - 1, y, color, total);
//        }
//        if(image.inBounds(x, y + 1) && image.getRGB(x, y + 1) == origin){
//            floodFillHelper(image, x, y + 1, color, total);
//        }
//        if(image.inBounds(x, y - 1) && image.getRGB(x, y - 1) == origin){
//            floodFillHelper(image, x, y - 1, color, total);
//        }
    }
     return total;
}

void readInput(istream& input, HashMap<string,Vector<string> >& store){
    string line;
    while(getline(input,line)){//reads input test
        int pos1 = line.find_first_of(':'); // try separating the left and the right
        string key = line.substr(0, pos1);
        if(store.containsKey(key)){
            error("Do not pass in two same non-terminal with different rules!");
            break;//exception case
        }
        Vector<string> store1;
        store1 = stringSplit(line.substr(pos1 + 3), "|");//This separate the words on the right side.
        store.add(key, store1);
    }
}

string grammarGenerateHelper(HashMap<string, Vector<string> >& rules, string symbol){
    string toGo;
    if(!rules.containsKey(symbol)){//base case
        toGo += symbol;
        toGo +=" ";
        return toGo;
    }
    else{//recursive case
        Vector<string> temp = rules.get(symbol);
        int random = randomInteger(0,temp.size() - 1);
        string now = temp[random]; //randomly select an element
        Vector<string> temp1 = stringSplit(now, " ");
        for(string type: temp1){// loop over the vector and create longer sentence
            toGo += grammarGenerateHelper(rules, type);
        }
    }
    return toGo;
}
