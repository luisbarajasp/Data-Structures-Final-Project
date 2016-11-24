/*
   Class to store the information needed for the Dijkstra Algorithm
   It will hold pointers to a vertex, the cost of getting here, when this vertex is visited
   and the pointer to the vertex that lead to this one

   For the Algorithm implementation, there will be a list of these elements

   Gilberto Echeverria
   gilecheverria@yahoo.com
   16/11/2016
*/

#ifndef INFO_NODE_HPP
#define INFO_NODE_HPP

#include <iostream>
#include "Vertex.hpp"

template <class T, class W>
class InfoNode {
    private:
        Vertex<T, W> * vertex = nullptr;
        bool visited;
        W cost;
        Vertex<T, W> * previous;
    public:
        InfoNode() :
            vertex(nullptr), visited(false), cost(-1), previous(nullptr) {}
        InfoNode(Vertex<T, W> * _vertex, const W & _cost = -1, Vertex<T, W> * _previous = nullptr) :
            vertex(_vertex), visited(false), cost(_cost), previous(_previous) {}
        bool isVisited() { return visited; }
        Vertex<T, W> * getVertex() { return vertex; }
        W getCost() { return cost; }
        Vertex<T, W> * getPrevious() { return previous; }
        void visit() { visited = true; }
        void setVertex(Vertex<T, W> * _vertex) { vertex = _vertex; }
        void setCost(const W & _cost) { cost = _cost; }
        void setPrevious(Vertex<T, W> * _previous) { previous = _previous; }

        template<class R, class S>
        friend std::ostream & operator<< (std::ostream & stream, const InfoNode<R, S> & info_node);
};

template <class T, class W>
std::ostream & operator<< (std::ostream & stream, const InfoNode<T, W> & info_node)
{
    stream << info_node.vertex->getData() << " " << info_node.visited << " " << info_node.cost << " ";
    if (info_node.previous != nullptr)
        stream << info_node.previous->getData();
    stream << std::endl;
    return stream;
}

#endif
