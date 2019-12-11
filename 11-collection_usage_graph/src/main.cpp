#include <iostream>
#include <fstream>
#include "basicgraph.h"

using namespace std;

string coolest(string filename) {
    ifstream input;
    input.open(filename);

    if(input.fail()){
        input.close();
        throw "File not found. ";
    }

    string name1, name2;
    BasicGraph twitter;

    // name1 name2
    // name1 follows name2
    while(input >> name1 >> name2){
        if(!twitter.containsVertex(name1)){
            twitter.addVertex(name1);
        }
        if(!twitter.containsVertex(name2)){
            twitter.addVertex(name2);
        }
        if(!twitter.containsEdge(name2, name1)){
            // edge represemt name2 followed by name1
            twitter.addEdge(name2, name1);
        }

    }

    int max = 0;
    string maxName = "";
    for(Vertex* v: twitter){
        // fof: number of followers of followers
        int fof = 0;
        for(Vertex* neighbor: twitter.getNeighbors(v)){
            fof += twitter.getNeighbors(neighbor).size();
        }

        if(fof > max){
            max = fof;
            maxName = v->name;
        }
    }

    return maxName;
}

int main() {
    cout << coolest("twitter.txt") << endl;

    return 0;
}
