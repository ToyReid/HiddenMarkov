#include "hmm.hpp"
using namespace std;

Node::Node() {
    val = -1;
    trace = nullptr;
}

vector<int> File::ReadToIntVec(ifstream& inFile) {
    char c;
    vector<int> ret;
    
    while(inFile >> c) {
        ret.push_back(c - '0');
    }

    return ret;
}