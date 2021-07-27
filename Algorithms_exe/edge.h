#pragma once
#include <iostream>
using namespace std;

/*
This class is representing an edge in a graph.
Every edge has origin and target vertexes and a weight.
*/

class Edge
{
private: int m_OriginVertex;
private: int m_TargetVertex;
private: int m_EdgeWeight;

public: Edge(int i_Origin, int i_Target, int i_Weight = 1);
public: int getEdgeOriginVertex() { return m_OriginVertex; }
public: int getEdgeTargetVertex() { return m_TargetVertex; }
public: int getEdgeWeight() { return m_EdgeWeight; }
public: friend ostream& operator<<(ostream& os, const Edge& edge) noexcept {
		os << edge.m_OriginVertex << "  " << edge.m_TargetVertex << endl;
		return os;
	}
};



