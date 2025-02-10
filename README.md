## Практическая работа №4. 
# Разработка класса и переопределение операций

В работе необходимо разработать класс для работы с динамической структурой данных. В
реализации нельзя использовать готовые шаблонные классы (vector, map, set и т.п.). Программу
необходимо структурировать следующим образом:
- файл с определением класса (имя совпадает с названием структуры данных, например,
OrderedSet.h);
- файл с определениями функций-элементов класса (имя совпадает с названием структуры
данных, например, OrderedSet.cpp);
- файл с пользовательским меню (source.cpp).

Задачи.
1. Реализовать класс в соответствии с вариантом и в объявлении класса ввести:
 - закрытые поля;
 - конструкторы;
 - деструктор.
2. Реализовать корректное копирование объектов (конструктор копирования, операция
присваивания).
3. Реализовать базовую функциональность класса обозначенную ниже в таблице (функции для
добавления\извлечения элементов, объединение\пересечение для двух структур данных).
4. Реализовать операторы сравнения для двух структур данных (==, !=, >, <, >=, <=).
5. Реализовать возможность вывода на консоль структур данных через перегрузку оператора
сдвига.
6. Через консольное меню реализовать возможность взаимодействия с пользователем и проверки
функциональности класса.

## Вариант: PriorityQueue
Каждый элемент очереди (int) характеризуется приоритетом (int). Извлечение элементов
осуществляется с учётом приоритета и порядка: первым извлекается элемент, который имеет
наивысший приоритет; если есть несколько элементов с данным приоритетом, то извлекается
элемент, который был добавлен первым.

Обязательная функциональность:
* добавление элемента с приоритетом
void add(int value, int priority);
* извлечение элемента (с удалением из очереди)
bool get(int& value, int& priority);
* число элементов (всего или с заданным приоритетом)
int count(int priority = 0);
* чтение элемента без удаления из очереди
bool peek(int& value, int& priority);
* Извлечение всех элементов с определенным приоритетом
элементы копируются в buffer и удаляются из структуры данных
int get(int priority, int*& buffer);
* проверка наличия элемента с учетом приоритета (priority > 0) или без
bool exist(int value, int priority = 0);
* объединение двух очередей (без устранения повторов)
PriorityQueue operator+(const PriorityQueue& other);
* разность двух очередей (элементы с учетом приоритета отстутствуют в other)
PriorityQueue operator-(const PriorityQueue& other);
* пересечение двух приоритетных очередей (элементы с учетом приоритета есть в обеих структурах
данных)
PriorityQueue operator&(const PriorityQueue& other);
/* Операторы сравнения двух структур данных ==, !=, >, <, >=, <=
 Сравнение по количеству элементов одного приоритета в обеих структурах
 Если совпадает наибольший приоритет в обеих структурах, проверяется число элементов наибольшего
приоритета; если совпадает, проверяется следующий приоритет.
*/