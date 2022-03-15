#ifndef PLIST_H
#define PLIST_H
#include <QtGlobal>
#include <QtDebug>

template <class T> struct Nod
{
    T data;
    Nod<T>* next;
    Nod<T>* prev;

    Nod(T* data);
    void operator= (Nod<T> value);
    void operator= (T value);
};



template <class T> class PList
{
    Nod<T>* first;
    Nod<T>* last;
    quint16 length;

public:
    PList();
    ~PList();

    void push_back(T* data);
    bool is_empty();

    bool remove(bool (*f)(Nod<T>* arg));
    void remove_first();
    void remove_last();
    void remove(Nod<T>* rmd);

    quint16 getLength();
    Nod<T>* getFirst();
    Nod<T>* getLast();
    void clear();

    Nod<T>* operator[] (unsigned int index);

};



#endif // PLIST_H
