#pragma once
#include <iostream>
using namespace std;

/*************** FUNCTION DECLARATIONS ***************
* This class represents a queue,
* The data structure is a static array.
* It is needed to set the phisical size in the ctor.
*****************************************************/

class Queue
{
	private: int m_Head;
	private: int m_Tail;
	private: int m_PhSize;
	private: int* m_Queue;

			// This method makes the code be more readable
			// This method recieve an int number
			// This method returns the number + 1 
	private: int AddOne(int x);

			// This is the ctor of the class
			// This method recieve an int number, the size of the queue
	public:	Queue(int n);

			// This is the dtor of the class
			// This method delete the memory of the queue
	public:	~Queue();

			// This method init the queue
	public:	void MakeEmpty();

			// This method checks if the queue is empty
			// This method returns true if it is empty, else flase
	public:	bool isEmpty();

			// This method returns the first element of the queue without removing it
	public:	int Front();

			// This method receive an int number representing an vertix
			// This method adds that vertex to the queue
	public:	void Enqueue(int vertexToInset);

			// This method returns the first element of the queue, and remove it from the queue
	public:	int Dequeue();
};