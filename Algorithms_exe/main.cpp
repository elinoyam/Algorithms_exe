#include "functionsHeader.h"

int main() {
    int numberOfVertexes, sourceVertex, targetVertex;
    string numberString;
    int result = BAD_INPUT;
    Graph* res = nullptr;

    try {
        cin >> numberString;
        if (cin.eof() || !checkIfNumber(numberString)) {
            throw exception("invalid input");
        }
        numberOfVertexes = atoi(numberString.c_str());
        Graph mainGraph(numberOfVertexes); 

        cin >> numberString;
        if (cin.eof() || !checkIfNumber(numberString)) {
            throw exception("invalid input");
        }
        sourceVertex = atoi(numberString.c_str());

        cin >> numberString;
        if (cin.eof() || !checkIfNumber(numberString)) {
            throw exception("invalid input");
        }
        targetVertex = atoi(numberString.c_str());
    
        // read the edges
        mainGraph.ReadGraph();
        res = timeMeasurement(mainGraph, sourceVertex, targetVertex);
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