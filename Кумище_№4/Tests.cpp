#include "Tests.h"
#include "PriorityQueue.h"
#include <iostream>

using namespace std;

void FullTest()
{
	PriorityQueue q1;
	PriorityQueue q2(3);
	cout << "Создание пустой очереди q1: " << endl;
	cout << "q1: " << endl;
	cout << q1 << endl;
	cout << "----------------" << endl;

	q1.add(1, 1);
	q1.add(12412, 1);
	q1.add(0, 99);
	cout << "Добавление элементов в q1: " << endl;
	cout << "q1: " << endl;
	cout << q1 << endl;
	cout << "----------------" << endl;

	cout << "Создание очереди с определенным числом приоритетов q2: " << endl;
	cout << "q2: " << endl;
	cout << q2 << endl;
	cout << "----------------" << endl;

	q2.add(1, 199);
	cout << "Добавление нового приоритета в q2: " << endl;
	cout << "q2: " << endl;
	cout << q2 << endl;
	cout << "----------------" << endl;

	PriorityQueue q3(q1);
	cout << "Использование конструктора копирования для q3: " << endl;
	cout << "q3: " << endl;
	cout << q3 << endl;
	cout << "----------------" << endl;

	int v, p;
	cout << "Получение элемента q1: " << endl;
	q1.get(v, p);
	cout << "Значение " << v << ", приоритет " << p << endl;
	cout << "----------------" << endl;
	cout << "q1: " << endl;
	cout << q1 << endl;
	cout << "----------------" << endl;

	q3.get(v, p);
	cout << "Получение элемента q3: " << endl;
	cout << "Значение " << v << ", приоритет " << p << endl;
	q2.peek(v, p);
	cout << "----------------" << endl;

	cout << "Получение элемента q2 без удаления: " << endl;
	cout << "Значение " << v << ", приоритет " << p << endl;
	cout << "q2: " << endl;
	cout << q2 << endl;
	cout << "----------------" << endl;

	cout << "Количество элементов q1: " << endl;
	cout << q1.count() << endl;
	cout << "----------------" << endl;

	q2.add(1, 12); q2.add(2, 12); q2.add(3, 12);
	q2.peek(v, p); q2.get(v, p); q2.add(4, 12);
	cout << "Добавление 3х элементов, изъятие одного и добавление еще одного в q2: " << endl;
	cout << q2.count(12) << endl;
	cout << "q2: " << endl;
	cout << q2 << endl;
	cout << "----------------" << endl;

	cout << "Проверка существования элемента \"4\" в q2 : " << endl;
	cout << q2.exist(4) << endl;
	cout << "----------------" << endl;

	q2.add(12345, 1);
	cout << "Проверка существования элемента \"12345\" с приоритетом 1 в q2 : " << endl;
	cout << q2.exist(12345, 1) << endl;
	cout << "q2: " << endl;
	cout << q2 << endl;
	cout << "----------------" << endl;

	q1.add(12345, 1);
	q1.add(2, 12);
	q1.add(0, 9);
	cout << endl << endl;
	cout << "q1: " << endl;
	cout << q1 << endl;
	cout << "q2: " << endl;
	cout << q2 << endl;

	cout << "Сложение q1 и q2: " << endl;
	PriorityQueue q_res = (q1 + q2);
	cout << q_res << endl;
	cout << "----------------" << endl;

	cout << "Вычитание q1 из q2: " << endl;
	q_res = q1 - q2;
	cout << q_res << endl;
	cout << "----------------" << endl;

	cout << "Пересечение q1 и q2: " << endl;
	q_res = q1 & q2;
	cout << q_res << endl;
	cout << "----------------" << endl;

	cout << "Равенство q1 и q2: " << endl;
	cout << (q2 == q1) << endl;
	cout << "----------------" << endl;

	cout << "Неравенство q1 и q2: " << endl;
	cout << (q2 != q1) << endl;
	cout << "----------------" << endl;

	cout << "q2 >= q1: " << endl;
	cout << (q2 >= q1) << endl;
	cout << "----------------" << endl;

	cout << "q2 <= q1: " << endl;
	cout << (q2 <= q1) << endl;
	cout << "----------------" << endl;

	cout << "q2 > q1: " << endl;
	cout << (q2 > q1) << endl;
	cout << "----------------" << endl;

	cout << "q2 < q1: " << endl;
	cout << (q2 < q1) << endl;
	cout << "----------------" << endl;

	cout << "q1 = q2: " << endl;
	q1 = q2;
	cout << "q1: " << endl;
	cout << q1 << endl;
	cout << "----------------" << endl;

	cout << "Добавление элемента в q2: " << endl;
	q2.add(999, 999);
	cout << "q2: " << endl;
	cout << q2 << endl;
	cout << "q1: " << endl;
	cout << q1 << endl;
	cout << "----------------" << endl;
}

