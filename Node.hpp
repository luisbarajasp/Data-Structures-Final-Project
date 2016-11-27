/*
    Node class to store integers in a linked list

    Gilberto Echeverria
    gilecheverria@yahoo.com
*/


#ifndef NODE_HPP
#define NODE_HPP

template <class T>
class Node {
    private:
        T data;
        Node * next = nullptr;
    public:
        Node () { }
        Node (T _data) { data = _data; }
        ~Node () { next = nullptr; }
        void setData(T _data) { data = _data; }
        T getData() { return data; }
        void setNext(Node * _next) { next = _next; }
        Node * getNext() { return next; }

        template <class S>
        friend std::ostream & operator<< (std::ostream & stream, const Node<S> & node);
};

template <class T>
std::ostream & operator<< (std::ostream & stream, const Node<T> & node)
{
    stream << "-" << node.getData() << "-";
    return stream;
}

#endif
