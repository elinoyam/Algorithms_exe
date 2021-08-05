#include "functionsHeader.h"


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;


int main2() {
    int numberOfVertexes, sourceVertex, targetVertex, edgeSource, edgeTarget;
    string numberString;
    bool WrongInput = false;
    int result = -1;    

    cin >> numberString;
    if (!checkIfNumber(numberString) || cin.eof()){
        cout << "invalid input" << endl;
        WrongInput = true;        
    }
    numberOfVertexes = atoi(numberString.c_str());
    Graph mainGraph(numberOfVertexes);

    cin >> numberString;
    if ((!checkIfNumber(numberString) || cin.eof()) && !WrongInput) {
        cout << "invalid input" << endl;
        WrongInput = true;  
    }
    sourceVertex = atoi(numberString.c_str());

    cin >> numberString;
    if ((!checkIfNumber(numberString) || cin.eof()) && !WrongInput) {
        cout << "invalid input" << endl;
        WrongInput = true;  
    }
    targetVertex = atoi(numberString.c_str());

    if (!WrongInput) {
        try {
            mainGraph.ReadGraph();
            Graph* res = timeMeasurement(mainGraph, sourceVertex, targetVertex);
            res->PrintGraph();
            delete res;
            result = 0;
        }
        catch (exception ex) {
            cout << "invalid input" << endl;
        }
    }
    else {

    }

    return result;
}

int main() {
    main2();
    _CrtDumpMemoryLeaks();
    return 11;
}
