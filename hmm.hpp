#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
using namespace std;

/* struct Node {
    int val;
    Node *trace;
    Node();
}; */

class Gen {
    int rolls;
    double shift;
    map<int, double> fair;
    map<int, double> loaded;
    vector<int> sequence;
    // vector<vector<Node> >;
public:
    Gen();
    void MakeSequence();
    double Rand();
    int DetermineRoll(double prob, map<int, double> weight);
    void PrintSeq();
};