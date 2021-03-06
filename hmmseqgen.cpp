#include "hmm.hpp"
using namespace std;

double Gen::Rand() {
    return (double)rand() / (double)RAND_MAX;
}

int Gen::DetermineRoll(double prob, map<int, double> weight) {
    double range;

    range = weight[1];
    if(prob <= range) return 1;

    range += weight[2];
    if(prob <= range) return 2;

    range += weight[3];
    if(prob <= range) return 3;

    range += weight[4];
    if(prob <= range) return 4;

    range += weight[5];
    if(prob <= range) return 5;

    return 6;
}

void Gen::MakeSequence() {
    int i, roll;
    map<int, double> curWeight;

    curWeight = fair; // Always fair at start
    for(i = 0; i < rolls; i++) {
        //if(curWeight == fair) printf("F");
        //else printf("L");
        roll = DetermineRoll(Rand(), curWeight);
        //printf("%d ", roll);
        sequence.push_back(roll);

        if(Rand() <= shift) { // Shift to other state
            if(curWeight == fair) curWeight = loaded;
            else curWeight = fair;
        }
    }
    //printf("\n");
}

void Gen::PrintSeq() {
    int i;

    for(i = 0; i < sequence.size(); i++) {
        printf("%d", sequence[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    Gen g;
    g.Rand(); // C's random number generator is not good. This circumvents that for some reason.

    g.MakeSequence();
    g.PrintSeq();

    return 0;
}