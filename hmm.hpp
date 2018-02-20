#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

struct Node {
    double val;
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
    vector<int> sequence;
public:
    map<int, double> fair;
    map<int, double> loaded;
    Gen();
    void MakeSequence();
    double Rand();
    int DetermineRoll(double prob, map<int, double> weight);
    void PrintSeq();
};

class ForVit {
    int seqLength;
    double fairShift;
    double loadShift;
    vector<vector<Node *> > table;
    vector<int> sequence;
public:
    ForVit(string fileName);
    void DeleteTable();
    double ForwardProb();
    void ViterbiSeq();
    string MakeTraceback();
};