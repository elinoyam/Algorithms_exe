#include "graph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;

#define GOOD_INPUT 0
#define BAD_INPUT -1

int main() {
    int numberOfVertexes, sourceVertex, targetVertex;
    string numberString;
    int result = BAD_INPUT;
    Graph* res = nullptr;
    
    try {
        cin >> numberString;
        if (cin.eof() || !Graph::checkIfNumber(numberString)) {
            throw exception("invalid input");
        }
        numberOfVertexes = atoi(numberString.c_str());
        Graph mainGraph(numberOfVertexes); 

        cin >> numberString;
        if (cin.eof() || !Graph::checkIfNumber(numberString)) {
            throw exception("invalid input");
        }
        sourceVertex = atoi(numberString.c_str());

        cin >> numberString;
        if (cin.eof() || !Graph::checkIfNumber(numberString)) {
            throw exception("invalid input");
        }
        targetVertex = atoi(numberString.c_str());
    
        // read the edges
        mainGraph.ReadGraph();

        auto start = chrono::high_resolution_clock::now();
        // unsync the I/O of C and C++.
        ios_base::sync_with_stdio(false);
        res = mainGraph.ShortestPathFromSToT(sourceVertex, targetVertex);
        auto end = chrono::high_resolution_clock::now();
        // Calculating total time taken by the program.
        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        
        cout << endl << "Time taken by function ShortestPathFromSToT is : " << fixed
            << time_taken << setprecision(9) << " sec" << endl << endl;

        res->PrintGraph();
        result = GOOD_INPUT;
    }
    catch (exception ex) {
        cout << "invalid input" << endl;
    }
    
    if (res != nullptr) {
        delete res;
    }

    return result;
}