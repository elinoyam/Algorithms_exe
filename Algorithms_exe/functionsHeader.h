#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "graph.h"

using namespace std;

bool checkIfNumber(string stringToCheck);
Graph* timeMeasurement(Graph& i_MainGraph, int i_SourceVertex, int i_TargetVertex);
