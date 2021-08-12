#pragma once
#include <iostream>
using namespace std;

/*************** FUNCTION DECLARATIONS ***************
* This class represents an edge in a graph.
* Every edge has origin and target vertexes.
*****************************************************/

class Edge
{
	private: int m_OriginVertex;
	private: int m_TargetVertex;
	
			// This is the ctor of the class
			// This method recieve two ints, the first represent the vertix which the edge begins
			// And the second represent the vertix it ends
	public:	Edge(int i_Origin, int i_Target);

			// This method returns the origin vertex of this edge
	public:	int getEdgeOriginVertex() { return m_OriginVertex; }

			// This method returns the target vertex of this edge
	public: int getEdgeTargetVertex() { return m_TargetVertex; }
	
			// This method implements the printing operator for this edge.
	public: friend ostream& operator<<(ostream& os, const Edge& edge) noexcept {
			os << edge.m_OriginVertex << "  " << edge.m_TargetVertex << endl;
			return os;
		}
};



