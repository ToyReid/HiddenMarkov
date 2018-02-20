#include "hmm.hpp"
using namespace std;

ForVit::ForVit(string fileName) {
    vector<Node *> tmp;
    ifstream inFile;
    Node *n = new Node;

    n->val = 1.0; // Casino always starts in fair state
    n->trace = nullptr; // Don't need traceback for forward analysis
    tmp.push_back(n);
    table.push_back(tmp);
    
    tmp.clear();
    n = new Node;
    n->val = 0;
    n->trace = nullptr;
    tmp.push_back(n);
    table.push_back(tmp);

    inFile.open(fileName);
    sequence = File::ReadToIntVec(inFile);

    seqLength = sequence.size();

    fairShift = 0.05;
    loadShift = 0.1;
}

void ForVit::DeleteTable() {
    int i;

    for(i = 0; i < seqLength; i++) {
        if(table[0][i]) {
            delete table[0][i];
        }
        if(table[1][i]) {
            delete table[1][i];
        }
    }

    table.clear();
}

double ForVit::ForwardProb() {
    int i;
    double a, b;
    Gen g;
    Node *n;
    
    for(i = 0; i < seqLength; i++) {
        // Next Fair Block
        //a = prev fair prob.  *   0.95
        a = table[0][i]->val * (1.0 - fairShift);
        //b = prev load prob.  *   0.1
        b = table[1][i]->val * loadShift;
        n = new Node;
        n->val = (a + b) * g.fair[sequence[i]];
        table[0].push_back(n);

        // Next Loaded Block
        //a = prev fair prob.  *   0.05
        a = table[0][i]->val * fairShift;
        //b = prev load prob.  *   0.9
        b = table[1][i]->val * (1.0 - loadShift);
        n = new Node;
        n->val = (a + b) * g.loaded[sequence[i]];
        table[1].push_back(n);
    }

    return table[0][seqLength]->val + table[1][seqLength]->val;
}

void ForVit::ViterbiSeq() {
    int i;
    double a, b;
    Gen g;
    Node *n;

    for(i = 0; i < seqLength; i++) {
        // Next Fair Block
        a = table[0][i]->val * (1.0 - fairShift) * g.fair[sequence[i]];
        b = table[1][i]->val * loadShift * g.fair[sequence[i]];
        n = new Node;
        if(a >= b) {
            n->val = a;
            n->trace = table[0][i];
        }
        else {
            n->val = b;
            n->trace = table[1][i];
        }
        table[0].push_back(n);

        // Next Loaded Block
        a = table[0][i]->val * fairShift * g.loaded[sequence[i]];
        b = table[1][i]->val * (1.0 - loadShift) * g.loaded[sequence[i]];
        n = new Node;
        if(a >= b) {
            n->val = a;
            n->trace = table[0][i];
        }
        else {
            n->val = b;
            n->trace = table[1][i];
        }
        table[1].push_back(n);
    }
}

string ForVit::MakeTraceback() {
    string ret;
    Node *n;
    int i = seqLength - 1;

    if(table[0][seqLength]->val > table[1][seqLength]->val) {
        n = table[0][seqLength];
        ret.append("F");
    }
    else {
        n = table[1][seqLength];
        ret.append("L");
    }
    n = n->trace;

    while(n) {
        if(n == table[0][i]) {
            ret.insert(ret.begin(), 'F');
        } else if(n == table[1][i]) {
            ret.insert(ret.begin(), 'L');
        }
        n = n->trace;
        i--;
    }

    return ret;
}

int main() {
    double prob;
    ofstream oFile;

    ForVit f = ForVit("1.txt");
    prob = f.ForwardProb();
    printf("Probability of Benchmark 1 = %e\n", prob);

    f = ForVit("2.txt");
    prob = f.ForwardProb();
    printf("Probability of Benchmark 2 = %e\n", prob);

    f.DeleteTable(); // Free table

    f = ForVit("1.txt");
    oFile.open("viterbi.1.txt");
    f.ViterbiSeq();
    oFile << f.MakeTraceback();
    f.DeleteTable();
    oFile.close();

    oFile.open("viterbi.2.txt");
    f = ForVit("2.txt");
    f.ViterbiSeq();
    oFile << f.MakeTraceback();
    f.DeleteTable();

    return 0;
}