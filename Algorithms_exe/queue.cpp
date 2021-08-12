#include "queue.h"

int Queue::AddOne(int x) {
	return ((1 + x) % m_PhSize);
}

Queue::Queue(int n) {
	m_Head = 1; 
	m_Tail = 0;
	m_PhSize = n;
	m_Queue = new int[n];
}

Queue::~Queue() {
	delete[] m_Queue;
}

void Queue::MakeEmpty() {
	m_Head = 1;
	m_Tail = 0;
}

bool Queue::isEmpty() {
	return (AddOne(m_Tail) == m_Head);
}

int Queue::Front() {
	
	if(isEmpty()) {
		throw 5;	// logic_error("There aren't any items in the queue.");
	}

	return m_Queue[m_Head];
}

void Queue::Enqueue(int vertexToInset) {
	
	if(AddOne(AddOne(m_Tail)) == m_Head){
		throw 5;	// length_error("The queue is full. Therefore the new item won't enter to the queue.");
	}

	m_Tail = AddOne(m_Tail);
	m_Queue[m_Tail] = vertexToInset;
}

int Queue::Dequeue() {
	
	if (isEmpty()) {
		throw 5;	// logic_error("There aren't any items in the queue.");
	}

	int item = m_Queue[m_Head];
	m_Head = AddOne(m_Head);

	return item;
}