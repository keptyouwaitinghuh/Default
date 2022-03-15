#include "plist.h"

template<class T>
Nod<T>::Nod(T* data)
{
    this->data = *data;
}

template<class T>
void Nod<T>::operator=(Nod<T> value)
{
    data=value.data;
}

template<class T>
void Nod<T>::operator=(T value)
{
    data=value;
}

template<class T>
PList<T>::PList() : first(nullptr), last(nullptr), length(0) {}

template<class T>
PList<T>::~PList()
{
    while (first != nullptr)
        remove_first();
}

template<class T>
Nod<T>* PList<T>::getFirst()
{
    return first;
}

template<class T>
Nod<T>* PList<T>::getLast()
{
    return last;
}

template<class T>
void PList<T>::clear()
{
    while(first!=nullptr) remove_first();
}

template<class T>
void PList<T>::push_back(T* data)
{
    Nod<T>* tmp = new Nod<T>(data);

    if (is_empty())
    {
        tmp->next = nullptr;
        tmp->prev = nullptr;
        first = tmp;
        last = tmp;
    }
    else
    {
        last->next = tmp;
        tmp->prev = last;
        tmp->next = nullptr;
        last = tmp;
    }
    ++length;
}

template<class T>
bool PList<T>::is_empty()
{
    return first == nullptr;
}

template<class T>
void PList<T>::remove(Nod<T>* rmd)
{
    qDebug()<<"remove in";

    if (rmd == first)
    {
        remove_first();
    }

    else if (rmd == last)
    {
        qDebug() << "remove last";
        remove_last();
    }

    else
    {
        qDebug() << "remove mid in";
        Nod<T>* tmp = rmd->prev;
        tmp->next = rmd->next;
        rmd->next->prev=tmp;
        delete rmd;
    }
    --length;
    qDebug()<<"remove out";
}

template<class T>
bool PList<T>::remove(bool (*f)(Nod<T>* arg))
{
    if (is_empty()) return false;
    Nod<T>* ptr = first;
    while (ptr != nullptr && !f(ptr)) ptr = ptr->next;
    if(ptr != nullptr)
    {
        remove(ptr);
        return true;
    }
    else
        return false;
}

template<class T>
void PList<T>::remove_first()
{
    if (!is_empty())
    {
        if (length == 1)
        {
            delete first;
            first = nullptr;
            last = nullptr;
            length--;
            return;
        }
        Nod<T>* tmp = first->next;
        delete first;
        tmp->prev = nullptr;
        first = tmp;
        --length;
    }
}

template<class T>
void PList<T>::remove_last()
{
    qDebug() << "remove last in";
    if (!is_empty())
    {
        if (length == 1)
        {
            remove_first();
            return;
        }

        Nod<T>* tmp = last->prev;
        delete last;
        tmp->next = nullptr;
        last = tmp;
        --length;

    }
}

template<class T>
quint16 PList<T>::getLength()
{
    return length;
}

template<class T>
Nod<T>* PList<T>::operator[](unsigned int i)
{
    qDebug()<<'['<<i<<']';
    Nod<T>* ptr;
    if (length - 1 < i) return nullptr;
    unsigned short k = length - i - 1;
    if (k > length / 2)
    {
        ptr = first;
        while (i)
        {
            ptr = ptr->next;
            --i;
        }

    }
    else
    {
        ptr = last;
        while (k)
        {
            ptr = ptr->prev;
            --k;
        }
    }
    qDebug() <<"[out]";
    return ptr;
}

