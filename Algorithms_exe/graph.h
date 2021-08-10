#pragma once
#include "listOfEdges.h"
#include "queue.h"
//#include "functionsHeader.h"
#include <math.h>
#define NO_PARENT -1

/*************** FUNCTION DECLARATIONS ***************
* This class represents a Graph,
* The data structure is an Adjacency List
*****************************************************/

class Graph
{
	private: int m_NumberOfVertex;
	private: ListOfEdges* m_AdjList;

	public: static bool checkIfNumber(string stringToCheck);
	private: ListOfEdges& getEdgesListInIndex(int index) { return m_AdjList[index]; }
	private: bool checkIfParentOfVertex(int* parentList, int vertixToCheck, int parentToFind);
	public: Graph(int i_NumberOfVertex) { MakeEmptyGraph(i_NumberOfVertex); }
	public: Graph(const Graph& other);
	public: ~Graph();

	public: void MakeEmptyGraph(int i_NumberOfVertex) { m_AdjList = new ListOfEdges[i_NumberOfVertex]; m_NumberOfVertex = i_NumberOfVertex; }
	public:	bool IsAdjacent(int i_FromVertex, int i_ToVertex);
	public:	ListOfEdges GetAdjList(int i_Vertex) {return m_AdjList[i_Vertex - 1];}
	public:	void RemoveEdge(int i_FromVertex, int i_ToVertex); 

	public:	void ReadGraph(); 
	public:	void PrintGraph();
	public:	int IsEmpty(); 
	public:	int AddEdge(int i_FromVertex, int i_ToVertex);
	public:	ListOfEdges Adj(int i_Vertex) {return m_AdjList[i_Vertex - 1];} 
	
	public: int* BFS(int i_Vertex, int** dbks);
	public: Graph* GetTransposedGraph();
	public: Graph* ShortestPathFromSToT(int i_FromVertex, int i_ToVertex);
};

