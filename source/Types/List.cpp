#include "List.h"

template <typename T> List<T>::List(int capacity = 8)
{
    _size = 0;
    _capacity = capacity;
    _data = new T[_capacity];
}

template <typename T> List<T>::~List()
{
    delete[] _data;
}

template <typename T> void List<T>::Add(T* item)
{
    // Check if the array needs to be resized
    if (_size == _capacity)
    {
        // Double the capacity
        _capacity *= 2;

        // Create a new array with the new capacity
        T* newData = new T[_capacity];

        // Copy the data from the old array to the new array
        for (int i = 0; i < _size; i++)
        {
            newData[i] = _data[i];
        }

        // Delete the old array
        delete[] _data;

        // Set the data pointer to the new array
        _data = newData;
    }

    // Add the item to the list
    _data[_size++] = *item;
}

template <typename T> T* List<T>::Get(int index)
{
    if (index < 0 || index >= _size)
    {
        return nullptr;
    }

    return &_data[index];
}

template <typename T> bool List<T>::Remove(int index)
{
    if (index < 0 || index >= _size)
    {
        return false;
    }

    // Shift all elements after the index to the left
    for (int i = index; i < _size - 1; i++)
    {
        _data[i] = _data[i + 1];
    }

    // Decrease the size of the list
    _size--;
    return true;
}

template <typename T> int List<T>::Size() const
{
    return _size;
}

template <typename T> int List<T>::Capacity() const
{
    return _capacity;
}

template <typename T> void List<T>::Clear()
{
    _size = 0;
}