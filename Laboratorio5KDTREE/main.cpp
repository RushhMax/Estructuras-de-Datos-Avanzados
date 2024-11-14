#include <iostream>
#include "KDTree.h"

int main(){
    KDTree<char, 3> tree(NULL);
    vi coord;

    srand(time(NULL));
    for(int i = 0; i < 20; i++){
        int n = 10;
        coord = {rand()%n, rand()%n, rand()%n};
        tree.insert('A'+i, coord);
    }

    tree.print();

    tree.searchNN({1, 2, 3});
    priority_queue<pair<double, Node<char, 3>*>> p = tree.searchKNN({1, 2, 3}, 5);
    while(!p.empty()){
        pair<double, Node<char, 3>*> x = p.top();
        cout << "Node: " << x.second->value << " with distance: " << x.first << endl;
        for(auto y: x.second->coord){
            cout << y << " ";
        }
        cout<<endl;
        p.pop();
    }
}
