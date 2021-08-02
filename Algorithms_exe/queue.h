#pragma once
#include <iostream>
using namespace std;

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


