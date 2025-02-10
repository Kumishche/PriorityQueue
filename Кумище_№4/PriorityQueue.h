#pragma once
#include <iostream>

class PriorityQueue
{
private:
	const int reservedForPr = 5;
	const int sizeOfQueue = 3;

	struct ElementOfQueue
	{
		int size;
		int top;
		int free;
		int* arr;

		ElementOfQueue()
		{
			size = 0;
			top = -1;
			free = 0;
			arr = nullptr;
		}

		void operator=(const ElementOfQueue& other)
		{
			size = other.size;
			top = other.top;
			free = other.free;
			delete[] arr;
			arr = new int[size];
			for (int i = 0; i < size; i++)
			{
				arr[i] = other.arr[i];
			}
		}
	};

	int N;  
	ElementOfQueue* queue;

public:
	PriorityQueue();
	PriorityQueue(int numOfPriorities);
	PriorityQueue(int value, int priority);
	PriorityQueue(PriorityQueue& other);
	~PriorityQueue();

	void add(int value, int priority);
	bool get(int& value, int& priority);
	int count(int priority = 0);
	bool peek(int& value, int& priority);
	int get(int priority, int*& buffer);
	bool exist(int value, int priority = 0);
	
	PriorityQueue& operator+(PriorityQueue& other);
	PriorityQueue& operator-(PriorityQueue& other);
	PriorityQueue& operator&(PriorityQueue& other);

	friend std::ostream& operator<<(std::ostream& os, PriorityQueue& q);

	bool operator==(PriorityQueue& other);
	bool operator!=(PriorityQueue& other);
	bool operator>(PriorityQueue& other);
	bool operator<(PriorityQueue& other);
	bool operator>=(PriorityQueue& other);
	bool operator<=(PriorityQueue& other);

	PriorityQueue& operator=(PriorityQueue& other);
};