// Кумище_№4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "Tests.h"
#include "PriorityQueue.h"

using namespace std;

void CheckInput(int& var);
void InputIdOfQueue(int& var, int size);
void InputPriority(int& var);


int main()
{
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    //---------------

    int V = abs(int('K') * int('R')) % 6;
    cout << "Вариант: " << V << endl;
    cout << setw(40) << setfill('=') << ' ' << endl; 
    //---------------

    int s;
    int c;
    int v = -1, p = -1;
    int numOfPr = 0;
    int* buffer = nullptr;
    int sizeOfBuffer = 0;

    const int size = 2;
    PriorityQueue* PQueue[size];
    PQueue[0] = nullptr;
    PQueue[1] = nullptr;

    while (true)
    {
        cout << "Приоритетная очередь" << endl;
        cout << setw(20) << setfill('-') << ' ' << endl;
        cout << "Выберите действие: " << endl;
        cout << "1 - создать новую очередь по умолчанию" << endl;
        cout << "2 - создать очередь с указанным количество приоритетов" << endl;
        cout << "3 - создать очередь с первым заданным элементом" << endl;
        cout << setw(20) << setfill('-') << ' ' << endl;
        cout << "4 - добавить элемент в очередь" << endl;
        cout << "5 - достать элемент из очереди" << endl;
        cout << "6 - посмотреть элемент из очереди" << endl;
        cout << "7 - вывести все элементы очереди указанного приоритета" << endl;
        cout << setw(20) << setfill('-') << ' ' << endl;
        cout << "8 - посмотреть наличие элемента" << endl;
        cout << "9 - вывести количество элементов очереди" << endl;
        cout << setw(20) << setfill('-') << ' ' << endl;
        cout << "10 - сложить очереди 1 и 2" << endl;
        cout << "11 - вычесть из очереди 1 очередь 2" << endl;
        cout << "12 - пересечь очереди 1 и 2" << endl;
        cout << "13 - сравнить очереди" << endl;
        cout << "14 - скопировать очередь 2 в очередь 1" << endl;
        cout << setw(20) << setfill('-') << ' ' << endl;
        cout << "15 - вывести очередь на экран" << endl;
        cout << setw(20) << setfill('-') << ' ' << endl;
        cout << "16 - автоматическое тестирование" << endl;
        cout << setw(20) << setfill('-') << ' ' << endl;
        cout << "17 - выйти" << endl;
        cout << setw(40) << setfill('=') << ' ' << endl;

        cout << "Введите символ: ";
        cin >> s;
        CheckInput(s);

        switch (s)
        {
        case 1:
            InputIdOfQueue(c, size);
            delete PQueue[c-1];
            PQueue[c-1] = new PriorityQueue;
            cout << "Очередь создана" << endl;
            break;

        case 2:
            InputIdOfQueue(c, size);
            cout << "Введите количество приоритетов: ";
            InputPriority(numOfPr);
            delete PQueue[c-1];
            PQueue[c-1] = new PriorityQueue(numOfPr);
            cout << "Очередь создана" << endl;
            break;

        case 3:
            InputIdOfQueue(c, size);
            cout << "Введите приоритет элемента: ";
            InputPriority(p);
            cout << endl;
            cout << "Введите значение элемента: ";
            cin >> v;
            CheckInput(v);
            delete PQueue[c-1];
            PQueue[c-1] = new PriorityQueue(v, p);
            cout << "Очередь создана" << endl;
            break;

        case 4:
            InputIdOfQueue(c, size);
            if (PQueue[c-1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            cout << "Введите приоритет элемента: ";
            InputPriority(p);
            cout << endl;
            cout << "Введите значение элемента: ";
            cin >> v;
            CheckInput(v);
            PQueue[c-1]->add(v, p);
            cout << "Значение добавлено" << endl;
            break;

        case 5:
            InputIdOfQueue(c, size);
            if (PQueue[c-1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            if (PQueue[c-1]->get(v, p))
            {
                cout << "Приоритет: " << p << endl;
                cout << "Значение: " << v << endl;
            }
            else
                cout << "Очередь пуста" << endl;
            break;

        case 6:
            InputIdOfQueue(c, size);
            if (PQueue[c-1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            if (PQueue[c-1]->peek(v, p))
            {
                cout << "Приоритет: " << p << endl;
                cout << "Значение: " << v << endl;
            }
            else
                cout << "Очередь пуста" << endl;
            break;

        case 7:
            InputIdOfQueue(c, size);
            if (PQueue[c-1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            cout << "Введите приоритет: ";
            InputPriority(p);
            sizeOfBuffer = PQueue[c-1]->get(p, buffer);
            cout << "Элементы скопированы в buffer" << endl;
            cout << "Вывод buffer: " << endl;
            for (int i = 0; i < sizeOfBuffer; i++)
            {
                cout << "Элемент " << i + 1 << ": " << buffer[i] << endl;
            }
            cout << endl;
            break;

        case 8:
            InputIdOfQueue(c, size);
            if (PQueue[c-1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            cout << "Введите приоритет элемента (0 - приоритета нет): ";
            cin >> p;
            CheckInput(p);
            while (p < 0)
            {
                cout << "Некорректный ввод" << endl;
                cout << "Повторите ввод: ";
                cin >> p;
                CheckInput(p);
            }
            cout << endl;
            cout << "Введите значение элемента: ";
            cin >> v;
            CheckInput(v);
            if (PQueue[c-1]->exist(v, p))
                cout << "Элемент есть" << endl;
            else
                cout << "Элемента нет" << endl;
            break;

        case 9:
            InputIdOfQueue(c, size);
            if (PQueue[c-1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            cout << "Введите приоритет элемента (0 - приоритета нет): ";
            cin >> p;
            CheckInput(p);
            while (p < 0)
            {
                cout << "Некорректный ввод" << endl;
                cout << "Повторите ввод: ";
                cin >> p;
                CheckInput(p);
            }
            cout << "Количество элементов: " << PQueue[c-1]->count(p) << endl;
            break;
            
        case 10:
            if (PQueue[0] == nullptr || PQueue[1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            cout << (*(PQueue[0]) + *(PQueue[1])) << endl;
            break;
            
        case 11:
            if (PQueue[0] == nullptr || PQueue[1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            cout << (*(PQueue[0]) - *(PQueue[1])) << endl;
            break;

        case 12:
            if (PQueue[0] == nullptr || PQueue[1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            cout << (*(PQueue[0]) & *(PQueue[1])) << endl;
            break;

        case 13:
            if (PQueue[0] == nullptr || PQueue[1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            cout << (*(PQueue[0]) == *(PQueue[1])) << endl;
            break;

        case 14:
            if (PQueue[0] == nullptr || PQueue[1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            *(PQueue[0]) = *(PQueue[1]);
            cout << PQueue[0];
            break;

        case 15:
            InputIdOfQueue(c, size);
            if (PQueue[c-1] == nullptr)
            {
                cout << "Очередь не создана" << endl;
                break;
            }
            cout << "Очередь: " << endl;
            cout << *PQueue[c-1] << endl;
            break;

        case 16:
            FullTest();
            break;

        case 17:
            return 0;

        default:           
            cout << "Некорректный ввод" << endl;
        }

        cout << setw(40) << setfill('=') << "" << endl;
        cout << endl;
    }
}

void CheckInput(int& var)
{
    while (cin.fail() || cin.get() != '\n')
    {
        cin.clear(); cin.ignore(256, '\n');
        cout << "Некорректный ввод" << endl;
        cout << "Повторите ввод: ";
        cin >> var;
    }
}

void InputIdOfQueue(int& var, int size)
{
    cout << "Введите номер очереди (1 - " << size << "): ";
    cin >> var;
    CheckInput(var);
    while (var < 1 || var > size)
    {
        cout << "Некорректный ввод" << endl;
        cout << "Повторите ввод: ";
        cin >> var;
        CheckInput(var);
    }
}

void InputPriority(int& var)
{
    cin >> var;
    CheckInput(var);
    while (var < 1)
    {
        cout << "Некорректный ввод" << endl;
        cout << "Повторите ввод: ";
        cin >> var;
        CheckInput(var);
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
