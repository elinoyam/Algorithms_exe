#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "graph.h"

#define GOOD_INPUT 0
#define BAD_INPUT -1


using namespace std;

bool checkIfNumber(string stringToCheck);
Graph* timeMeasurement(Graph& i_MainGraph, int i_SourceVertex, int i_TargetVertex);
