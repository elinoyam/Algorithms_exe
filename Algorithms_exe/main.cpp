#include "graph.h"
#include "dynamicArray.h"
#include <iostream>


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int main2() {
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
    /*for (int i = 0; i < 6; i++) {
        DynamicArray<int>* toPrint = res->at(i);
        for (int j = 0; j < toPrint->size(); j++) {
            cout << toPrint->at(j) << " ";
        }
        cout << endl;
    }*/
    res->PrintGraph();
    delete res;
    //gp.PrintGraph();
    return 0;
}

int main() {
    main2();
    _CrtDumpMemoryLeaks();
    return 11;
}