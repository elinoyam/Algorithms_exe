#include "graph.h"
#include <math.h>

Graph::~Graph() {
	for (int i = 0; i < m_NumberOfVertex; ++i) {
		delete (m_AdjList + i);
	}
}

bool Graph::IsAdjacent(int i_FromVertex, int i_ToVertex) {
	bool found = false;	

	ListOfEdges fromVertexList = m_AdjList[i_FromVertex - 1];
	ListOfEdges::EdgeNode* currentNode = fromVertexList.getListHead();
	while (currentNode != nullptr && !found) {
		if (currentNode->getEdge().getEdgeTargetVertex() == i_ToVertex) {
			found = true;
		}
			
		currentNode = currentNode->getNext();
	}

	return found;
}

void Graph::AddEdge(int i_FromVertex, int i_ToVertex, int i_Weight) { 
	ListOfEdges& fromVertexList = m_AdjList[i_FromVertex - 1];
	fromVertexList.addEdgeToTail(i_FromVertex, i_ToVertex, i_Weight);
}

int Graph::AddEdge(int i_FromVertex, int i_ToVertex ) { 
	int res = 1;
	if(i_FromVertex > m_NumberOfVertex || i_FromVertex < 0 || i_ToVertex > m_NumberOfVertex || i_ToVertex < 0) {
		res = 0;
		//throw invalid_argument("not on scope");
	}
	else {
		ListOfEdges& fromVertexList = m_AdjList[i_FromVertex - 1];
		ListOfEdges::EdgeNode* newElem = fromVertexList.addEdgeToTail(i_FromVertex, i_ToVertex, 1);
		if (newElem == nullptr) {
			res =  0;
		}
	}

	return res;
}


void Graph::RemoveEdge(int i_FromVertex, int i_ToVertex) {
	bool found = false;

	ListOfEdges fromVertexList = m_AdjList[i_FromVertex - 1];
	fromVertexList.RemoveEdge(i_ToVertex);
}


void Graph::ReadGraph() {} // todo

void Graph::PrintGraph() {
	for(int i = 0; i < m_NumberOfVertex; ++i) {
		ListOfEdges& fromVertexList = m_AdjList[i];
		ListOfEdges::EdgeNode* currentNode = fromVertexList.getListHead();
		
		while (currentNode != nullptr) {
			cout << currentNode->getEdge() << endl;
			currentNode = currentNode->getNext();
		}
	}
}

int Graph::IsEmpty() {
	int isGrapgEmpty = 0;
	if (0 == m_NumberOfVertex) {
		isGrapgEmpty = 1;
	}

	return isGrapgEmpty;
}

DynamicArray<DynamicArray<int>*>* Graph::BFS(int i_Vertex) {
	DynamicArray<DynamicArray<int>*>* result = new DynamicArray<DynamicArray<int>*>(m_NumberOfVertex);
	int* d = new int[m_NumberOfVertex];
	for (int i = 0; i < m_NumberOfVertex; i++) {
		result->push_back(new DynamicArray<int>());
		d[i] = numeric_limits<int>::max();
	
	}
	d[i_Vertex-1] = 0;
	result->at(0)->push_back(i_Vertex);			// the actual number
	int index = 0;

	while (result->at(index)->size() != 0) {
		for (int j = 0; j < result->at(index)->size(); j++) {
			ListOfEdges& currentVertexAdj = m_AdjList[(result->at(index)->at(j))-1];
			ListOfEdges::EdgeNode* adj = currentVertexAdj.getListHead();
			while (adj != nullptr) {
				if (d[adj->getEdge().getEdgeTargetVertex() - 1]== numeric_limits<int>::max()) {
					d[adj->getEdge().getEdgeTargetVertex() - 1] = index + 1;
					result->at(index + 1)->push_back(adj->getEdge().getEdgeTargetVertex());
				}
				adj = adj->getNext();
			}
		}
		index++;
	}

	return result;
}

