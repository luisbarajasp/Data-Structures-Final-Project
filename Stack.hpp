/*
A queue implemented with dynamic memory

Gilberto Echeverria
gilecheverria@yahoo.com
*/

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "Node.hpp"

template <class T>
class Stack {
    private:
        Node<T> * head = nullptr;
    public:
        Stack () {}
        Stack (Node<T> * new_node) { head = new_node; }
        ~Stack() { clear(); }
        
        bool isEmpty() { return head == nullptr; }
        Node<T> * top();
        Node<T> * pop();
        void push(Node<T> * new_node);
        void push(T data);
        void clear();
};

template <class T>
Node<T> * Stack<T>::top()
{
    return head;
}

template <class T>
Node<T> * Stack<T>::pop()
{
    // If the list was empty
    if(head == nullptr)
        return nullptr;
        
    Node<T> * item = head;
    // Update the head in the list
    head = head->getNext();
    // Break the connection to the list
    item->setNext(nullptr);
    return item;
}

template <class T>
void Stack<T>::push(Node<T> * new_node)
{
    // If the queue is empty
    if (head == nullptr)
    {
        head = new_node;
    }
    else
    {
        // Make the new node point to the former head
        new_node->setNext(head);
        // Set the new node as head
        head = new_node;
    }
}

template <class T>
void Stack<T>::push(T data)
{
    Node<T> * new_item = new Node<T>(data);
    push(new_item);
}
        
template <class T>
void Stack<T>::clear()
{
    Node<T> * item = head;
    
    while (item != nullptr)
    {
        head = item->getNext();
        delete item;
        item = head;
    }
}

#endif
