#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>

template<typename T, int dim>
class Node{
    public:
        T value;
        vi coord;
        Node<T, dim> *L, *R, *P;

        Node(T _value, vi _coord){
            coord = _coord;
            L = R = P = NULL;
            value = _value;
        }

        ~Node(){
            delete L;
            delete R;
        }
};

#endif
