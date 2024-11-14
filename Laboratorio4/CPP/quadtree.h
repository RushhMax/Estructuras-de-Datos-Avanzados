#ifndef QUADTREE_H
#define QUADTREE_H

#include "node.h"
#include <iostream>
#include <sstream>
#include <fstream>

template<typename T>
class QuadTree
{
private:
    Node<T>* root;
    std::string compare(Node<T>* P, int x, int y);
    void postOrden(Node<T>* N);
    void graph_node(std::ofstream& f, Node<T>* N, int& null_n);
public:
    QuadTree();
    ~QuadTree();
    void insert(int x, int y, T value);
    void search(int t_x, int t_y, int b_x, int b_y);          // busqueda por rango
    void search(Node<T>* N, int t_x, int t_y, int b_x, int b_y);
    void search(int x, int y);
    void graph(std::string dir);
    void postOrden();
};

template<typename T>
QuadTree<T>::QuadTree()
{
    root=nullptr;
}

template<typename T>
QuadTree<T>::~QuadTree()
{
    root->automatate(root);
    std::cout<<"fin\n";
}

template<typename T>
std::string QuadTree<T>::compare(Node<T>* P, int x, int y)
{
    if(x<P->x)
    {
        if(y<P->y) return "SW";
        else return "NW";
    }
    else if(y<P->y) return "SE";
    return "NE";
}

bool equal_cor(int x, int y, int _x, int _y)
{
    if(x==_x && y==_y)
        return true;
    return false;
}

template<typename T>
void QuadTree<T>::insert(int x, int y, T value)
{
    std::string Q;
    Node<T>* tmp=root;
    if(!root)
        root = new Node<T>("root",x,y,value);
    else
    {
        Node<T>* p;
        while(tmp && !equal_cor(tmp->x, tmp->y, x, y))
        {
            p=tmp;
            Q=compare(tmp,x,y);
            if(Q=="NW")
                tmp = tmp->NW;
            else if(Q=="NE")
                tmp = tmp->NE;
            else if(Q=="SW")
                tmp = tmp->SW;
            else if(Q=="SE")
                tmp = tmp->SE;
        }
        if(!tmp)
        {
            if(Q=="NW")
                p->NW = new Node<T>(Q,x,y,value),p->NW->parent=p;
            else if(Q=="NE")
                p->NE = new Node<T>(Q,x,y,value),p->NE->parent=p;
            else if(Q=="SW")
                p->SW = new Node<T>(Q,x,y,value),p->SW->parent=p;
            else if(Q=="SE")
                p->SE = new Node<T>(Q,x,y,value),p->SE->parent=p;
        }
    }
}

template<typename T>
void QuadTree<T>::search(int t_x, int t_y, int b_x, int b_y)          // busqueda por rango
{
    search(root, t_x, t_y, b_x, b_y);
}

template<typename T>
void QuadTree<T>::search(Node<T>* N, int t_x, int t_y, int b_x, int b_y)          // busqueda por rango
{
    if(!N)
        return;
    if(t_x <= N->x && N->x <= b_x && t_y >= N->y && N->y >= b_y)
        std::cout<<"punto en el rango: "<<N->value<<" ("<<N->x<<","<<N->y<<")\n";
    if(t_x <= N->x && t_y >= N->y)              // limite superior al oeste y norte
    {
        search(N->NW, t_x, t_y, b_x, b_y);      // busca NW
        if(b_y < N->y)                          // limite inferior ocupa el sur
            search(N->SW, t_x, t_y, b_x, b_y);  // busca al SW
    }
    else if(t_x < N->x && t_y < N->y)           // limite supeior al oeste, pero al sur
        search(N->SW, t_x, t_y, b_x, b_y);      // busca al SW
    
    if(b_x >N->x && b_y < N->y)                 // limite inferior al este y sur
    {
        search(N->SE, t_x, t_y, b_x, b_y);      // busca al SE
        if(t_y > N->y)                          // limite superior ocupa norte
            search(N->NE, t_x, t_y, b_x, b_y);  // busca al NE
    }
    else if(b_x > N->x && b_y > N->y)           // limite inferior al este, pero al norte
        search(N->NE, t_x, t_y, b_x, b_y);      // busca al NE
}

template<typename T>
void QuadTree<T>::graph(std::string dir)
{
    int null_n=1;
    std::ofstream f(dir);
    f<<"graph T{\n";
    graph_node(f, root, null_n);
    f<<"}";
    f.close();

    std::stringstream dir1(dir);
    std::string name, ext, aux;
    std::getline(dir1,aux,'.');
    name = aux;
    std::getline(dir1,aux,'.');
    ext = aux;
    system(&(("dot "+ dir + " -o " + name + ".png -Tpng")[0]));
    system(&(("xdg-open " + name + ".png")[0]));
    // system("dot grafo.dot -o grafo.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    // system("grafo.png");
}

template<typename T>
void QuadTree<T>::graph_node(std::ofstream& f, Node<T>* N, int& null_n)
{
    if(!N)
        return;
    f<<N->value<<";\n";
    if(N->NW)
    {
        f<<N->value<<" -- "<<N->NW->value<<";\n";
        graph_node(f,N->NW,null_n);
    }
    else
        f<<N->value<<" -- NW_"+std::to_string(null_n++)<<";\n";
    if(N->NE)
    {
        f<<N->value<<" -- "<<N->NE->value<<";\n";
        graph_node(f,N->NE,null_n);
    }
    else
        f<<N->value<<" -- NE_"+std::to_string(null_n++)<<";\n";
    if(N->SW)
    {
        f<<N->value<<" -- "<<N->SW->value<<";\n";
        graph_node(f,N->SW,null_n);
    }
    else
        f<<N->value<<" -- SW_"+std::to_string(null_n++)<<";\n";
    if(N->SE)
    {
        f<<N->value<<" -- "<<N->SE->value<<";\n";
        graph_node(f,N->SE,null_n);
    }
    else
        f<<N->value<<" -- SE_"+std::to_string(null_n++)<<";\n";
}

template<typename T>
void QuadTree<T>::postOrden()
{
    postOrden(root);
    std::cout<<'\n';
}

template<typename T>
void QuadTree<T>::postOrden(Node<T>* N)
{
    if(!N)
        return;
    postOrden(N->NW);
    postOrden(N->NE);
    postOrden(N->SW);
    postOrden(N->SE);
    std::cout<<N->value<<" ";
}

#endif
