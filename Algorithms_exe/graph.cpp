#include "graph.h"

bool Graph::checkIfNumber(string stringToCheck) {
	bool res = true;

	for (char ch : stringToCheck) {
		if (ch < '0' || '9' < ch) {
			res = false;
			break;
		}
	}

	return res;
}

Graph::Graph(const Graph& other) : m_NumberOfVertex(other.m_NumberOfVertex) {
	m_AdjList = new ListOfEdges[m_NumberOfVertex];

	for (int i = 0; i < m_NumberOfVertex; i++) {				// for each vertex
		ListOfEdges::EdgeNode* edge = other.m_AdjList[i].getListHead();
		while (edge != nullptr) {								// copy all the edges he has
			m_AdjList[i].addEdgeToTail(edge->getEdge());
			edge = edge->getNext();
		}
		//m_AdjList[i] = other.m_AdjList[i];
	}
}

Graph::~Graph() {
	delete[] (m_AdjList);
}

bool Graph::IsAdjacent(int i_FromVertex, int i_ToVertex) {
	bool found = false;	

	ListOfEdges fromVertexList = m_AdjList[i_FromVertex - 1];			// get the edges of the i_FromVertex vertex 
	ListOfEdges::EdgeNode* currentNode = fromVertexList.getListHead();
	while (currentNode != nullptr && !found) {
		if (currentNode->getEdge().getEdgeTargetVertex() == i_ToVertex) {			// if this edge is from i_FromVertex to i_ToVertex
			found = true;
		}
			
		currentNode = currentNode->getNext();
	}

	return found;
}

int Graph::AddEdge(int i_FromVertex, int i_ToVertex) { 

	int res = 1;
	if (i_FromVertex > m_NumberOfVertex || i_FromVertex < 0 || i_ToVertex > m_NumberOfVertex || i_ToVertex < 0) {
		res = 0;
		throw 5;	// invalid_argument("not on scope");
	}
	else {
		ListOfEdges& fromVertexList = m_AdjList[i_FromVertex - 1];
		ListOfEdges::EdgeNode* newElem = fromVertexList.addEdgeToTail(i_FromVertex, i_ToVertex);
		if (newElem == nullptr) {
			res = 0;
		}
	}

	return res;
}

void Graph::RemoveEdge(int i_FromVertex, int i_ToVertex) {
	bool found = false;

	ListOfEdges& fromVertexList = getEdgesListInIndex(i_FromVertex - 1);
	fromVertexList.RemoveEdge(i_ToVertex);
}

void Graph::ReadGraph() {
	string numberString;
	int edgeSource;
	int edgeTarget;

	cin >> numberString;

    while (!cin.eof()) { 
		if (!checkIfNumber(numberString)) {
			throw 5;	// invalid_argument("The given vertex is not in a digit.");
		}
		// check if number
		edgeSource = atoi(numberString.c_str());

		cin >> numberString;

		if (!checkIfNumber(numberString) || cin.eof()) {
			throw invalid_argument("The given vertex is not in a digit.");
		}
			
		edgeTarget = atoi(numberString.c_str());
		AddEdge(edgeSource, edgeTarget);
		cin >> numberString;
    }
} 

void Graph::PrintGraph() {
	for(int i = 0; i < m_NumberOfVertex; ++i) {					// for each vertex
		ListOfEdges& fromVertexList = m_AdjList[i];
		ListOfEdges::EdgeNode* currentNode = fromVertexList.getListHead();
		
		while (currentNode != nullptr) {						// go through all his edges
			cout << currentNode->getEdge() << endl;				// print each edge
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

int* Graph::BFS(int i_Vertex, int** degreeList) {
	Queue queue(m_NumberOfVertex);
	int* d = new int[m_NumberOfVertex];
	int* p = new int[m_NumberOfVertex];
	int vertex;

	for (int i = 0; i < m_NumberOfVertex; i++) {		// INIT loop
		d[i] = numeric_limits<int>::max();				// sign that we haven't visited this vertex yet
		p[i] = NO_PARENT;
	}

	queue.Enqueue(i_Vertex);						   // enter the i_Vertex (starting point) to the queue
	d[i_Vertex - 1] = 0;							   // set it to the 0 "level"

	while (!queue.isEmpty()) {
		vertex = queue.Dequeue();
		ListOfEdges& currentVertexAdj = m_AdjList[vertex - 1];
		ListOfEdges::EdgeNode* adj = currentVertexAdj.getListHead();
		while (adj != nullptr) {						// for each edge of the vertex will took from the queue
			if (d[adj->getEdge().getEdgeTargetVertex() - 1] == numeric_limits<int>::max()) {		// if we haven't visited this edge target vertex
				d[adj->getEdge().getEdgeTargetVertex() - 1] = d[vertex - 1] + 1;					// set his degree
				p[adj->getEdge().getEdgeTargetVertex() - 1] = vertex;								// set his parent (in the MAKAB)
				queue.Enqueue(adj->getEdge().getEdgeTargetVertex());								
			}

			adj = adj->getNext();
		}
	}

	*degreeList = d;
	return p;
}

Graph* Graph::GetTransposedGraph() {
	Graph* transpose = new Graph(m_NumberOfVertex);

	for (int i = 0; i < m_NumberOfVertex; i++) {				// for each vertex
		ListOfEdges& list = m_AdjList[i];
		ListOfEdges::EdgeNode* adj = list.getListHead();

		while (adj != nullptr) {								// go through all his edges
			int origin = adj->getEdge().getEdgeOriginVertex();
			int target = adj->getEdge().getEdgeTargetVertex();
			transpose->AddEdge(target, origin);					// add the oposite edge to the G tranpose
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
	// go through all the vertexes and delete each edge that degreeList[source] != degreeList[target] + 1
	ListOfEdges::EdgeNode* currentEdge = Gs->getEdgesListInIndex(i).getListHead();
	
		while (currentEdge != nullptr) {
			int v = currentEdge->getEdge().getEdgeTargetVertex();
			if(degreeList[v-1] != degreeList[i] + 1) {
				currentEdge = currentEdge->getNext();				// save the next edge before the deletion of the current edge
				Gs->RemoveEdge(i+1, v);
			}
			else {
				currentEdge = currentEdge->getNext();
			}
		}
	}

	Graph* GsTranspose = Gs->GetTransposedGraph(); // also Htranspose

	//delete p and d, and Gs
	delete Gs;
	delete[] degreeList;
	delete[] parentList;

	parentList = GsTranspose->BFS(i_ToVertex, &degreeList);

	for (int i = 0; i < GsTranspose->m_NumberOfVertex; i++) {			// for each vertex
		if(!checkIfParentOfVertex(parentList,i+1,i_ToVertex)) {			// if there isn't any path from the target vertex to the current vertex
			GsTranspose->m_AdjList[i].RemoveAllTheEdges();
		}
	}

	Graph* H = GsTranspose->GetTransposedGraph();						// this is the wanted graph

	delete[] degreeList;
	delete[] parentList;
	delete GsTranspose;

	return H;
}

bool Graph::checkIfParentOfVertex(int* parentList, int vertixToCheck, int parentToFind) {
	bool found = false;
	int currentParent = parentList[vertixToCheck - 1];

	if (vertixToCheck == parentToFind) {		// if the given vertex is the parent we want to find
		found = true;
	}

	while(!found && (currentParent != NO_PARENT)) {			// while there is a parent to the given vertex 
		if(currentParent == parentToFind) {					  //until we find the wanted parent
			found = true;
		}
		else {
			currentParent = parentList[currentParent - 1];	// update to the vertex parent
		}
	}

	return found;
}