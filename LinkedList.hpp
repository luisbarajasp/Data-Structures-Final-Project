/*
    Linked list template class
    
    Gilberto Echeverria
    gilecheverria@yahoo.com
    11/10/2016
*/

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <stdexcept>
#include "Node.hpp"

template <class T>
class LinkedList {
    protected:
        Node<T> * head = nullptr;
        int length = 0;
        
        void printRecursive(Node<T> * _head);
        int searchRecursive(T data, Node<T> * _head, int index);
    public:
        LinkedList() {}
        LinkedList(Node<T> * first) { head = first; length++; }
        ~LinkedList();
        // Insertion
        void insertHead(T data);
        void insertHead(Node<T> * new_node);
        void insertTail(T data);
        void insertTail(Node<T> * new_node);
        void insertAtPosition(T data, int position);
        void insertAtPosition(Node<T> * new_node, int position);
        void insertOrdered(T data);
        void insertOrdered(Node<T> * new_node);
        // Deletion
        Node<T> * deleteHead();
        Node<T> * deleteTail();
        Node<T> * deleteFromPosition(int position);
        Node<T> * deleteElement(T data);
        // Search
        int searchIterative(T data);
        int searchRecursive(T data);
        T getDataAtHead() const;
        T getDataAtTail() const;
        T getDataAtPosition (int position) const;
        // Helper methods
        Node<T> * getHead() { return head; }
        int getLength() { return length; }
        const int getLength() const { return length; }
        void clear();
        void printList();
        void print();

        // Overload the assignment operator
        // http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
        LinkedList<T> & operator= (const LinkedList<T> & other);
        
        template <class S>
        friend std::ostream & operator<< (std::ostream & stream, const LinkedList<S> & list);
};


template <class T>
LinkedList<T>::~LinkedList()
{
    clear();
}

///// INSERT /////

template <class T>
void LinkedList<T>::insertHead(T data)
{
    Node<T> * new_node = new Node<T>(data);
    insertHead(new_node);
}

template <class T>
void LinkedList<T>::insertHead(Node<T> * new_node)
{
    // Make the new node point to the previous head
    new_node->setNext(head);
    // Set the head of the list to the new node
    head = new_node;
    // Increase the size of the list
    length++;
}

template <class T>
void LinkedList<T>::insertTail(T data)
{
    Node<T> * new_node = new Node<T>(data);
    insertTail(new_node);
}

template <class T>
void LinkedList<T>::insertTail(Node<T> * new_node)
{
    // In case of an empty list
    if (head == nullptr)
    {
        head = new_node;
    }
    else
    {
        Node<T> * item = head;
        // Look for the last element in the list
        while (item->getNext() != nullptr)
        {
            item = item->getNext();
        }
        item->setNext(new_node);
    }
    // Increase the size of the list
    length++;
}

template <class T>
void LinkedList<T>::insertAtPosition (T data, int position)
{
    Node<T> * new_node = new Node<T>(data);
    insertAtPosition(new_node, position);
}

template <class T>
void LinkedList<T>::insertAtPosition (Node<T> * new_node, int position)
{
    // Do nothing in case of invalid positions
    if (position < 0 || position > length)
    {
        std::cout << "The positions specified is invalid\n";
        std::cout << "You must provide a positive number less than or equal to " << length << std::endl;
        return;
    }
    // Special cases for the head and tail
    else if(position == 0)
    {
        insertHead(new_node);
    }
    else if (position == length)
    {
        insertTail(new_node);
    }
    else
    {
        Node<T> * item = head;
        for (int i=1; i<position; i++)
        {
            item = item->getNext();
        }
        new_node->setNext(item->getNext());
        item->setNext(new_node);
        length++;
    }
}

template <class T>
void LinkedList<T>::insertOrdered (T data)
{
    Node<T> * new_node = new Node<T>(data);
    insertOrdered(new_node);
}

template <class T>
void LinkedList<T>::insertOrdered (Node<T> * new_node)
{
    if (head == nullptr || new_node->getData() < head->getData())
    {
        insertHead(new_node);
    }
    else
    {
        Node<T> * previous = head;
        Node<T> * item = previous->getNext();
        // Look for an item in the list with higher value than the new one
        while (item != nullptr && new_node->getData() > item->getData())
        {
            previous = item;
            item = item->getNext();
        }
        // Update the links between nodes
        previous->setNext(new_node);
        new_node->setNext(item);
        // Increase the size of the list
        length++;
    } 
}

///// DELETE /////

template <class T>
Node<T> * LinkedList<T>::deleteHead()
{
    // If the list was empty
    if(head == nullptr)
        return nullptr;
        
    Node<T> * item = head;
    // Update the head in the list
    head = head->getNext();
    // Break the connection to the list
    item->setNext(nullptr);
    // Update the length of the list
    length--;
    return item;
}

