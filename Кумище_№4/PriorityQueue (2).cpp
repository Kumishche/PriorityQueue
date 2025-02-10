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
	// Вопрос с выделением памяти для динамики
	queue[priority - 1].size = sizeOfQueue;
	queue[priority - 1].top = 0;
	queue[priority - 1].free = 1;
	queue[priority - 1].arr = new int[sizeOfQueue];
	queue[priority - 1].arr[0] = value;
}

PriorityQueue::PriorityQueue(PriorityQueue& other)
{
	//Вопрос с доступом к private N
	N = other.N;
	queue = new ElementOfQueue [N];
	for (int i = 0; i < N; i++)
	{
		queue[i].size = other.queue[i].size;
		queue[i].top = other.queue[i].top;
		queue[i].free = other.queue[i].free;
		queue[i].arr = new int[other.queue[i].size];
		for (int j = 0; j < queue[i].size; j++)
		{
			queue[i].arr[j] = other.queue[i].arr[j];
		}
	}

}

PriorityQueue::~PriorityQueue()
{
	/*for (int i = 0; i < N; i++)
	{
		delete queue[i];
	}*/
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
		for (int i = 0; i < queue[id].size; i++)
		{
			newArr[i] = queue[id].arr[i];
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
	delete[] buffer;
	buffer = new int[num];

	if (queue[id].top != -1)
	{
		for (int i = queue[id].top; i % queue[id].size != queue[id].free; i++)
		{
			buffer[i-queue[id].top] = queue[id].arr[i % queue[id].size];
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
	int cnt = 0;

	if (priority == 0)
	{
		for (int i = 0; i < N; i++)
		{
			cnt = count(i + 1);
			for (int j = 0; j < cnt; j++)
			{
				if (queue[i].arr[(queue[i].top + j) % queue[i].size] == value)
					return true;
			}
		}
	}
	else if (priority > 0 && priority <= N)
	{
		int id = priority - 1;
		cnt = count(id + 1);

		for (int j = 0; j < cnt; j++)
		{
			if (queue[id].arr[(queue[id].top + j) % queue[id].size] == value)
				return true;
		}
	}

	return false;
}

// объединение двух очередей (без устранения повторов)
PriorityQueue PriorityQueue::operator+(const PriorityQueue& other)
{
	PriorityQueue newQueue;

	for (int i = 0; i < other.N; i++)
	{
		if (other.queue[i].top == -1) continue;

		for (int j = other.queue[i].top; j % other.queue[i].size != other.queue[i].free; j++)
		{
			newQueue.add(other.queue[i].arr[j % other.queue[i].size], i + 1);
		}
	}

	return newQueue;
}

// разность двух очередей (элементы с учетом приоритета отстутствуют в other)
PriorityQueue PriorityQueue::operator-(const PriorityQueue& other)
{
	PriorityQueue newQueue;

	int min_N = (N < other.N) ? N : other.N;
	bool flag = false;
	/*int count_this = 0;
	int count_other = 0;*/

	for (int i = 0; i < min_N; i++)
	{
		for (int j = queue[i].top; j % queue[i].size != queue[i].size; j++)
		{
			if (other.queue[i].top == -1) continue;

			/*if (other.queue[i].free < other.queue[i].top)
				count_other += other.queue[i].free + (other.queue[i].size - other.queue[i].top);
			else
				count_other += other.queue[i].free - other.queue[i].top;*/

			for (int k = other.queue[i].top; 
				k % other.queue[i].size != other.queue[i].free; k++)
			{
				if (queue[i].arr[j % queue[i].size] == 
					other.queue[i].arr[k % other.queue[i].size])
				{
					flag = true;
					break;
				}
			}

			if (!flag)
			{
				newQueue.add(queue[i].arr[j % queue[i].size], i + 1);
			}

			flag = false;
		}
	}

	if (min_N < N)
	{
		for (int i = min_N; i < N; i++)
		{
			for (int j = queue[i].top; j % queue[i].size != queue[i].free; j++)
			{
				newQueue.add(queue[i].arr[j % queue[i].size], i + 1);
			}
		}
	}

	return newQueue;
}

// пересечение двух приоритетных очередей (элементы с учетом приоритета есть в обеих структурах
// данных)
PriorityQueue PriorityQueue::operator&(const PriorityQueue& other)
{
	PriorityQueue newQueue;

	int min_N = (N < other.N) ? N : other.N;
	bool flag = false;

	for (int i = 0; i < min_N; i++)
	{
		for (int j = queue[i].top; j % queue[i].size != queue[i].free; j++)
		{
			if (other.queue[i].top == -1) continue;

			for (int k = other.queue[i].top;
				k % other.queue[i].size != other.queue[i].free; k++)
			{
				if (queue[i].arr[j % queue[i].size] == other.queue[i].arr[k % other.queue[i].size])
				{
					newQueue.add(queue[i].arr[j % queue[i].size], i + 1);
					break; 
				}
			}
		}
	}

	return newQueue;
}

std::ostream& operator <<(std::ostream& os, PriorityQueue& q)
{
	int v = -1, p = -1;

	os << "Количество элементов: " << q.count() << std::endl;
	q.peek(v, p);
	os << "Первый элемент: приоритет " << p << ", значение " << v << std::endl;
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
	
}

bool PriorityQueue::operator<(PriorityQueue& other)
{

}

PriorityQueue PriorityQueue::operator=(const PriorityQueue& other)
{

}

///* Операторы сравнения двух структур данных ==, !=, >, <, >=, <=
// Сравнение по количеству элементов одного приоритета в обеих структурах
// Если совпадает наибольший приоритет в обеих структурах, проверяется число элементов наибольшего
//приоритета; если совпадает, проверяется следующий приоритет.
//*/