#include <iostream>
#include "quadtree.h"
using namespace std;

int main()
{
    QuadTree<string> tree;
    tree.insert(35, 40, "chicago");
    tree.insert(50, 10, "mobile");
    tree.insert(60, 75, "toronto");
    tree.insert(80, 65, "buffalo");
    tree.insert(5, 45, "denver");
    tree.insert(25, 35, "omaha");
    tree.insert(85, 15, "atlanta");
    tree.insert(90, 5, "miami");
    cout<<"BUSQUEDA POST ORDEN\n";
    tree.postOrden();
    tree.graph("quadtree.dot");
    cout<<"BUSQUEDA 1\n";
    tree.search(50,80,90,60);
    cout<<"BUSQUEDA 2\n";
    tree.search(0,100,100,0);
    cout<<"BUSQUEDA 3\n";
    tree.search(20,75,60,5);
    cout<<"BUSQUEDA 4\n";
    tree.search(20,75,60,75);
    cout<<"BUSQUEDA 5\n";
    tree.search(5,100,5,45);
    cout<<"BUSQUEDA 6\n";
    tree.search(20,50,95,5);
}
