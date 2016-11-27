/*
   Class for a directed weighted graph
   The vertces are stored in a list
   Each vertex will have a list of the edges going out from it
   This class allows for an inefficient implementation of the Dijkstra Algorithm

   Gilberto Echeverria
   gilecheverria@yahoo.com
   15/11/2016
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Vertex.hpp"
#include "InfoNode.hpp"

template <class T, class W>
class Graph {
    private:
        LinkedList<Vertex<T, W> *> vertices;
        LinkedList<Edge<T, W> *> edges;
        Vertex<T, W> * start;

        // Private methods
        void clearVisits();
        InfoNode<T, W> * initializeDijkstra(LinkedList<InfoNode<T, W> *> * dijkstra, Node<Vertex<T, W> *> * node, Vertex<T, W> * origin);
        void clearDjikstra(LinkedList<InfoNode<T, W> *> * dijkstra);
        InfoNode<T, W> * getCheapest(LinkedList<InfoNode<T, W> *> * dijkstra);
        LinkedList<Vertex<T, W> *> * recoverPath(LinkedList<InfoNode<T, W> *> dijkstra, InfoNode<T, W> * current_vertex_info_node);
    public:
        Graph() { start = nullptr; }
        ~Graph();
        void addVertex(const T & _data);
        void addVertex(Vertex<T, W> * _vertex);
        void addEdge(const T & origin_data, const T & destination_data, const W & _weight = 1);
        void addEdge(Vertex<T, W> * _origin, Vertex<T, W> * _destination, const W & _weight = 1);
        void addEdge(Edge<T, W> * _edge);
        Vertex<T, W> * getStart() { return start; }
        void setStart(Vertex<T, W> * _start) { start = _start; }
        void setStart(const T & _data);
        void printBreadthFirst();
        void printDepthFirst();
        LinkedList<Vertex<T, W> *> * findPath(Vertex<T, W> * origin, Vertex<T, W> * destination);
        LinkedList<Vertex<T, W> *> * findPath(const T & origin, const T & destination);
        void printPath(LinkedList<Vertex<T, W> *> * path);
        //Added
        int getVerticesLength() { return vertices.getLength(); }
        LinkedList<Vertex<T, W> *> * getVerticesList() { return &vertices; }
        Vertex<T, W> * getVertex(const T & _data);

};

template <class T, class W>
Vertex<T, W> * Graph<T, W>::getVertex(const T & _data){
    Vertex<T, W> * current_vertex = nullptr;

    Node<Vertex<T, W> *> * node = vertices.getHead();
    // Look for the vertex that contain the data specified
    while (node != nullptr)
    {
        current_vertex = node->getData();
        if (current_vertex->getData() == _data)
            return current_vertex;
    }

    current_vertex = nullptr;

    return current_vertex;
}

template <class T, class W>
Graph<T, W>::~Graph()
{
    Vertex<T, W> * vertex_ptr = nullptr;
    Node<Vertex<T, W> *> * vertex_node = nullptr;
    Edge<T, W> * edge_ptr = nullptr;
    Node<Edge<T, W> *> * edge_node = nullptr;

    vertex_node = vertices.getHead();
    // Delete the vertices first
    while (vertex_node != nullptr)
    {
        vertex_ptr = vertex_node->getData();
        // Deleting the vertex will call its destructor
        //  and clear its neighbours list
        delete vertex_ptr;
        vertex_node = vertex_node->getNext();
    }

    edge_node = edges.getHead();
    // Delete the vertices first
    while (edge_node != nullptr)
    {
        edge_ptr = edge_node->getData();
        // Deleting the edge will call its destructor
        delete edge_ptr;
        edge_node = edge_node->getNext();
    }

    // Now clear the lists in this class
    vertices.clear();
    edges.clear();
}

template <class T, class W>
void Graph<T, W>::addVertex(const T & _data)
{
    Vertex<T, W> * new_vertex = new Vertex<T, W>(_data);
    addVertex(new_vertex);
}

template <class T, class W>
void Graph<T, W>::addVertex(Vertex<T, W> * _vertex)
{
    vertices.insertTail(_vertex);
}

template <class T, class W>
void Graph<T, W>::addEdge(const T & origin_data, const T & destination_data, const W & _weight)
{
    Vertex<T, W> * _origin = nullptr;
    Vertex<T, W> * _destination = nullptr;
    Vertex<T, W> * current_vertex = nullptr;
    Node<Vertex<T, W> *> * node = vertices.getHead();
    // Look for the vertices that contain the data specified
    while (node != nullptr)
    {
        current_vertex = node->getData();
        if (current_vertex->getData() == origin_data)
            _origin = current_vertex;
        if (current_vertex->getData() == destination_data)
            _destination = current_vertex;
        node = node->getNext();
    }
    // Call the other methods in this class to add edges
    addEdge(_origin, _destination, _weight);
}

template <class T, class W>
void Graph<T, W>::addEdge(Vertex<T, W> * _origin, Vertex<T, W> * _destination, const W & _weight)
{
    if (_origin != nullptr && _destination != nullptr)
    {
        Edge<T, W> * new_edge = new Edge<T, W>(_origin, _destination, _weight);
        addEdge(new_edge);
    }
}

template <class T, class W>
void Graph<T, W>::addEdge(Edge<T, W> * _edge)
{
    if (_edge != nullptr)
    {
        // Insert the edge to the list in the graph
        edges.insertTail(_edge);
        // Add the edge to the list in the origin vertex
        _edge->getOrigin()->addEdge(_edge);
    }
}

template <class T, class W>
void Graph<T, W>::setStart(const T & _data)
{
    Vertex<T, W> * current_vertex = nullptr;
    Node<Vertex<T, W> *> * node = vertices.getHead();
    // Look for the vertices that contain the data specified
    while (node != nullptr)
    {
        current_vertex = node->getData();
        if (current_vertex->getData() == _data)
        {
            setStart(current_vertex);
            return;
        }
        node = node->getNext();
    }
}

template <class T, class W>
void Graph<T, W>::printBreadthFirst()
{
    if (start == nullptr)
        return;

    Vertex<T, W> * current_vertex = nullptr;
    Vertex<T, W> * neighbour = nullptr;
    Node<Vertex<T, W> *> * queue_item = nullptr;
    Node<Edge<T, W> *> * node = nullptr;
    LinkedList<Edge<T, W> *> * edge_list = nullptr;
    Queue<Vertex<T, W> *> queue;

    std::cout << "Breadth First Traversal:" << std::endl;
    // Make sure all vertices are marked as not visited
    clearVisits();
    // Add the initial node to the queue
    queue.push(start);
    while(!queue.isEmpty())
    {
        // Get the next vertex from the queue
        queue_item = queue.pop();
        current_vertex = queue_item->getData();
        delete queue_item;
        std::cout << current_vertex->getData() << " -> ";
        // Mark the vertex as visited
        current_vertex->visit();
        // Get the list of edges
        edge_list = current_vertex->getEdges();
        // Get the node with the first edge
        node = edge_list->getHead();
        while(node != nullptr)
        {
            // Get the destination of the edge stored in the node
            neighbour = node->getData()->getDestination();
            // If the neighbour has not been visited, add it to the queue
            if (!neighbour->isVisited())
            {
                queue.push(neighbour);
            }
            // Get next neighbour
            node = node->getNext();
        }
    }
    std::cout << std::endl;
}

template <class T, class W>
void Graph<T, W>::printDepthFirst()
{
    if (start == nullptr)
        return;

    Vertex<T, W> * current_vertex = nullptr;
    Vertex<T, W> * neighbour = nullptr;
    Node<Vertex<T, W> *> * stack_item = nullptr;
    Node<Edge<T, W> *> * node = nullptr;
    LinkedList<Edge<T, W> *> * edge_list = nullptr;
    Stack<Vertex<T, W> *> stack;

    std::cout << "Depth First Traversal:" << std::endl;
    // Make sure all vertices are marked as not visited
    clearVisits();
    // Add the initial node to the stack
    stack.push(start);
    while(!stack.isEmpty())
    {
        // Get the next vertex from the stack
        stack_item = stack.pop();
        current_vertex = stack_item->getData();
        delete stack_item;
        std::cout << current_vertex->getData() << " -> ";
        // Mark the vertex as visited
        current_vertex->visit();
        // Get the list of edges
        edge_list = current_vertex->getEdges();
        // Get the node with the first edge
        node = edge_list->getHead();
        while(node != nullptr)
        {
            // Get the destination of the edge stored in the node
            neighbour = node->getData()->getDestination();
            // If the neighbour has not been visited, add it to the stack
            if (!neighbour->isVisited())
            {
                stack.push(neighbour);
            }
            // Get next neighbour
            node = node->getNext();
        }
    }
    std::cout << std::endl;
}

template <class T, class W>
void Graph<T, W>::clearVisits()
{
    // Set all vertices as not visited
    Node<Vertex<T, W> *> * node = vertices.getHead();
    Vertex<T, W> * current_vertex;

    while(node != nullptr)
    {
        current_vertex = node->getData();
        current_vertex->unvisit();
        node = node->getNext();
    }
}

template <class T, class W>
LinkedList<Vertex<T, W> *> * Graph<T, W>::findPath(const T & origin_data, const T & destination_data)
{
    Vertex<T, W> * _origin = nullptr;
    Vertex<T, W> * _destination = nullptr;
    Vertex<T, W> * current_vertex = nullptr;
    Node<Vertex<T, W> *> * node = vertices.getHead();
    // Look for the vertices that contain the data specified
    while (node != nullptr)
    {
        current_vertex = node->getData();
        if (current_vertex->getData() == origin_data)
            _origin = current_vertex;
        if (current_vertex->getData() == destination_data)
            _destination = current_vertex;
        node = node->getNext();
    }
    // Find the path from the origin vertex to the destination vertex
    return findPath(_origin, _destination);
}

template <class T, class W>
LinkedList<Vertex<T, W> *> * Graph<T, W>::findPath(Vertex<T, W> * origin, Vertex<T, W> * destination)
{
    LinkedList<InfoNode<T, W> *> dijkstra;
    Node<InfoNode<T, W> *> * dijkstra_node = nullptr;
    InfoNode<T, W> * info_node = nullptr;
    InfoNode<T, W> * current_vertex_info_node = nullptr;
    Node<Edge<T, W> *> * edge_node = nullptr;
    Vertex<T, W> * current_vertex = nullptr;
    Vertex<T, W> * neighbour = nullptr;
    LinkedList<Edge<T, W> *> * edge_list = nullptr;
    LinkedList<Vertex<T, W> *> * path = nullptr;

    // Set the current_vertex vertex to the starting point (origin)
    current_vertex = origin;
    // Initialize the "table" for the Dijkstra algorithm
    current_vertex_info_node = initializeDijkstra(&dijkstra, vertices.getHead(), origin);

    // Loop until the destination is reached
    while (current_vertex_info_node != nullptr and current_vertex != destination)
    {
         // Get the list of edges
        edge_list = current_vertex->getEdges();
        // Get the node with the first edge
        edge_node = edge_list->getHead();
        // Loop over the neighbours of the current vertex
        while(edge_node != nullptr)
        {
            // Get the destination of the edge stored in the node
            neighbour = edge_node->getData()->getDestination();
            // Update the cost for each neighbour
            // TODO: This is very inefficient. The Dijkstra list is searched each time
            dijkstra_node = dijkstra.getHead();
            while (dijkstra_node != nullptr)
            {
                info_node = dijkstra_node->getData();
                if (info_node->getVertex() == neighbour)
                {
                    // Add cost of the current_vertex node and the edge weight to the neighbour
                    W new_cost = current_vertex_info_node->getCost() + edge_node->getData()->getWeight();
                    // If the new cost is lower, than the previous, or if no cost has been determined yet
                    if (info_node->getCost() == -1 or new_cost < info_node->getCost())
                    {
                        info_node->setCost(new_cost);
                        info_node->setPrevious(current_vertex);
                    }
                }
                dijkstra_node = dijkstra_node->getNext();
            }
            // Get next neighbour
            edge_node = edge_node->getNext();
        }
        // Continue by checking the next cheapest item in the dijkstra list
        current_vertex_info_node = getCheapest(&dijkstra);
        current_vertex_info_node->visit();
        current_vertex = current_vertex_info_node->getVertex();
    }

    // Recover the path from origin to destination
    path = recoverPath(dijkstra, current_vertex_info_node);

    // Clear the memory used by the Dijkstra list
    clearDjikstra(&dijkstra);

    return path;
}


// Create the table with the information needed to determine the path using Djikstra
// Receives the list, the head of the list of vertices and the origin vertex
// Returns the info node for the origin vertex
template <class T, class W>
InfoNode<T, W> * Graph<T, W>::initializeDijkstra(LinkedList<InfoNode<T, W> *> * dijkstra, Node<Vertex<T, W> *> * node, Vertex<T, W> * origin)
{
    InfoNode<T, W> * info_node = nullptr;
    InfoNode<T, W> * origin_info_node = nullptr;
    Vertex<T, W> * current_vertex = nullptr;

    // Fill the dijkstra list with info nodes
    while(node != nullptr)
    {
        current_vertex = node->getData();
        info_node = new InfoNode<T, W> (current_vertex);
        if (current_vertex == origin)
        {
            origin_info_node = info_node;
            info_node->setCost(0);
        }
        dijkstra->insertTail(info_node);
        node = node->getNext();
    }

    return origin_info_node;
}

// Free all the data nodes created for the Dijkstra table
template <class T, class W>
void Graph<T, W>::clearDjikstra(LinkedList<InfoNode<T, W> *> * dijkstra)
{
    Node<InfoNode<T, W> *> * dijkstra_node = nullptr;
    InfoNode<T, W> * info_node = nullptr;

    // Delete all the info nodes created and stored in the djikstra list
    dijkstra_node = dijkstra->getHead();
    while (dijkstra_node != nullptr)
    {
        info_node = dijkstra_node->getData();
        delete info_node;
        dijkstra_node = dijkstra_node->getNext();
    }
}

template <class T, class W>
InfoNode<T, W> * Graph<T, W>::getCheapest(LinkedList<InfoNode<T, W> *> * dijkstra)
{
    InfoNode<T, W> * info_node = nullptr;
    InfoNode<T, W> * lowest_vertex = nullptr;
    Node<InfoNode<T, W> *> * list_node;
    // TODO: Find a better way to initialize the cost
    W lowest_cost = 99999999;

    list_node = dijkstra->getHead();
    while(list_node != nullptr)
    {
        info_node = list_node->getData();
        //std::cout << "Comparing with: " << *info_node << std::endl;
        if (info_node->getCost() != -1 and info_node->getCost() < lowest_cost and !info_node->isVisited())
        {
            lowest_cost = info_node->getCost();
            lowest_vertex = info_node;
        }
        list_node = list_node->getNext();
    }
    return lowest_vertex;
}

// Recover the path from origin to destination
template <class T, class W>
LinkedList<Vertex<T, W> *> * Graph<T, W>::recoverPath(LinkedList<InfoNode<T, W> *> dijkstra, InfoNode<T, W> * current_vertex_info_node)
{
    LinkedList<Vertex<T, W> *> * path = new LinkedList<Vertex<T, W> *>;
    Node<InfoNode<T, W> *> * dijkstra_node = nullptr;
    InfoNode<T, W> * info_node = nullptr;

    // Search the previous vertices in the Dijkstra list
    while(current_vertex_info_node->getPrevious() != nullptr)
    {
        // Insert the vertex in to the path list
        path->insertHead(current_vertex_info_node->getVertex());
        // Look in the list of info nodes for the previous vertex
        dijkstra_node = dijkstra.getHead();
        while (dijkstra_node != nullptr)
        {
            info_node = dijkstra_node->getData();
            // Get the vertex that is marked as previous in this info node
            if (info_node->getVertex() == current_vertex_info_node->getPrevious())
            {
                current_vertex_info_node = info_node;
                break;
            }
            dijkstra_node = dijkstra_node->getNext();
        }
    }
    // Insert the origin vertex in the list
    path->insertHead(current_vertex_info_node->getVertex());

    return path;
}

// Method to print the contents of a list of vertices as a path
template <class T, class W>
void Graph<T, W>::printPath(LinkedList<Vertex<T, W> *> * path)
{
    Node<Vertex<T, W> *> * node = nullptr;
    Vertex<T, W> * vertex;

    node = path->getHead();
    while(node != nullptr)
    {
        vertex = node->getData();
        std::cout << (*vertex).getData();
        node = node->getNext();
        if (node != nullptr)
            std::cout << " -> ";
        else
            std::cout << std::endl;
    }
}

#endif
