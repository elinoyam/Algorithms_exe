#include "graph.h"
#include "dynamicArray.h"
#include <iostream>
#include <string>


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;



bool checkIfNumber(string stringToCheck);

int main2() {
    int numberOfVertexes, sourceVertex, targetVertex, edgeSource, edgeTarget;
    string numberString;
    bool WrongInput = false;

    cin >> numberString;
    if (!checkIfNumber(numberString) && !WrongInput) {
        cout << "wrong input" << endl;
        WrongInput = true;        
    }
    numberOfVertexes = atoi(numberString.c_str());
    Graph mainGraph(numberOfVertexes);

    cin >> numberString;
    if (!checkIfNumber(numberString) && !WrongInput) {
        cout << "wrong input" << endl;
        WrongInput = true;  
    }
    sourceVertex = atoi(numberString.c_str());

    cin >> numberString;
    if (!checkIfNumber(numberString) && !WrongInput) {
        cout << "wrong input" << endl;
        WrongInput = true;  
    }
    targetVertex = atoi(numberString.c_str());

    cin >> numberString;

    while (!cin.eof() && !WrongInput) { 
        
        if (!checkIfNumber(numberString)) {
            cout << "wrong input" << endl;
            WrongInput = true;  
        }
        // check if number
        edgeSource = atoi(numberString.c_str());


        cin >> numberString;

        if (!checkIfNumber(numberString) || cin.eof()) {
            cout << "wrong input" << endl;
            WrongInput = true;  
        }
        // check if number
        edgeTarget = atoi(numberString.c_str());
        mainGraph.AddEdge(edgeSource, edgeTarget);
        cin >> numberString;
    }

    if (!WrongInput) {
        Graph* res = mainGraph.ShortestPathFromSToT(sourceVertex, targetVertex);
        res->PrintGraph();
        delete res;
    }


/* tester
    int n = 6;
    Graph gp(n);
    gp.AddEdge(6, 5);
    gp.AddEdge(5, 6);
    gp.AddEdge(6, 1);
    gp.AddEdge(1, 6);
    gp.AddEdge(1, 5);
    gp.AddEdge(2, 5);
    gp.AddEdge(1, 2);
    gp.AddEdge(2, 1);
    gp.AddEdge(5, 4);
    gp.AddEdge(4, 2);
    gp.AddEdge(5, 3);
    gp.AddEdge(4, 3);
    gp.AddEdge(2, 3);
    gp.AddEdge(3, 1);

    gp.PrintGraph();
    cout << "=========================================================" << endl;

    Graph* res = gp.ShortestPathFromSToT(1, 4);
    //for (int i = 0; i < 6; i++) {
        DynamicArray<int>* toPrint = res->at(i);
        for (int j = 0; j < toPrint->size(); j++) {
            cout << toPrint->at(j) << " ";
        }
        cout << endl;
    //}
    res->PrintGraph();
    delete res;
    //gp.PrintGraph();
    */ 
    cout << "End of program!!!" << endl;
    return 0;
}

int main() {
    main2();
    _CrtDumpMemoryLeaks();
    return 11;
}


bool checkIfNumber(string stringToCheck) {
    bool res = true;

    for (char ch : stringToCheck)    {
        if (ch < '0' || '9' < ch) {
            res = false;
            break;
        }
    }
    return res;
}