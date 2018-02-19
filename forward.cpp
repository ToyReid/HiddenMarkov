#include "hmm.hpp"
using namespace std;

Forward::Forward() {
    vector<Node *> tmp;
    Node *n = new Node;

    n->val = 1; // Casino always starts in fair state
    n->trace = nullptr;
    tmp.push_back(n);
    table.push_back(tmp);
    
    tmp.clear();
    n = new Node;
    n->val = 0;
    n->trace = nullptr;
    tmp.push_back(n);
    table.push_back(tmp);
}

void Forward::FindProb() {
    int i;
    ifstream in;

    in.open("1.txt");
    sequence = File::ReadToIntVec(in);

    printf("cool");
}

int main() {
    return 0;
}