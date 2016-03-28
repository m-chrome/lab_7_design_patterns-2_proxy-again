/*
 * Вариант 6
 *
 * Используя паттерн Proxy, реализовать «умный» указатель
 * для объектов шаблонного класса. Необходимо реализовать
 * подсчет числа ссылок на реальный объект. При отсутствии
 * ссылок память под объект автоматически освобождается.
 */

#include <iostream>

using namespace std;

template <typename T>
class SmartProxy
{
private:
    T *obj;
    int thisLink;
    static int links;
public:
    SmartProxy()
    {
        //thisLink=links++;
        obj = 0;
    }
    ~SmartProxy()
    {
        --links;
        delete obj;
    }

    void createPtr()
    {
        if (!obj)
        {
            cout << "Создадим real human being" << endl;
            obj = new T;
        }
        thisLink=++links;
    }

    void showLinks()
    {
        cout << "Links: " << links << endl;
    }
};

template <typename T>
int SmartProxy<T> ::links=0;

int main()
{
    int *i = new int;
    *i = 42;
    SmartProxy<int> *ptr1 = new SmartProxy<int>;
    SmartProxy<int> *ptr2 = new SmartProxy<int>;
    SmartProxy<int> *ptr3 = new SmartProxy<int>;
    ptr1->createPtr();
    ptr2->createPtr();
    ptr3->createPtr();
    ptr1->showLinks();
    cout << "Delete!" << endl;
    delete ptr3;
    ptr1->showLinks();
    delete ptr2;
    ptr1->showLinks();
    delete ptr1;

    return 0;
}

