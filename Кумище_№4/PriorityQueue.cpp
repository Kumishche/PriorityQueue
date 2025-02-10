#include "PriorityQueue.h"
#include <math.h>


PriorityQueue::PriorityQueue()
{
	N = reservedForPr;
	queue = new ElementOfQueue [N];
}

PriorityQueue::PriorityQueue(int numOfPriorities)
{
	N = numOfPriorities;
	queue = new ElementOfQueue [N];
}

PriorityQueue::PriorityQueue(int value, int priority)
{
	N = (reservedForPr >= priority) ? reservedForPr : priority;
	queue = new ElementOfQueue [N];
	queue[priority - 1].size = sizeOfQueue;
	queue[priority - 1].top = 0;
	queue[priority - 1].free = 1;
	queue[priority - 1].arr = new int[sizeOfQueue];
	queue[priority - 1].arr[0] = value;
}

PriorityQueue::PriorityQueue(PriorityQueue& other)
{
	N = other.N;
	queue = new ElementOfQueue [N];
	int cnt;

	for (int i = 0; i < N; i++)
	{
		queue[i] = other.queue[i];
	}
}

PriorityQueue::~PriorityQueue()
{
	for (int i = 0; i < N; i++)
		delete[] queue[i].arr;

	delete[] queue;
}

// добавление элемента с приоритетом
void PriorityQueue::add(int value, int priority)
{
	int id = priority - 1;

	if (priority < 1)
		return;
	else if (priority > N)
	{
		int newSize = (N * 2 > priority) ? N * 2 : priority;
		ElementOfQueue* newQueue = new ElementOfQueue[newSize];
		for (int i = 0; i < N; i++)
		{
			newQueue[i] = queue[i];
		}
		delete[] queue;
		N = newSize;
		queue = newQueue;
		newQueue = nullptr;
	}

	if (queue[id].size == 0)
	{
		queue[id].arr = new int[sizeOfQueue];
		queue[id].top = 0;
		queue[id].size = sizeOfQueue;
	}
	else if (queue[id].free == queue[id].top)
	{
		int* newArr = new int[queue[id].size * 2];
		int i;
		for (i = 0; i < queue[id].size; i++)
		{
			newArr[i] = queue[id].arr[(queue[id].top + i)%queue[id].size];
		}
		queue[id].free = queue[id].size;
		queue[id].size *= 2;
		delete[] queue[id].arr;
		queue[id].arr = newArr;
		newArr = nullptr;
	}
	
	queue[id].arr[queue[id].free] = value;
	if (queue[id].top == -1)
		queue[id].top = queue[id].free;
	queue[id].free = (queue[id].free + 1) % queue[id].size;
}

// извлечение элемента (с удалением из очереди)
bool PriorityQueue::get(int& value, int& priority)
{
	for (int i = 0; i < N; i++)
	{
		if (queue[i].top != -1)
		{
			value = queue[i].arr[queue[i].top];
			priority = i + 1;
			if ((queue[i].top + 1) % queue[i].size != queue[i].free)
				queue[i].top = (queue[i].top + 1) % queue[i].size;
			else
			{
				queue[i].top = -1;
				if (queue[i].size > sizeOfQueue)
				{
					delete[] queue[i].arr;
					queue[i].size = 0;
					queue[i].free = 0;
				}
			}
			return true;
		}
	}

	return false;
}

// число элементов (всего или с заданным приоритетом)
int PriorityQueue::count(int priority)
{
	int sum = 0;
	
	if (priority > N)
		return 0;

	if (priority != 0)
	{
		if (queue[priority - 1].top != -1)
		{
			if (queue[priority - 1].free <= queue[priority - 1].top)
				sum += queue[priority - 1].free + (queue[priority - 1].size - queue[priority - 1].top);
			else
				sum += queue[priority - 1].free - queue[priority - 1].top;
		}

		return sum;
	}

	for (int i = 0; i < N; i++)
	{
		if (queue[i].top != -1)
		{
			if (queue[i].free <= queue[i].top)
				sum += queue[i].free + (queue[i].size - queue[i].top);
			else
				sum += queue[i].free - queue[i].top;
		}
	}

	return sum;
}

// чтение элемента без удаления из очереди
bool PriorityQueue::peek(int& value, int& priority)
{
	for (int i = 0; i < N; i++)
	{
		if (queue[i].top != -1)
		{
			value = queue[i].arr[queue[i].top];
			priority = i + 1;
			return true;
		}
	}

	return false;
}

// Извлечение всех элементов с определенным приоритетом
// элементы копируются в buffer и удаляются из структуры данных
int PriorityQueue::get(int priority, int*& buffer)
{
	if (priority > N)
		return 0;

	int num = count(priority);
	int id = priority - 1;
	int cnt;
	delete[] buffer;
	
	if (queue[id].top != -1)
	{
		cnt = count(priority);
		buffer = new int[num];
		for (int i = 0; i < cnt; i++)
		{
			buffer[i] = queue[id].arr[(i + queue[i].top) % queue[id].size];
		}	
		delete[] queue[id].arr;
		queue[id].top = -1;
		queue[id].size = 0;
		queue[id].free = 0;

		return num;
	}

	return 0;
}

// проверка наличия элемента с учетом приоритета (priority > 0) или без
bool PriorityQueue::exist(int value, int priority)
{
	if (priority == 0)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < queue[i].size; j++)
			{
				if (queue[i].arr[j] == value)
					return true;
			}
		}
	}
	else if (priority > 0 && priority <= N)
	{
		int id = priority - 1;

		for (int j = 0; j < queue[id].size; j++)
		{
			if (queue[id].arr[j] == value)
				return true;
		}
	}

	return false;
}

