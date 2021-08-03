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

	private: int AddOne(int x);

	public:	Queue(int n);
	public:	~Queue();
	public:	void MakeEmpty();
	public:	bool isEmpty();
	public:	int Front();
	public:	void Enqueue(int vertexToInset);
	public:	int Dequeue();
};