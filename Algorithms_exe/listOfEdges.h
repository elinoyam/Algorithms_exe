#pragma once
#include "edge.h"
using namespace std;

/*************** FUNCTION DECLARATIONS ***************
* This class represents a list of edges in a graph.
* The data structure is a linked list by pointers
* Every vertex in the graph has a list of edges to his neighbors
*****************************************************/

class ListOfEdges
{
public:
	class EdgeNode {
		private: Edge m_Edge;
		private: EdgeNode* m_Next;

				// This is the EdgeNode ctor.
				// The ctor recives the Edge to hold and a pointer to the next edge in the list.
		public: EdgeNode(Edge& i_Edge, EdgeNode* i_Next) :m_Edge(i_Edge), m_Next(i_Next) {}

				// This method returns the edge it holds.
		public: Edge getEdge() { return m_Edge; }

				// This method returns a pointer to the next edge in the list.
		public: EdgeNode* getNext() { return m_Next; }

				// This method receives a pointer to EdgeNode and set it to the m_Next field
		public: void setNext(EdgeNode* node) { m_Next = node; }
	};

	private: EdgeNode* m_ListHead;
	private: EdgeNode* m_ListTail;
	private: int m_NumberOfEdgesInList;

			// This is the ListOfEdges empty ctor.
	public: ListOfEdges() : m_ListHead(nullptr), m_ListTail(nullptr), m_NumberOfEdgesInList(0) {}

			// This is the ListOfEdges copy-ctor.
	public: ListOfEdges(const ListOfEdges& other);

			// This is the ListOfEdges dtor.
	public:~ListOfEdges();

			// This method returns true is there isn't any edges in this list. (No adjacents to this vertex)
	public: bool isEmpty() { return m_NumberOfEdgesInList == 0; }

			// This method receives an edge and add it to the tail of the list.
	public: EdgeNode* addEdgeToTail(Edge i_EdgeToAdd);

			// This method receives to vertexes and makes new edge between the two,
			// and then adds the new edge to the end of the list.
	public: EdgeNode* addEdgeToTail(int i_OriginVertex, int i_TargetVertex);

			// This method prints all the edges in the list.
	public: void printList();

			// This method returns a pointer to the head of the list.
	public: EdgeNode* getListHead() { return m_ListHead; }

		  // This method returns a pointer to the tail of the list.
	public: EdgeNode* getListTail() { return m_ListTail; }

			// This method receives a number of a vertex (i_Adjacent),
			// and delete from this list the edge with the same target vertex.
	public: void RemoveEdge(int i_Adjacent);

			// This method is deleting all the edges in this list.
	public: void RemoveAllTheEdges();

};

