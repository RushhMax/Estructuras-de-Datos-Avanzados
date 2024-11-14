#include "KDTree.h"


double distance(vi coord1, vi coord2, int dim){
    double dist = 0;
    for(int i = 0; i < dim; i++){
        dist += (coord1[i] - coord2[i])*(coord1[i] - coord2[i]);
    }
    return sqrt(dist);
}

template <typename T, int dim>
priority_queue<pair<double, Node<T, dim>*>> bruteForce(vector<Node<T, dim>*> &nodes, vi coord, int k){
    priority_queue<pair<double, Node<T, dim>*> > pq;    
    Node<T, dim>* bestNode = NULL;
    for(auto node:nodes){
        double bestDist = distance(node->coord, coord, dim);
        if(pq.size() < k){
            pq.push({bestDist, node});
        }else if(bestDist < pq.top().first){
            pq.pop();
            pq.push({bestDist, node});
        }
    }
    return pq;
}

template <typename T, int dim>
void printKNN(priority_queue<pair<double, Node<T, dim>*> > pq){
    while(!pq.empty()){
        pair<double, Node<T, dim>*> x = pq.top();
        cout << "Node (";
        for(auto y: x.second->coord){
            cout << y << ", ";
        }
        cout<< ") with distance: " << x.first << endl;
        pq.pop();
    }
    cout<<endl;
}

int main(){
    ifstream f1("1000.csv");
    ifstream f2("10000.csv");
    ifstream f3("20000.csv");
    ofstream outp("output.txt");

    KDTree<char, 3> tree1(NULL);
    KDTree<char, 3> tree2(NULL);
    KDTree<char, 3> tree3(NULL);

    vector<Node<char, 3>*> nodesTree1;
    vector<Node<char, 3>*> nodesTree2;
    vector<Node<char, 3>*> nodesTree3;

    /// TREE 1
    int x,y,z, i = 0;
    while(f1 >> x >> y >> z){
        //cout<< "Insertando " << x << " " << y << " " << z << endl;
        tree1.insert('A'+i, {x,y,z});
        Node<char, 3>* node = new Node<char, 3>('A'+i, {x,y,z});
        nodesTree1.push_back(node);
        i++;
    }
    //tree1.print();
    
    /// TREE 2
    i = 0;
    while(f2 >> x >> y >> z){
        //cout<< "Insertando " << x << " " << y << " " << z << endl;
        tree2.insert('A'+i, {x,y,z});
        Node<char, 3>* node = new Node<char, 3>('A'+i, {x,y,z});
        nodesTree2.push_back(node);
        i++;
    }
    //tree2.print();
    
    /// TREE 3
    i = 0;
    while(f3 >> x >> y >> z){
        //cout<< "Insertando " << x << " " << y << " " << z << endl;
        tree3.insert('A'+i, {x,y,z});
        Node<char, 3>* node = new Node<char, 3>('A'+i, {x,y,z});
        nodesTree3.push_back(node);
        i++;
    }
    //tree3.print();
    
    int k, xr = rand()%100, yr = rand()%100, zr = rand()%100;
    priority_queue<pair<double, Node<char, 3>*> > pq;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
    std::chrono::duration<double> duration1, duration2;
    //cout<<" Buscando KNN... k= ";cin>>k;
    for(int k = 10; k <= 1000; k+=50){
        outp << "k: " << k << "\n";

        cout << "Tree 1: " << endl;
        start =  std::chrono::high_resolution_clock::now();
        pq = tree1.searchKNN({xr, yr , zr },k);
        stop = std::chrono::high_resolution_clock::now();
        duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time taken by KDTree: " << duration1.count() << " microseconds" << endl;
        printKNN(pq);
        outp << duration1.count() << " ";

        //cout<<" Buscando KNN con fuerza bruta... k= "<<k<<endl;
        start = std::chrono::high_resolution_clock::now();
        pq = bruteForce(nodesTree1, {xr, yr, zr},k);
        stop = std::chrono::high_resolution_clock::now();
        duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time taken by Brute Force: " << duration2.count() << " microseconds" << endl;
        printKNN(pq);
        outp << duration2.count() << endl;

        
        cout << "Tree 2: " << endl;
        //cout<<" Buscando KNN... k= "<<k<<endl;
        start =  std::chrono::high_resolution_clock::now();
        pq = tree2.searchKNN({xr, yr , zr },k);
        stop = std::chrono::high_resolution_clock::now();
        duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time taken by KDTree: "    << duration1.count() << " microseconds" << endl;
        printKNN(pq);
        outp << duration1.count() << " ";

        //cout<<" Buscando KNN con fuerza bruta... k= "<<k<<endl;
        start = std::chrono::high_resolution_clock::now();
        pq = bruteForce(nodesTree2, {xr, yr, zr},k);
        stop = std::chrono::high_resolution_clock::now();
        duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time taken by Brute Force: "<< duration2.count() << " microseconds" << endl;
        printKNN(pq);
        outp << duration2.count() << endl;

        
        cout << "Tree 3: " << endl;
        //cout<<" Buscando KNN... k= "<<k<<endl;
        start =  std::chrono::high_resolution_clock::now();
        pq = tree3.searchKNN({xr, yr , zr },k);
        stop = std::chrono::high_resolution_clock::now();
        duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time taken by KDTree: " << duration1.count() << " microseconds" << endl;
        printKNN(pq);
        outp << duration1.count() << " ";    

        //cout<<" Buscando KNN con fuerza bruta... k= "<<k<<endl;
        start = std::chrono::high_resolution_clock::now();
        pq = bruteForce(nodesTree3, {xr, yr, zr},k);
        stop = std::chrono::high_resolution_clock::now();
        duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time taken by Brute Force: " << duration2.count() << " microseconds" << endl;
        printKNN(pq);
        outp << duration2.count() << endl;
    }
    outp.close();
}
