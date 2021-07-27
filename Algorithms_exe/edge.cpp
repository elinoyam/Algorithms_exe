#include "edge.h"

Edge::Edge(int i_Origin, int i_Target, int i_Weight) {
	this->m_OriginVertex = i_Origin;
	this->m_TargetVertex = i_Target;
	this->m_EdgeWeight = i_Weight;
}
