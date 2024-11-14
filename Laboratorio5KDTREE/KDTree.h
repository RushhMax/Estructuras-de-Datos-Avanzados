#ifndef KDTREE_H
#define KDTREE_H

#include "Node.h"

template<typename T, int dim>
class KDTree{
    public:
        Node<T, dim> *root;

        KDTree(Node<T,dim>* _root){ root = _root; }
        ~KDTree(){ delete root; }

        void insert(T value, vi coord);
        void insert(T value, vi coord, int ind, Node<T,dim>* &node, Node<T,dim> *parent);

        // Busqueda exacta
        bool search(vi coord);
        bool search(vi coord, int ind, Node<T,dim>* node);

        double distance(vi coord1, vi coord2);
        // Busqueda Near Neighbor
        void searchNN(vi coord);
        pair<Node<T, dim>*, double> searchNN(vi coord, int ind, double bestDist, Node<T, dim>* node, Node<T, dim>* bestNode);

        // Busqueda de K-Near Neighbors
        priority_queue<pair<double, Node<T, dim>*>> searchKNN(vi coord, int k);
        priority_queue<pair<double, Node<T, dim>*>> searchKNN(vi coord, int ind, Node<T, dim>* node, int k, priority_queue<pair<double, Node<T, dim>*>> pq);

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
    double bestDist = 100000;
    pair<Node<T, dim> *, double> p = searchNN(coord, 0, bestDist, root, root);
    cout << "Best Node: " << p.first->value << " with ";
    for(auto x: p.first->coord){
        cout << x << " ";
    }cout<<endl;
    cout << "Best Distance: " << p.second << endl;
}

template<typename T, int dim>
pair<Node<T, dim>*, double> KDTree<T, dim>::searchNN(vi coord, int ind, double bestDist, Node<T, dim>* node, Node<T, dim>* bestNode){
    if(!node) return {bestNode, bestDist};
    double dist = distance(coord, node->coord);
    if(dist < bestDist){
        bestDist = dist;
        bestNode = node;
    }
    Node<T, dim>* closeBranch = NULL;
    Node<T, dim>* farBranch = NULL;
    if(coord[ind] < node->coord[ind]){
        closeBranch = node->L;
        farBranch = node->R;
    }else{
        closeBranch = node->R;
        farBranch = node->L;
    }
    tie(bestNode, bestDist) = searchNN(coord, (ind+1)%dim, bestDist, closeBranch, bestNode);
    if(abs(coord[ind] - node->coord[ind]) < bestDist){
        tie(bestNode, bestDist) = searchNN(coord, (ind+1)%dim, bestDist, farBranch, bestNode);
    }
    return {bestNode, bestDist};
}

template<typename T, int dim>
priority_queue<pair<double, Node<T, dim>*>> KDTree<T, dim>::searchKNN(vi coord, int k){
    priority_queue<pair<double, Node<T, dim>*>> pq;
    pq.push({INT_MAX, root});
    pq = searchKNN(coord, 0, root, k, pq);
    pair<double, Node<T, dim>*> p = pq.top();
    if(p.first == INT_MAX){
        cout << "No se encontraron los " << k << " vecinos mas cercanos" << endl;
        //pq.pop();
    }
    return pq;
}

template<typename T, int dim>
priority_queue<pair<double, Node<T, dim>*>> KDTree<T, dim>::searchKNN(vi coord, int ind, Node<T, dim>* node, int k, priority_queue<pair<double, Node<T, dim>*>> pq){
    if(!node) return pq;
    double dist = distance(coord, node->coord);
    
    if(pq.size() < k){
        pq.push({dist, node});
    }else if(dist < pq.top().first){
        pq.pop();
        pq.push({dist, node});
    }
    Node<T, dim>* closeBranch = NULL;
    Node<T, dim>* farBranch = NULL;
    if(coord[ind] < node->coord[ind]){
        closeBranch = node->L;
        farBranch = node->R;
    }else{
        closeBranch = node->R;
        farBranch = node->L;
    }
    pq = searchKNN(coord, (ind+1)%dim, closeBranch, k, pq);
    if(abs(coord[ind] - node->coord[ind]) < pq.top().first || pq.size() < k){
        pq = searchKNN(coord, (ind+1)%dim, farBranch, k, pq);
    }
    return pq;
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

#endif
