#pragma once
#include "listOfEdges.h"
#include "queue.h"
#include "limits"
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

			// This method receives a string and returns if this string contains a number
	public: static bool checkIfNumber(string stringToCheck);

			// This method receives an index i and returns the i'th adjacent vertex 
	private: ListOfEdges& getEdgesListInIndex(int index) { return m_AdjList[index]; }

			// This method is getting a list og parents that was returned by the BFS algorithm,
			// and recives the number of the vertex we want to check and the number of the parent vertex.
		    // The method will return true if the parentToFind is a parent of vertixToCheck.
	private: bool checkIfParentOfVertex(int* parentList, int vertixToCheck, int parentToFind);

			// This is the Graph ctor, that receives the number of vertexes in the new graph.
	public: Graph(int i_NumberOfVertex) { MakeEmptyGraph(i_NumberOfVertex); }

			// This is the graph copy-ctor
	public: Graph(const Graph& other);

			// This is the Graph dtor
	public: ~Graph();
			
			// This method is making a new ListOfEdges according to the given parameter i_NumberOfVertex.
	public: void MakeEmptyGraph(int i_NumberOfVertex) { m_AdjList = new ListOfEdges[i_NumberOfVertex]; m_NumberOfVertex = i_NumberOfVertex; }

			// This method returns true if there is an edge from i_FromVertex to i_ToVertex.
	public:	bool IsAdjacent(int i_FromVertex, int i_ToVertex);

			// This method returns the adjacent list of the given i_Vertex.
	public:	ListOfEdges GetAdjList(int i_Vertex) {return m_AdjList[i_Vertex - 1];}

			// This method deletes the edge between the given i_FromVertex and i_ToVertex.
	public:	void RemoveEdge(int i_FromVertex, int i_ToVertex); 

			// This method is reading a graph from the user.
			// The method will add all the given edges from the user.
	public:	void ReadGraph(); 
			
			// This method prints all the edges in this graph.
	public:	void PrintGraph();

			// This method returns true if the m_NumberOfVertex of this graph is 0.
	public:	int IsEmpty(); 

			// This method is adding an edge between the given i_FromVertex and i_ToVertex.
			// This method returns 1 is the edge was added successfully or 0 otherwise.
	public:	int AddEdge(int i_FromVertex, int i_ToVertex);

			// This method returns a list of all the adjacent vertexes of the given i_Vertex.
	public:	ListOfEdges Adj(int i_Vertex) {return m_AdjList[i_Vertex - 1];} 
	
			// This method is implementation of the BFS algorithm we studied at class.
			// We implemented it using a queue.
			// The method receives the number of the source vertex (i_Vertex),
			// and an int array in which it returns the degree of each vertex in the graph from i_Vertex.
	public: int* BFS(int i_Vertex, int** degreeList);

			// This method returns the transposed graph of this graph.
	public: Graph* GetTransposedGraph();

			// This method is implementation of the given algorithm in this project.
			// The method finds and return a graph that holds all the shortest paths from the given i_FromVertex to i_ToVertex.
			// This method is using the BFS algorithm and the GetTransposedGraph method.
	public: Graph* ShortestPathFromSToT(int i_FromVertex, int i_ToVertex);
};

