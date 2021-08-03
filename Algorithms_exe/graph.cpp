#include "graph.h"
#include "queue.h"
#include <math.h>
#define NO_PARENT -1


Graph::Graph(const Graph& other) : m_NumberOfVertex(other.m_NumberOfVertex), m_AdjList(other.m_AdjList) {
}

Graph::~Graph() {
	//for (int i = 0; i < m_NumberOfVertex; ++i) {
	delete[] (m_AdjList);
	//
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

	ListOfEdges& fromVertexList = getEdgesListInIndex(i_FromVertex - 1);
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

int* Graph::BFS(int i_Vertex, int** dbks) {
	Queue queue(m_NumberOfVertex);
	int* d = new int[m_NumberOfVertex];
	int* p = new int[m_NumberOfVertex];
	int vertex;

	for (int i = 0; i < m_NumberOfVertex; i++) {
		d[i] = numeric_limits<int>::max();
		p[i] = NO_PARENT;
	}
	queue.Enqueue(i_Vertex);
	d[i_Vertex - 1] = 0;

	while (!queue.isEmpty()) {
		vertex = queue.Dequeue();
		ListOfEdges& currentVertexAdj = m_AdjList[vertex - 1];
		ListOfEdges::EdgeNode* adj = currentVertexAdj.getListHead();
		while (adj != nullptr) {
			if (d[adj->getEdge().getEdgeTargetVertex() - 1] == numeric_limits<int>::max()) {
				d[adj->getEdge().getEdgeTargetVertex() - 1] = d[vertex - 1] + 1;
				p[adj->getEdge().getEdgeTargetVertex() - 1] = vertex;
				queue.Enqueue(adj->getEdge().getEdgeTargetVertex());
			}

			adj = adj->getNext();
		}
	}

	//need to delete d
	*dbks = d;
	return p;
}

	//	DynamicArray<DynamicArray<int>*>* Graph::BFS(int i_Vertex) {
		//DynamicArray<DynamicArray<int>*>* result = new DynamicArray<DynamicArray<int>*>(m_NumberOfVertex);
		//int* d = new int[m_NumberOfVertex];
		//for (int i = 0; i < m_NumberOfVertex; i++) {
		//	//result->at(i) = nullptr;
		//	result->push_back(new DynamicArray<int>());
		//	d[i] = numeric_limits<int>::max();
		//}

		//d[i_Vertex-1] = 0;
		////result->at(0) = new DynamicArray<int>(1);
		//result->at(0)->push_back(i_Vertex);			// the actual number
		//int index = 0;

		//while (result->at(index)->size() != 0) {
		//	for (int j = 0; j < result->at(index)->size(); j++) {
		//		ListOfEdges& currentVertexAdj = m_AdjList[(result->at(index)->at(j))-1];
		//		ListOfEdges::EdgeNode* adj = currentVertexAdj.getListHead();
		//		while (adj != nullptr) {
		//			if (d[adj->getEdge().getEdgeTargetVertex() - 1]== numeric_limits<int>::max()) {
		//				d[adj->getEdge().getEdgeTargetVertex() - 1] = index + 1;
		//				result->at(index + 1)->push_back(adj->getEdge().getEdgeTargetVertex());
		//			}
		//			adj = adj->getNext();
		//		}
		//	}
		//	index++;
		//}

		//return result;
	//}


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
			adj = adj->getNext();
		}
	}

	return transpose;
}

Graph* Graph::ShortestPathFromSToT(int i_FromVertex, int i_ToVertex) {
	Graph* Gs = new Graph(*this);
	int* degreeList;
	int* parentList;

	parentList = BFS(i_FromVertex, &degreeList);

	for (int i = 0; i < Gs->m_NumberOfVertex; i++) {		// for each vertex
	// go through all the vertexes and delete each edge that degreeList[source] != degreeList[target] 
	ListOfEdges::EdgeNode* currentEdge = Gs->getEdgesListInIndex(i).getListHead();
	
		while (currentEdge != nullptr) {
			int v = currentEdge->getEdge().getEdgeTargetVertex();
			if(degreeList[v-1] != degreeList[i] + 1) {
				currentEdge = currentEdge->getNext();
				Gs->RemoveEdge(i+1, v);
			}
			else {
				currentEdge = currentEdge->getNext();
			}
		}
	}
	// tester
	Gs->PrintGraph();
	cout << "=========================================================" << endl;
	//

	Graph* GsTranspose = Gs->GetTransposedGraph(); // also Htranspose
	
	// tester
	GsTranspose->PrintGraph();
	cout << "=========================================================" << endl;
	//

	//delete p and d, and Gs
	delete Gs;
	delete[] degreeList;
	delete[] parentList;

	parentList = GsTranspose->BFS(i_ToVertex, &degreeList);


	for (int i = 0; i < GsTranspose->m_NumberOfVertex; i++) {
		if(!checkIfParentOfVertex(parentList,i+1,i_ToVertex)) {
			GsTranspose->m_AdjList[i].RemoveAllTheEdges();
		}
		//else go to next u (==i)
	}

	// tester
	GsTranspose->PrintGraph();
	cout << "=========================================================" << endl;
	//

	//delete p and d
	delete[] degreeList;
	delete[] parentList;

	Graph* H = GsTranspose->GetTransposedGraph(); 

	// delete GsTranspose
	delete GsTranspose;

	return H;
}


