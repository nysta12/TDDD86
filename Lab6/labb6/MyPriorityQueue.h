// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"


template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    // Constructor
    MyPriorityQueue() = default;

    // Deconstructor
    ~MyPriorityQueue() = default;

    // add element to the priorityQueue
    void push(const T& t);

    // return the element with the highest priority from the priorityQueue
    T top()const;

    // remove the element with the highest priority from the priorityQueue
    void pop();

    // return whether or not the priorityQueue is empty
    bool empty()const;

    // return the size of the priorityQueue
    unsigned size() const;

private:

    // returns the index of the left child
    int getLeftChild(const unsigned i) const;

    // returns the index of the parent
    int getParent(const unsigned i) const;

    // check if the current position is a leaf or not
    // that is if it has a child or children
    bool isLeaf(const unsigned index);
};

template <typename T, typename C>
int MyPriorityQueue<T,C>::getLeftChild(const unsigned i) const{
    return (2 * i) + 1;
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::getParent(const unsigned i) const{
    return (i - 1) / 2;
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::isLeaf(const unsigned index){
    return (2*index + 1) >= vector_array.size() && index < vector_array.size();
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);
    int i = vector_array.size() - 1;

    // if root node then it has nothing to compare to
    // root node when i = 0
    if(i > 0){
        int parent = getParent(i);

        while(strictly_larger_operator(vector_array[parent], t)){
            // t gets swapped with the parent if it has higher priority
            std::swap(vector_array[i],vector_array[parent]);

            // update parent
            i = parent;
            parent = getParent(i);
        }
    }
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    if(vector_array.size() > 0){

        // swaps the values of the two positions, the one with the highest
        // and the last element, then removes the element with the highest priority
        std::swap(vector_array[vector_array.size()-1], vector_array[0]);
        vector_array.pop_back();

        int i = 0;

        // i is swapped down the heap as long as a child
        // has higher priority than i
        while(!isLeaf(i)){
            unsigned leftChildPosition = getLeftChild(i);
            unsigned rightChildPosition = leftChildPosition + 1;
            unsigned childPosition = leftChildPosition;

            // if both left and right child exists and right child has higher priority,
            // make childPosition the right child
            if((leftChildPosition < (vector_array.size() - 1)) && rightChildPosition < vector_array.size() &&
                    strictly_larger_operator(vector_array[leftChildPosition], vector_array[rightChildPosition])){
                childPosition = rightChildPosition;
            }

            // if childPosition is smaller than current position i, perform the swap. Otherwise finished
            if(strictly_larger_operator(vector_array[i], vector_array[childPosition])){
                // swaps the values of the two positions
                std::swap(vector_array[i], vector_array[childPosition]);
                i = childPosition;
            }
            else{
                break;
            }
        }
    }
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return size() == 0;
}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();
}

#endif // MY_PRIORITY_QUEUE_H
