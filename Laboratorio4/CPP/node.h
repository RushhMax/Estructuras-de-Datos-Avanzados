#ifndef NODE_H
#define NODE_H

#include <sstream>

template<typename T=int>
class Node
{
public:
    Node<T>* NW;
    Node<T>* NE;
    Node<T>* SW;
    Node<T>* SE;
    Node<T>* parent;
    std::string Q;
    int x,y;
    T value;
    Node()
    {
        NW=NE=SW=SE=parent=nullptr;
        x=y=0;
    }
    Node(std::string _Q, int _x, int _y, T _value)
    {
        NW=NE=SW=SE=parent=nullptr;
        Q=_Q;
        value=_value;
        x=_x;
        y=_y;
    }
    void automatate(Node<T>* N)
    {
        if(!N)
            return;
        automatate(N->NW);
        automatate(N->NE);
        automatate(N->SW);
        automatate(N->SE);
        delete N;
    }
};

#endif
