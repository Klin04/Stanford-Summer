#include <iostream>
#include <cstdlib>
#include "hello.h"
#include "console.h"
#include <vector>
#include "math.h"
using namespace std;

int i;

int main() {
    cout << "This reminds me things in Stanford" << endl;
    vector<int> store;
    int k = rand();
    store.push_back(1);
    store.push_back(6);
    store.push_back(k);
    for(int i : store) cout << i << endl;
    return 0;
}

int common(int i){
    if(i > 5){
        return i;
    }
    else{
        return i%5;
    }
}
