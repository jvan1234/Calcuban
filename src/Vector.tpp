#include "Vector.hpp"

template <typename T>
Vector<T>::Vector(int capacity) {
    this->capacity = capacity;
    this->data = new T[capacity];
    this->size = 0;
}

template <typename T>
Vector<T>::~Vector()
{
    if (data) delete[] data;
}

template <typename T>
bool Vector<T>::full() const {
    return size == capacity;
}

template <typename T>
bool Vector<T>::empty() const {
    return size == 0;
}

template <typename T>
void Vector<T>::allocateMemory(int new_capacity)
{
    capacity = new_capacity;
    T* old_data = data;
    data = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        data[i] = old_data[i];
    }
    delete[] old_data;
}

template <typename T>
void Vector<T>::push_back(const T& val) {
    if (full()) allocateMemory(capacity * 2);
    data[size] = val;
    size++;
}

template <typename T>
T Vector<T>::at(int i) const
{
    if (i > size || i < 0)
    {
        return nullptr;
    }
    return data[i];
}

template <typename T>
int Vector<T>::index(const T& val) const
{
    for (int i = 0; i < size; i++)
    {
        if (val == this->at(i)) return i;
    }
    return -1;
}

template <typename T>
int Vector<T>::length() const {
    return size;
}
