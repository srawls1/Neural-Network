#ifndef VECTOR_H
#define VECTOR_H

#include "Types.h"

template<class T>
class Vector
{

    u32 sz, cap;
    T* data;

    void resize(u32 newCap);

public:

    Vector(u32 initCap = 8);
    Vector(Vector<T>& other);
    Vector(Vector<T>&& other);
    ~Vector();
    Vector<T>& operator=(Vector<T>& other);

    T& operator[](u32 index);
    void add(T t);
    void insertAt(T t, u32 index);
    void removeAt(u32 index);
    u32 size();

};

template<class T>
void Vector<T>::resize(u32 newCap)
{
    T* newData = new T[newCap];
    for (u32 i = 0; i < sz; ++i)
    {
        newData[i] = data[i];
    }
    cap = newCap;
    delete[] data;
    data = newData;
}

template<class T>
Vector<T>::Vector(u32 initCap)
{
    sz = 0;
    cap = initCap;
    data = new T[cap];
}

template<class T>
Vector<T>::Vector(Vector<T>& other)
{
    sz = other.sz;
    cap = other.cap;
    data = new T[cap];
    for (u32 i = 0; i < other.sz; ++i)
    {
        data[i] = other.data[i];
    }
}

template<class T>
Vector<T>::Vector(Vector<T>&& other)
{
    sz = other.sz;
    cap = other.cap;
    data = other.data;
    other.sz = 0;
    other.cap = 0;
    other.data = nullptr;
}

template<class T>
Vector<T>::~Vector()
{
    delete[] data;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>& other)
{
    delete[] data;
    sz = other.sz;
    cap = other.cap;
    data = new T[cap];
    for (u32 i = 0; i < other.sz; ++i)
    {
        data[i] = other.data[i];
    }
    return *this;
}

template<class T>
T& Vector<T>::operator[](u32 index)
{
    return data[index % sz];
}

template<class T>
void Vector<T>::add(T t)
{
    if (sz == cap)
    {
        resize(cap * 2);
    }
    data[sz++] = t;
}

template<class T>
void Vector<T>::insertAt(T t, u32 index)
{
    if (sz == cap)
    {
        resize(cap * 2);
    }
    for (u32 i = sz; i > index; --i)
    {
        data[i] = data[i - 1];
    }
    data[index] = t;
    ++sz;
}

template<class T>
void Vector<T>::removeAt(u32 index)
{
    for (u32 i = index; i < sz - 1; ++i)
    {
        data[i] = data[i + 1];
    }
    --sz;
}

template<class T>
u32 Vector<T>::size()
{
    return sz;
}

#endif
