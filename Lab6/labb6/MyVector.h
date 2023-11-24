/*
* Victor Nyström, vicny135.
*
* This file contains the template class MyVector.
* The file contains both declarations and definitions
* of all the methods for the class template.
*/

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    // Constructor.
    MyVector();

    // Deconstructor.
    ~MyVector();

    // Copy constructor.
    MyVector(const MyVector& other);

    // Assignement operator
    MyVector& operator =(const MyVector& other);

    // Pushes an element to the end of the vector.
    void push_back(const T&);

    // Pops an element from the end of the vector.
    void pop_back();

    // overloads the [] operator to provide access to elements in the vector.
    T& operator[](unsigned i);

    // Const index operator.
    const T& operator[](unsigned i)const;

    // Returns true if the vector is empty.
    bool empty()const;

    // Returns a pointer to the first element.
    T* begin();

    // Returns a pointer to the last element.
    T* end();

    // Deletes all elements in the vector.
    void clear();

    // Returns the number of elements in the vector.
    unsigned size()const;

private:
    // pointer to dynamically allocated memory
    T* storage;

    // number of elements that are currently stored
    unsigned numberOfElements;

    // capacity of the vector
    unsigned capacity;

    // creates a deep copy of provided other.
    void copy(const MyVector& other);

    // creates more capacity in the vector by doubling it.
    void increaseCapacity();

};

template<typename T>
MyVector<T>::MyVector(){
    // initially assigning a capacity of 1 for the vector with 0 elements
    capacity = 1;
    storage = new T[1];
    numberOfElements = 0;
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] storage;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    copy(other);
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if(this == &other){
        // self assignment check
        return *this;
    }

    // deallocate memory
    delete[] storage;

    // call method to copy
    copy(other);

    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    // timecomplexity: O(1)
    if(capacity <= size()){
        // if capacity is met, call method to increase the capacity
        increaseCapacity();
    }

    storage[size()] = e;
    numberOfElements++;
}

template<typename T>
void MyVector<T>::pop_back(){
    if(size() == 0){
        return;
    }
    numberOfElements--;
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return storage[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
     return storage[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    return numberOfElements == 0;
}

template<typename T>
void MyVector<T>::clear(){
    capacity = 1;
    numberOfElements = 0;
    delete[] storage;
    storage = new T[1];
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}

template<typename T>
T* MyVector<T>::begin(){
    return storage;
}

template<typename T>
T* MyVector<T>::end(){
    return storage + size();
}

template<typename T>
void MyVector<T>::increaseCapacity(){
    // increase capacity by 4, leads to the method being called
    // more often and therefore results in a timecomplexity of O(n)
    // instead of O(1)
    /*
     * capacity += 4;
    */
    // double capacity size
    capacity *= 2;
    T* x = new T[capacity];
    for (unsigned i = 0; i < size(); i++) {
        x[i] = storage[i];
    }
    // deallocate memory
    delete[] storage;

    storage = x;
}

template<typename T>
void MyVector<T>::copy(const MyVector &other) {
    storage = new T[other.capacity];
    numberOfElements = other.numberOfElements;
    capacity = other.capacity;

    for (int i = 0; i < other.size(); i++) {
        storage[i] = other.storage[i];
    }
}

#endif // MY_VECTOR_H
