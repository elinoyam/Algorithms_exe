#include "listOfEdges.h"
using namespace std;

ListOfEdges::ListOfEdges(const ListOfEdges& other) {
	ListOfEdges::EdgeNode *edge = other.m_ListHead;
	for (int i = 0; i < other.m_NumberOfEdgesInList; i++) {
		this->addEdgeToTail(edge->getEdge());
		edge = edge->getNext();
	}
}

ListOfEdges::~ListOfEdges() {
	ListOfEdges::EdgeNode* toDelete = m_ListHead;
	ListOfEdges::EdgeNode* saveBeforeDelete;
	while (toDelete != nullptr) {
		saveBeforeDelete = toDelete->getNext();			// save the next edge in the list
		delete toDelete;
		toDelete = saveBeforeDelete;
	}
}


ListOfEdges::EdgeNode* ListOfEdges::addEdgeToTail(Edge& i_EdgeToAdd) {
	ListOfEdges::EdgeNode* newTail = new ListOfEdges::EdgeNode(i_EdgeToAdd, nullptr);

	if (isEmpty()) //first link
		this->m_ListHead = this->m_ListTail = newTail;
	else
	{
		this->m_ListTail->setNext(newTail);
		this->m_ListTail = newTail;
	}
	m_NumberOfEdgesInList++;

	return newTail;
}


ListOfEdges::EdgeNode* ListOfEdges::addEdgeToTail(int i_OriginVertex, int i_TargetVertex, int i_EdgeWeight) {
	Edge edge(i_OriginVertex, i_TargetVertex, i_EdgeWeight);
	return ListOfEdges::addEdgeToTail(edge);
}

void ListOfEdges::printList() {
	ListOfEdges::EdgeNode* currentNode = this->m_ListHead;

	while (currentNode != nullptr)
	{
		cout << currentNode->getEdge(); // need to do print operator
		currentNode = currentNode->getNext();
	}
	cout << endl;
}

void ListOfEdges::RemoveEdge(int i_Adjacent) {
	bool found = false;
	ListOfEdges::EdgeNode* currentNode = m_ListHead;

	if (currentNode->getEdge().getEdgeTargetVertex() == i_Adjacent) {					// the edge we want to remove is at the start of the list
		m_ListHead = currentNode->getNext();
		if (m_ListHead == nullptr) {
			m_ListTail = nullptr;
		}
		delete currentNode;
		found = true;
	}
	while (!found && currentNode != nullptr && currentNode->getNext() != nullptr ) {
		if (currentNode->getNext()->getEdge().getEdgeTargetVertex() == i_Adjacent) { 	// the edge we want to remove is at the middle of the list
			ListOfEdges::EdgeNode* toDelete = currentNode->getNext();
			currentNode->setNext(toDelete->getNext());
			delete toDelete;
			found = true;
		}
	}
	if (!found && m_ListTail->getEdge().getEdgeTargetVertex() == i_Adjacent) {			// the edge we want to remove is at the end of the list
		ListOfEdges::EdgeNode* toDelete = m_ListTail;
		currentNode->setNext(nullptr);
		delete toDelete;
		m_ListTail = currentNode;
		found = true;
	}
	if (!found)
		throw invalid_argument("The given vertex is not in the graph. Therefore no vertex as been deleted.");
}