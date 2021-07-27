#pragma once
#include "edge.h"

class ListOfEdges
{
public:
	class EdgeNode {
	private: Edge m_Edge;
	private: EdgeNode* m_Next;
	public: EdgeNode(Edge& i_Edge, EdgeNode* i_Next) :m_Edge(i_Edge), m_Next(i_Next) {}
	public: Edge& getEdge() { return m_Edge; }
	public: EdgeNode* getNext() { return m_Next; }
	public: void setNext(EdgeNode* node) { m_Next = node; }
	};

	private: EdgeNode* m_ListHead;
	private: EdgeNode* m_ListTail;
	private: int m_NumberOfEdgesInList;


	public:ListOfEdges() :m_ListHead(nullptr), m_ListTail(nullptr), m_NumberOfEdgesInList(0){}
	public:~ListOfEdges();
	public: bool isEmpty() { return m_NumberOfEdgesInList == 0; }
	public: EdgeNode* addEdgeToTail(Edge & i_EdgeToAdd);
	public: EdgeNode* addEdgeToTail(int i_OriginVertex, int i_TargetVertex, int i_EdgeWeight);
	public: void printList();
	public: EdgeNode* getListHead() { return m_ListHead; }
	public: EdgeNode* getListTail() { return m_ListTail; }
	public: void RemoveEdge(int i_Adjacent);
};

