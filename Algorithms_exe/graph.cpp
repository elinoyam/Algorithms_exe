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

Graph* Graph::GetTransposedGraph() {
	Graph* transpose = new Graph(m_NumberOfVertex);

	for (int i = 0; i < m_NumberOfVertex; i++) {
		ListOfEdges& list = m_AdjList[i];
		ListOfEdges::EdgeNode* adj = list.getListHead();

		while (adj != nullptr) {
			int origin = adj->getEdge().getEdgeOriginVertex();
			int target = adj->getEdge().getEdgeTargetVertex();
			int weight = adj->getEdge().getEdgeWeight();
			transpose->AddEdge(target, origin, weight);				// add the oposite edge to the G tranpose
		}
	}

	return transpose;
}

Graph* Graph::ShortestPathFromSToT(int i_FromVertex, int i_ToVertex) {
	Graph* Gs = new Graph(m_NumberOfVertex);

	DynamicArray<DynamicArray<int>*>* listOfBfs = BFS(i_FromVertex);
	int index = 0;

	while (listOfBfs->at(index)->size() > 0) {
		for (int i = 0; i < listOfBfs->at(-index)->size(); i++) {
			DynamicArray<int>* nextLevel = listOfBfs->at(index + 1);
			int vertixNumber = listOfBfs->at(index)->at(i);
			ListOfEdges newList = m_AdjList[vertixNumber - 1];
			ListOfEdges::EdgeNode* currentEdge = newList.getListHead();
			while (currentEdge != nullptr) {
				bool found = false;
				for (int k = 0; k < nextLevel->size() && !found; k++) {		// check if the next level contain this edex
					if (nextLevel->at(k) == currentEdge->getEdge().getEdgeTargetVertex()) {
						found = true;
					}
				}
				//check if the eage is correct if it is add to a list/ delete it but before i need to save my original
				if (!found) {
					// delete the eadge
					newList.RemoveEdge(currentEdge->getEdge().getEdgeTargetVertex());
				}
				// ignore save the edge
				
				currentEdge = currentEdge->getNext();
			}
			ListOfEdges::EdgeNode* node = newList.getListHead();
			while (node != nullptr) {
				Gs->AddEdge(node->getEdge().getEdgeOriginVertex(), node->getEdge().getEdgeTargetVertex());
			}
			// put the list in the right vertix in the new graph
			
		}
		index++;
	}


	Graph* GsTranspose = Gs->GetTransposedGraph();  

	DynamicArray<DynamicArray<int>*>* listOfBfs2222 = GsTranspose->BFS(i_ToVertex);

	Graph* HTranspose = new Graph(m_NumberOfVertex);
	//only save the edges from t
	
	for (int i = 0; i < m_NumberOfVertex; ++i) {
		bool found = false;
		for (int i = 0; i < listOfBfs2222->size() && !found; ++i) {
			DynamicArray<int>* currentLevel = listOfBfs2222->at(i);
			for (int j = 0; j < currentLevel->size(); j++) {
				/*int currentVertex = currentLevel->at(j);*/
				if (currentLevel->at(j) == (i+1)) {
					found = true;
				}
			}
		}

		if(!found/*listOfBfs2222.contains(i+1)*/) {
			// bad delete its list of ages	
			ListOfEdges& list = m_AdjList[i];
			ListOfEdges::EdgeNode* currentEdge = list.getListHead();
			while (currentEdge != nullptr) {
				GsTranspose->RemoveEdge(currentEdge->getEdge().getEdgeOriginVertex(), currentEdge->getEdge().getEdgeTargetVertex());
			}
		}
	//else - good skip

	} // exit for


	Graph* H = HTranspose->GetTransposedGraph();
	return H;		
}