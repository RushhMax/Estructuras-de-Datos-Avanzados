#include <bits/stdc++.h>

#define vi vector<int>

using namespace std;

template<typename T, int dim>
class Node{
    public:
        T value;
        vi coord;
        Node *L, *R, *P;

        Node(T _value, vi _coord){
            coord = _coord;
            L = R = P = NULL;
            value = _value;
        }
};

template<typename T, int dim>
class KDTree{
    public:
        Node<T, dim> *root;

        KDTree(Node<T,dim>* _root){ root = _root; }

        void insert(T value, vi coord);
        void insert(T value, vi coord, int ind, Node<T,dim>* &node, Node<T,dim> *parent);

        // Busqueda exacta
        bool search(vi coord);
        bool search(vi coord, int ind, Node<T,dim>* node);

        double distance(vi coord1, vi coord2);
        // Busqueda Near Neighbor
        void searchNN(vi coord);
        void searchNN(vi coord, int ind, Node<T,dim>* node);

        // Busqueda de K-Near Neighbors
        void searchKNN(vi coord, int k);
        void searchKNN(vi coord, int k, int ind, Node<T,dim>* node);

        void print();
        void print(string ref, Node<T,dim> *node);
};


template<typename T, int dim>
void KDTree<T, dim>::insert(T value, vi coord){
    insert(value, coord, 0, root, NULL);
}

template<typename T, int dim>
void KDTree<T, dim>::insert(T value, vi coord, int ind, Node<T, dim>* &node, Node<T, dim> *parent){
    if(!node){
        node = new Node<T, dim>(value, coord);
        node->P = parent;
        return;
    }
    if(coord[ind] < node->coord[ind]){
        insert(value, coord, (ind+1)%dim, node->L, node);
    }else{
        insert(value, coord, (ind+1)%dim, node->R, node);
    }
}

template<typename T, int dim>
bool KDTree<T, dim>::search(vi coord){
    return search(coord, 0, root);
}

template<typename T, int dim>
bool KDTree<T, dim>::search(vi coord, int ind, Node<T, dim>* node){
    if(!node) return false;
    if(node->coord == coord) return true;
    if(coord[ind] < node->coord[ind]) return search(coord, (ind+1)%dim, node->L);
    return search(coord, (ind+1)%dim, node->R);
}

template<typename T, int dim>
double KDTree<T, dim>::distance(vi coord1, vi coord2){
    double dist = 0;
    for(int i = 0; i < dim; i++){
        dist += (coord1[i] - coord2[i])*(coord1[i] - coord2[i]);
    }
    return sqrt(dist);
}

template<typename T, int dim>
void KDTree<T, dim>::searchNN(vi coord){
    // Primer minimo
    Node<T, dim>* min = searchNN(coord, 0, root);
    if(!min) return;

    Node<T, dim>* parent = min->P;
    while(parent){
        if(distance(coord, parent->coord) < distance(coord, min->coord)){
            min = parent;
        }

        parent = parent->P;
    }
}

template<typename T, int dim>
Node<T, dim>* KDTree<T, dim>::searchNN(vi coord, int ind, Node<T, dim>* node){
    if(!node) return NULL;
    if(node->coord == coord) return NULL;
    if(coord[ind] < node->coord[ind]){
        if(!node->L) return node;
        return searchNN(coord, (ind+1)%dim, node->L);
    }
    if(!node->R) return node;
    return searchNN(coord, (ind+1)%dim, node->R);
}


template<typename T, int dim>
void KDTree<T, dim>::searchKNN(vi coord, int k){
    searchKNN(coord, k, 0, root);
}

template<typename T, int dim>
void KDTree<T, dim>::searchKNN(vi coord, int k, int ind, Node<T, dim>* node){
    
}

template<typename T, int dim>
void KDTree<T, dim>::print(){
    cout << "Printing tree" << endl;
    print("", root);
}

template<typename T, int dim>
void KDTree<T, dim>::print(string ref, Node<T, dim> *node){
    if(!node) return;
    cout << "N "<<node->value << ": ";
    for(auto x: node->coord){
        cout << x << " ";
    }
    cout << endl;
    ref = ref + "|  ";
    if(node->L) cout << ref << "L";
    print(ref , node->L);
    if(node->R) cout << ref << "R";
    print(ref , node->R);
}

int main(){
    KDTree<char, 3> tree(NULL);
    vi coord;

    srand(time(NULL));
    for(int i = 0; i < 100; i++){
        int n = 10;
        coord = {rand()%n, rand()%n, rand()%n};
        tree.insert('A'+i, coord);
    }

    tree.print();

}