template <class T>
Node<T> * LinkedList<T>::deleteTail()
{
     // In case of an empty list
    if (head == nullptr)
    {
        return nullptr;
    }
    // If there is only one element in the list
    else if (head->getNext() == nullptr)
    {
        return deleteHead();
    }
    // A list with more than one element
    else
    {
        Node<T> * previous = head;
        Node<T> * item = previous->getNext();
        // Look for the last element in the list
        while (item->getNext() != nullptr)
        {
            previous = item;
            item = item->getNext();
        }
        // Make 'previous' the new tail
        previous->setNext(nullptr);
        // Decrease the size of the list
        length--;
        return item;
    }
}

template <class T>
Node<T> * LinkedList<T>::deleteFromPosition(int position)
{
    // Do nothing in case of invalid positions
    if (position < 0 || position > length-1)
    {
        std::cout << "The positions specified is invalid\n";
        std::cout << "You must provide a positive number less than or equal to " << length-1 << std::endl;
        return nullptr;
    }
    // Special cases for the head and tail
    else if(position == 0)
    {
        return deleteHead();
    }
    else if (position == length-1)
    {
        return deleteTail();
    }
    else
    {
        Node<T> * previous = head;
        Node<T> * item = previous->getNext();
        for (int i=1; i<position; i++)
        {
            previous = item;
            item = item->getNext();
        }
        // Update the previous node
        previous->setNext(item->getNext());         
        // Disconnect item from the list
        item->setNext(nullptr);
        length--;
        return item;
    }
}

template <class T>
Node<T> * LinkedList<T>::deleteElement(T data)
{
    return nullptr;
}


///// SEARCH /////

template <class T>
int LinkedList<T>::searchIterative(T data)
{
    Node<T> * item = head;
    int counter = 0;
    
    while (item != nullptr && item->getData() != data)
    {
        counter++;
        item = item->getNext();
    }
    if (item == nullptr)
        return -1;
    else
        return counter;
}

template <class T>
int LinkedList<T>::searchRecursive(T data)
{
    return searchRecursive(data, head, 0);
}

template <class T>
int LinkedList<T>::searchRecursive(T data, Node<T> * _head, int index)
{
    if (_head == nullptr)
        return -1;
    else if (_head->getData() == data)
        return index;
    else
        return searchRecursive(data, _head->getNext(), index+1);
}


template <class T>
T LinkedList<T>::getDataAtHead () const
{
    if (head != nullptr)
        return head->getData();
    else
        throw std::runtime_error("Empty list!");
}

template <class T>
T LinkedList<T>::getDataAtTail () const
{
    if (head != nullptr)
    {
        Node<T> * item = head;
        while (item->getNext() != nullptr)
        {
            item = item->getNext();
        }
        return item->getData();
    }
    else
    {
        throw std::runtime_error("Empty list!");
    }
}

template <class T>
T LinkedList<T>::getDataAtPosition (int position) const
{
    if (head != nullptr && position >= 0)
    {
        Node<T> * item = head;
        int index = 0;
        while (item->getNext() != nullptr && index < position)
        {
            item = item->getNext();
        }
        return item->getData();
    }
    else
    {
        throw std::runtime_error("Empty list!");
    }
}


///// HELPERS /////

template <class T>
void LinkedList<T>::printList()
{
    Node<T> * item = head;
    int count = 0;
    
    while (item != nullptr)
    {
        std::cout << "Item " << count++ << " = " << item->getData() << std::endl;
        item = item->getNext();
    }
}

template <class T>
void LinkedList<T>::print()
{
    printRecursive(head);
}

template <class T>
void LinkedList<T>::printRecursive(Node<T> * _head)
{
    if (_head == nullptr)
    {
        std::cout << std::endl;
    }
    else
    {
        std::cout << _head->getData() << " ";
        printRecursive(_head->getNext());
    }
}

template <class T>
std::ostream & operator<< (std::ostream & stream, const LinkedList<T> & list)
{
    Node<T> * item = list.head;
    
    stream << "[ ";
    while (item != nullptr)
    {
        stream << item->getData();
        item = item->getNext();
        if (item != nullptr)
            stream << ", ";
        else
            stream << " ";
    }
    stream << "]" << std::endl;
    return stream;
}

template <class T>
void LinkedList<T>::clear()
{
    Node<T> * item = head;
    
    while (item != nullptr)
    {
        head = item->getNext();
        delete item;
        item = head;
    }
    length = 0;
}

    template <class T>
LinkedList<T> & LinkedList<T>::operator= (const LinkedList<T> & other)
{
    if (this != &other)
    {
        // Free the current contents of this list
        clear();
        // Copy the other list
        Node<T> * item = other.head;
        while (item != nullptr)
        {
            insertTail(item->getData());
            item = item->getNext();
        }
    }
    // Return a reference to this very same object
    return *this;
}

#endif
