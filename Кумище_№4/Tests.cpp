#include "Tests.h"
#include "PriorityQueue.h"
#include <iostream>

using namespace std;

void FullTest()
{
	PriorityQueue q1;
	PriorityQueue q2(3);
	cout << "�������� ������ ������� q1: " << endl;
	cout << "q1: " << endl;
	cout << q1 << endl;
	cout << "----------------" << endl;

	q1.add(1, 1);
	q1.add(12412, 1);
	q1.add(0, 99);
	cout << "���������� ��������� � q1: " << endl;
	cout << "q1: " << endl;
	cout << q1 << endl;
	cout << "----------------" << endl;

	cout << "�������� ������� � ������������ ������ ����������� q2: " << endl;
	cout << "q2: " << endl;
	cout << q2 << endl;
	cout << "----------------" << endl;

	q2.add(1, 199);
	cout << "���������� ������ ���������� � q2: " << endl;
	cout << "q2: " << endl;
	cout << q2 << endl;
	cout << "----------------" << endl;

	PriorityQueue q3(q1);
	cout << "������������� ������������ ����������� ��� q3: " << endl;
	cout << "q3: " << endl;
	cout << q3 << endl;
	cout << "----------------" << endl;

	int v, p;
	cout << "��������� �������� q1: " << endl;
	q1.get(v, p);
	cout << "�������� " << v << ", ��������� " << p << endl;
	cout << "----------------" << endl;
	cout << "q1: " << endl;
	cout << q1 << endl;
	cout << "----------------" << endl;

	q3.get(v, p);
	cout << "��������� �������� q3: " << endl;
	cout << "�������� " << v << ", ��������� " << p << endl;
	q2.peek(v, p);
	cout << "----------------" << endl;

	cout << "��������� �������� q2 ��� ��������: " << endl;
	cout << "�������� " << v << ", ��������� " << p << endl;
	cout << "q2: " << endl;
	cout << q2 << endl;
	cout << "----------------" << endl;

	cout << "���������� ��������� q1: " << endl;
	cout << q1.count() << endl;
	cout << "----------------" << endl;

	q2.add(1, 12); q2.add(2, 12); q2.add(3, 12);
	q2.peek(v, p); q2.get(v, p); q2.add(4, 12);
	cout << "���������� 3� ���������, ������� ������ � ���������� ��� ������ � q2: " << endl;
	cout << q2.count(12) << endl;
	cout << "q2: " << endl;
	cout << q2 << endl;
	cout << "----------------" << endl;

	cout << "�������� ������������� �������� \"4\" � q2 : " << endl;
	cout << q2.exist(4) << endl;
	cout << "----------------" << endl;

	q2.add(12345, 1);
	cout << "�������� ������������� �������� \"12345\" � ����������� 1 � q2 : " << endl;
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

	cout << "�������� q1 � q2: " << endl;
	PriorityQueue q_res = (q1 + q2);
	cout << q_res << endl;
	cout << "----------------" << endl;

	cout << "��������� q1 �� q2: " << endl;
	q_res = q1 - q2;
	cout << q_res << endl;
	cout << "----------------" << endl;

	cout << "����������� q1 � q2: " << endl;
	q_res = q1 & q2;
	cout << q_res << endl;
	cout << "----------------" << endl;

	cout << "��������� q1 � q2: " << endl;
	cout << (q2 == q1) << endl;
	cout << "----------------" << endl;

	cout << "����������� q1 � q2: " << endl;
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

	cout << "���������� �������� � q2: " << endl;
	q2.add(999, 999);
	cout << "q2: " << endl;
	cout << q2 << endl;
	cout << "q1: " << endl;
	cout << q1 << endl;
	cout << "----------------" << endl;
}

