#pragma once
#include "dynamicArray.h"
#include "listOfEdges.h"

class Graph
{
	private: int m_NumberOfVertex;
	private: ListOfEdges* m_AdjList;


	public: Graph(int i_NumberOfVertex) { MakeEmptyGraph(i_NumberOfVertex); }
	public: ~Graph();

	public: void MakeEmptyGraph(int i_NumberOfVertex) { m_AdjList = new ListOfEdges[i_NumberOfVertex]; m_NumberOfVertex = i_NumberOfVertex; }
	public:	bool IsAdjacent(int i_FromVertex, int i_ToVertex);
	public:	ListOfEdges GetAdjList(int i_Vertex) {return m_AdjList[i_Vertex - 1];}
	public:	void AddEdge(int i_FromVertex, int i_ToVertex, int i_Weight); // TODO understand weight??? default = 1?
	public:	void RemoveEdge(int i_FromVertex, int i_ToVertex); 

	public:	void ReadGraph(); // TODO!
	public:	void PrintGraph();
	public:	int IsEmpty(); 
	public:	int AddEdge(int i_FromVertex, int i_ToVertex);
	public:	ListOfEdges Adj(int i_Vertex) {return m_AdjList[i_Vertex - 1];} // todo think of use - same as GetAdjList  https://mama.mta.ac.il/mod/forum/discuss.php?d=389 can do only one
	
	public: DynamicArray<DynamicArray<int>*>* BFS(int i_Vertex);
	public: Graph* GetTransposedGraph();
	public: Graph* ShortestPathFromSToT(int i_FromVertex, int i_ToVertex);
	public: bool fakeContains(DynamicArray<int>* arrToSearch, int vertexToFind);
};