bool Graph::checkIfParentOfVertex(int* parentList, int vertixToCheck, int parentToFind) {
	bool found = false;
	int currentParent = parentList[vertixToCheck - 1];
	if (vertixToCheck == parentToFind) {
		found = true;
	}

	while(!found && (currentParent != NO_PARENT)) {
		if(currentParent == parentToFind) {
			found = true;
		}
		else {
			currentParent = parentList[currentParent - 1];
		}
	}

	return found;
}

/*Graph* Graph::ShortestPathFromSToT(int i_FromVertex, int i_ToVertex) {
	Graph* Gs = new Graph(m_NumberOfVertex);


	DynamicArray<DynamicArray<int>*>* listOfBfs= BFS(i_FromVertex, &degreeList);
	int index = 0;


	while (listOfBfs->at(index)->size() > 0) {
		for (int i = 0; i < listOfBfs->at(index)->size(); i++) {
			DynamicArray<int>* nextLevel = listOfBfs->at(index + 1);
			int vertixNumber = listOfBfs->at(index)->at(i);
			ListOfEdges newList = m_AdjList[vertixNumber - 1];
			ListOfEdges::EdgeNode* currentEdge = newList.getListHead();
			while (currentEdge != nullptr) {
				bool found = false;
				for (int k = 0; k < nextLevel->size() && !found; k++) {		// check if the next level contain this edge
					if (nextLevel->at(k) == currentEdge->getEdge().getEdgeTargetVertex()) {
						found = true;
					}
				}
				//check if the edge is correct if it is add to a list/ or delete it but before i need to save my original
				if (!found) {
					//save where to go next
					ListOfEdges::EdgeNode* temp = currentEdge->getNext();

					// delete the eadge
					newList.RemoveEdge(currentEdge->getEdge().getEdgeTargetVertex());
					currentEdge = temp;
				}
				else {
					// ignore save the edge
					currentEdge = currentEdge->getNext();
				}
				
				
			}
			ListOfEdges::EdgeNode* node = newList.getListHead();
			while (node != nullptr) {
				Gs->AddEdge(node->getEdge().getEdgeOriginVertex(), node->getEdge().getEdgeTargetVertex());
				node = node->getNext();
			}
			// put the list in the right vertix in the new graph
			
		}
		index++;
	}

	
	Gs->PrintGraph();
	cout << "=========================================================" << endl;

	Graph* GsTranspose = Gs->GetTransposedGraph();  

	GsTranspose->PrintGraph();
	cout << "=========================================================" << endl;
	
	DynamicArray<DynamicArray<int>*>* listOfBfs2222 = GsTranspose->BFS(i_ToVertex);

	Graph* HTranspose = new Graph(m_NumberOfVertex);
	//only save the edges from t
	for (int i = 0; i < listOfBfs2222->size()-1; ++i) {
		DynamicArray<int>* currentLevel = listOfBfs2222->at(i);
		DynamicArray<int>* nextLevel = listOfBfs2222->at(i+1);

		for (int j = 0; j < currentLevel->size(); j++) {
			int currentVertex = currentLevel->at(j);
			ListOfEdges adjList = GsTranspose->GetAdjList(currentVertex); 
			ListOfEdges::EdgeNode* currentEdge = adjList.getListHead();
			while (currentEdge != nullptr) {
				//if(!nextLevel.contains(currentEdge->getEdge().getEdgeTargetVertex())) {
				//	//delete it from list
				//	ListOfEdges::EdgeNode* temp = currentEdge->getNext();
				//	adjList.RemoveEdge(currentEdge->getEdge().getEdgeTargetVertex());
				//	currentEdge = temp;
				//}
				//else {
				//		currentEdge = currentEdge->getNext();
				//}
				if(fakeContains(nextLevel ,currentEdge->getEdge().getEdgeTargetVertex())) {
					HTranspose->AddEdge(currentEdge->getEdge().getEdgeOriginVertex(), currentEdge->getEdge().getEdgeTargetVertex());
				}
				currentEdge = currentEdge->getNext();
			}
		}
	} //end of for 

	Graph* H = HTranspose->GetTransposedGraph();

	delete Gs;
	delete GsTranspose;
	delete HTranspose;
	return H;	
}*/

bool Graph::fakeContains(DynamicArray<int>* arrToSearch, int vertexToFind) {
	bool found = false;
	for (int k = 0; k < arrToSearch->size() && !found; k++) {		// check if the next level contain this edge
		if (arrToSearch->at(k) == vertexToFind) {
			found = true;
		}
	}
	return found;
}
	
	//for (int k = 0; k < m_NumberOfVertex; ++k) {
	//	bool found = false;
	//	for (int i = 0; i < listOfBfs2222->size() && !found; ++i) {
	//		DynamicArray<int>* currentLevel = listOfBfs2222->at(i);
	//		for (int j = 0; j < currentLevel->size(); j++) {
	//			/*int currentVertex = currentLevel->at(j);*/
	//			if (currentLevel->at(j) == (i+1)) {
	//				found = true;
	//			}
	//		}
	//	}

	//	// until here works good ! - TODO

	//	if(!found/*listOfBfs2222.contains(i+1)*/) {
	//		// bad delete its list of ages	
	//		ListOfEdges& list = m_AdjList[k];
	//		ListOfEdges::EdgeNode* currentEdge = list.getListHead();
	//		while (currentEdge != nullptr) {
	//			GsTranspose->RemoveEdge(currentEdge->getEdge().getEdgeOriginVertex(), currentEdge->getEdge().getEdgeTargetVertex());
	//			currentEdge = currentEdge->getNext();
	//		}
	//	}
	////else - good skip

	//} // exit for


	
//}