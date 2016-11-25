/*
   Class for the Vertex of a directed weighted graph
   Each vertex has a list of edges going out from it

   Gilberto Echeverria
   gilecheverria@yahoo.com
   15/11/2016
*/

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include "LinkedList.hpp"
#include "Edge.hpp"

template <class T, class W>
class Vertex {
    private:
        T data;
        bool visited;
        LinkedList<Edge<T, W> *> edges;
        //Variables for the SFML implementation
        int x;
        int y;
    public:
        Vertex();
        Vertex(const T & _data);
        ~Vertex() { edges.clear(); }
        T getData() { return data; }
        void setData(const T & _data) { data = _data; }
        void visit() { visited = true; }
        void unvisit() { visited = false; }
        bool isVisited() { return visited; }
        LinkedList<Edge<T, W> *> * getEdges() { return &edges; }
        void addEdge(Edge<T, W> * _edge);

        void setX(int _x) { x = _x; }
        int getX() { return x; }
        void setY(int _y) { y = _y; }
        int getY() { return y; }

        template <class R, class S>
        friend std::ostream & operator<< (std::ostream & stream, const Vertex<R, S> & vertex);
};

template <class T, class W>
Vertex<T, W>::Vertex()
{
    visited = false;
    edges = nullptr;
}

template <class T, class W>
Vertex<T, W>::Vertex(const T & _data)
{
    data = _data;
    visited = false;
    edges = nullptr;
}

template <class T, class W>
void Vertex<T, W>::addEdge(Edge<T, W> * _edge)
{
    edges.insertTail(_edge);
}

template <class T, class W>
std::ostream & operator<< (std::ostream & stream, const Vertex<T, W> & vertex)
{
    stream << "Data: " << vertex.data << " | " << (vertex.visited ? "" : "not ") << "visited";
    return stream;
}

#endif
