#include "functionsHeader.h"

bool checkIfNumber(string stringToCheck) {
    bool res = true;

    for (char ch : stringToCheck) {
        if (ch < '0' || '9' < ch) {
            res = false;
            break;
        }
    }

    return res;
}


Graph* timeMeasurement(Graph& i_MainGraph, int i_SourceVertex, int i_TargetVertex) {
    auto start = chrono::high_resolution_clock::now();
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
    Graph* res = i_MainGraph.ShortestPathFromSToT(i_SourceVertex, i_TargetVertex);
    auto end = chrono::high_resolution_clock::now();
    // Calculating total time taken by the program.
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    ofstream myfile("Measure.txt"); // The name of the file
    myfile << "Time taken by function ShortestPathFromSToT is : " << fixed
        << time_taken << setprecision(9);
    myfile << " sec" << endl;
    myfile.close();

    return res;
}