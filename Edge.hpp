/*
   Class for the edges in a directed weighted graph
   The edge has pointers to the vertices incident on it, and a weight variable

   Gilberto Echeverria
   gilecheverria@yahoo.com
   15/11/2016
*/

#ifndef EDGE_HPP
#define EDGE_HPP

template <class T, class W>
class Vertex;

template <class T, class W>
class Edge {
    private:
        Vertex<T, W> * origin;
        Vertex<T, W> * destination;
        W weight;
    public:
        //Edge() : origin(nullptr), destination(nullptr), weight(1) {}
        Edge(Vertex<T, W> * _origin=nullptr, Vertex<T, W> * _destination=nullptr, const W & _weight=1) :
            origin(_origin), destination(_destination), weight(_weight) {}
        void setWeight(const W & _weight) { weight = _weight; }
        W getWeight() { return weight; }
        Vertex<T, W> * getOrigin() { return origin; }
        Vertex<T, W> * getDestination() { return destination; }
};

#endif
