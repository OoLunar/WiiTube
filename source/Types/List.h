#pragma once

template <typename T> class List
{
  private:
    // The number of items current in the list
    int _size;

    // The number of items that can be stored in the list
    int _capacity;

    // The data stored in the list
    T* _data;

  public:
    List(int capacity = 8);
    ~List();
    void Add(T* item);
    T* Get(int index);
    bool Remove(int index);
    int Size() const;
    int Capacity() const;
    void Clear();
};