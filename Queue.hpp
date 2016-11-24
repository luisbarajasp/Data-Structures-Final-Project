/*
A queue implemented with dynamic memory

Gilberto Echeverria
gilecheverria@yahoo.com
*/

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include "Node.hpp"

template <class T>
class Queue {
    private:
        Node<T> * head = nullptr;
        Node<T> * tail = nullptr;
    public:
        Queue () {}
        Queue (Node<T> * new_node)
        { head = new_node; tail = new_node; }
        ~Queue() { clear(); }
        
        bool isEmpty() { return head == nullptr; }
        Node<T> * top();
        Node<T> * pop();
        void push(Node<T> * new_node);
        void push(T data);
        void clear();
};

template <class T>
Node<T> * Queue<T>::top()
{
    return head;
}

template <class T>
Node<T> * Queue<T>::pop()
{
    // If the list was empty
    if(head == nullptr)
        return nullptr;
        
    Node<T> * item = head;
    // Update the head in the list
    head = head->getNext();
    // If there was only one element in the list
    if (head == nullptr)
        tail = nullptr;
    // Break the connection to the list
    item->setNext(nullptr);
    return item;
}

template <class T>
void Queue<T>::push(Node<T> * new_node)
{
    // If the queue is empty
    if (tail == nullptr)
    {
        tail = new_node;
        head = new_node;
    }
    else
    {
        // Add the new node at the tail
        tail->setNext(new_node);
        // Update the pointer
        tail = new_node;
    }
}

template <class T>
void Queue<T>::push(T data)
{
    Node<T> * new_item = new Node<T>(data);
    push(new_item);
}
        
template <class T>
void Queue<T>::clear()
{
    Node<T> * item = head;
    
    while (item != nullptr)
    {
        head = item->getNext();
        delete item;
        item = head;
    }
    tail = nullptr;
}

#endif
