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

class Object
{
public:
    Object()
    {
        cout << "Real Human Bean" << endl;
    }

    void live()
    {
        cout << "Lifetime" << endl;
    }

    ~Object()
    {
        cout << "Dead Human Bean" << endl;
    }
};

template <typename T>
class SmartProxy
{
private:
    T *obj_this;
    int *obj_links;

public:
    SmartProxy(T *ptr = NULL)
    {
        obj_this = ptr;
        obj_links = new int;
        *obj_links = 1;
    }

    SmartProxy(SmartProxy<T> &o)
    {
        obj_this = o.obj_this;
        obj_links = o.obj_links;
        (*obj_links)++;
        cout << "+1 ссылка на объект" << endl;
    }

    ~SmartProxy()
    {
        free();
    }

    SmartProxy<T>& operator =(SmartProxy &o)
    {
        if (&o != this)
        {
            free();
            obj_this = o.obj_this;
            obj_links = o.obj_links;
            (*obj_links)++;
            cout << "+1 ссылка на объект" << endl;
        }
        return *this;
    }

    T* operator->()
    {
        return obj_this;
    }

    T& operator *()
    {
        return *obj_this;
    }

    int getLinks()
    {
        return *obj_links;
    }

    void free()
    {
        if(!--(*obj_links))
        {
            cout << "Объект не имеет ссылок." << endl;
            delete obj_links;
            obj_links=NULL;
            if(obj_this)
            {
                cout << "Удаляем объект." << endl;
                delete obj_this;
                obj_this=NULL;
            }
        }
    }
};

typedef SmartProxy<Object> ptr_t;

int main()
{
    ptr_t test_ptr1(new Object);
    cout << test_ptr1.getLinks() << endl;
    ptr_t test_ptr2=test_ptr1;
    test_ptr2->live();
    cout << test_ptr2.getLinks() << endl;
    ptr_t test_ptr3=test_ptr1;
    cout << test_ptr3.getLinks() << endl;
    ptr_t test_ptr4(test_ptr1);
    cout << test_ptr4.getLinks() << endl;

    cout << endl << "Запилим ещё один новый объект:" << endl << endl;
    {
        ptr_t t1(new Object);
        ptr_t t2=t1;
        cout << t2.getLinks() << endl;
    }
    cout << endl << "Объект уничтожен!" << endl << endl;

    return 0;
}
