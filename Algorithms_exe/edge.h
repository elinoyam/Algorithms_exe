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

	public: Edge(int i_Origin, int i_Target);
	public: int getEdgeOriginVertex() { return m_OriginVertex; }
	public: int getEdgeTargetVertex() { return m_TargetVertex; }
	public: friend ostream& operator<<(ostream& os, const Edge& edge) noexcept {
			os << edge.m_OriginVertex << "  " << edge.m_TargetVertex << endl;
			return os;
		}
};