// объединение двух очередей (без устранения повторов)
PriorityQueue& PriorityQueue::operator+(PriorityQueue& other)
{
	PriorityQueue* newQueue = new PriorityQueue(*this);
	int cnt;

	for (int i = 0; i < other.N; i++)
	{
		if (other.queue[i].top == -1) continue;

		cnt = other.count(i + 1);
		for (int j = 0; j < cnt; j++)
		{
			(*newQueue).add(other.queue[i].arr[(j + other.queue[i].top)
				% other.queue[i].size], i + 1);
		}
	}

	return (*newQueue);
}

// разность двух очередей (элементы с учетом приоритета отстутствуют в other)
PriorityQueue& PriorityQueue::operator-(PriorityQueue& other)
{
	PriorityQueue* newQueue = new PriorityQueue;

	int min_N = (N < other.N) ? N : other.N;
	bool flag = false;
	int cnt1;
	int cnt2;

	for (int i = 0; i < min_N; i++)
	{
		if (queue[i].top == -1) continue;

		cnt1 = count(i + 1);
		for (int j = 0; j < cnt1; j++)
		{
			if (other.queue[i].top != -1)
			{
				cnt2 = other.count(i + 1);
				for (int k = 0; k < cnt2; k++)
				{
					if (queue[i].arr[(j + queue[i].top) % queue[i].size] ==
						other.queue[i].arr[(k + other.queue[i].top) % other.queue[i].size])
					{
						flag = true;
						break;
					}
				}
			}

			if (!flag)
			{
				(*newQueue).add(queue[i].arr[(j + queue[i].top) 
					% queue[i].size], i + 1);
			}

			flag = false;
		}
	}

	if (min_N < N)
	{
		for (int i = min_N; i < N; i++)
		{
			if (queue[i].top == -1) continue;
			
			cnt1 = count(i + 1);
			for (int j = 0; j < cnt1; j++)
			{
				(*newQueue).add(queue[i].arr[(j + queue[i].top) 
					% queue[i].size], i + 1);
			}
		}
	}

	return *newQueue;
}

// пересечение двух приоритетных очередей (элементы с учетом приоритета есть в обеих структурах
// данных)
PriorityQueue& PriorityQueue::operator&(PriorityQueue& other)
{
	PriorityQueue* newQueue = new PriorityQueue;

	int min_N = (N < other.N) ? N : other.N;
	bool flag = false;
	int cnt1;
	int cnt2;

	for (int i = 0; i < min_N; i++)
	{
		if (queue[i].top == -1) continue;

		cnt1 = count(i + 1);
		for (int j = 0; j < cnt1; j++)
		{
			if (other.queue[i].top == -1) continue;

			cnt2 = other.count(i + 1);
			for (int k = 0; k < cnt2; k++)
			{
				if (queue[i].arr[(j + queue[i].top) % queue[i].size] ==
					other.queue[i].arr[(k+other.queue[i].top) % other.queue[i].size])
				{
					(*newQueue).add(queue[i].arr[(j + queue[i].top) 
						% queue[i].size], i + 1);
					break; 
				}
			}
		}
	}

	return *newQueue;
}

std::ostream& operator<<(std::ostream& os, PriorityQueue& q)
{
	int cnt;

	os << "Количество элементов: " << q.count() << std::endl;
	os << "-------" << std::endl;
	for (int i = 0; i < q.N; i++)
	{
		if (q.queue[i].top != -1)
		{
			cnt = q.count(i+1);
			os << "Приоритет: " << i + 1 << std::endl;
			for (int j = 0; j < cnt; j++)
			{
				os << q.queue[i].arr[(j+q.queue[i].top)%q.queue[i].size] 
					<< std::endl;
			}
			os << "-------" << std::endl;
		}
	}

	return os;
}

bool PriorityQueue::operator==(PriorityQueue& other)
{
	return !(*this != other);
}

bool PriorityQueue::operator!=(PriorityQueue& other)
{
	if (N != other.N) return true;

	for (int i = 0; i < N; i++)
	{
		if (count(i + 1) != other.count(i + 1))
			return true;
	}

	return false;
}

bool PriorityQueue::operator>(PriorityQueue& other)
{
	for (int i = 0; i < N; i++)
	{
		if (count(i + 1) > other.count(i + 1))
			return true;
		else if (count(i + 1) < other.count(i + 1))
			return false;
	}

	return false;
}

bool PriorityQueue::operator<(PriorityQueue& other)
{
	return !(*this > other) && *this != other;
}

bool PriorityQueue::operator>=(PriorityQueue& other)
{
	return *this > other || *this == other;
}

bool PriorityQueue::operator<=(PriorityQueue& other)
{
	return !(*this > other);
}

PriorityQueue& PriorityQueue::operator=(PriorityQueue& other)
{
	int cnt;

	if (this == &other) return *this;

	delete[] queue;

	N = other.N;
	queue = new ElementOfQueue[N];
	for (int i = 0; i < N; i++)
	{
		cnt = other.count(i + 1);
		queue[i].size = other.queue[i].size;
		queue[i].top = other.queue[i].top;
		queue[i].free = other.queue[i].free;
		if (queue[i].top == -1) continue;
		queue[i].arr = new int[queue[i].size];
		for (int j = 0; j < cnt; j++)
		{
			queue[i].arr[(j + queue[i].top)% queue[i].size] 
				= other.queue[i].arr[(j + queue[i].top) % queue[i].size];
		}
	}
}

///* Операторы сравнения двух структур данных ==, !=, >, <, >=, <=
// Сравнение по количеству элементов одного приоритета в обеих структурах
// Если совпадает наибольший приоритет в обеих структурах, проверяется число элементов наибольшего
//приоритета; если совпадает, проверяется следующий приоритет.
//*/