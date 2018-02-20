#include "hmm.hpp"
using namespace std;

Node::Node() {
    val = -1;
    trace = nullptr;
}

Gen::Gen() {
    int i;

    for(i = 1; i <= 6; i++) {
        fair.insert(pair<int, double>(i, 1/(double)6));
    }
    for(i = 1; i <= 5; i++) {
        loaded.insert(pair<int, double>(i, 0.1));
    }
    loaded.insert(pair<int, double>(6, 0.5));

    shift = 0.05;
    rolls = 300;
}

vector<int> File::ReadToIntVec(ifstream& inFile) {
    char c;
    vector<int> ret;
    
    while(inFile >> c) {
        ret.push_back(c - '0');
    }

    return ret;
}