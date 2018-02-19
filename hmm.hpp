#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
#include "readFile.hpp"
using namespace std;

struct Node {
    int val;
    Node *trace;
    Node();
};

class File {
public:
    static vector<int> ReadToIntVec(ifstream& inFile);
};

class Gen {
    int rolls;
    double shift;
    map<int, double> fair;
    map<int, double> loaded;
    vector<int> sequence;
public:
    Gen();
    void MakeSequence();
    double Rand();
    int DetermineRoll(double prob, map<int, double> weight);
    void PrintSeq();
};

class Forward {
    double shift;
    vector<vector<Node *> > table;
    vector<int> sequence;
public:
    Forward();
    void FindProb();
};