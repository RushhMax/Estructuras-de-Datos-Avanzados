#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <cstdlib>
#include "R_RBT.cpp"

using namespace std;

void guardar(int n, vector<double> &v){
    ofstream archivo("Compares.txt",  ios::app);
    archivo << n << " ";
    for (const double &time : v) {
        archivo << time << " ";
    }
    archivo << endl;
    archivo.close();
}

int main(){
    srand(time(NULL));
    ofstream archivo;
    archivo.open("Compares.txt",  ios::out);
    archivo.close();

    for(int n = 100 ; n <= 10000 ; n+=50){
        RedBlack_Tree<int> RBT;        
        vector<int> numbersRAN;

        //cout<<"\nAgregando>>\n";
        for(int i=0; i<n; i++){
            int random = rand() % (n*10);
            numbersRAN.push_back(random);
            RBT.Add(random);
        }

        RBT.dibujar();

        vector<double> compares;
        for (int i = 0; i < 100; i++) {
            int search_value = numbersRAN[rand() % n];
            // COMPARACIONES 
            compares.push_back(RBT.FindCompares(search_value));
        }

        cout<<"\n Promedio Compares > "<<accumulate(compares.begin(), compares.end(), 0.0) / compares.size() << "\n";
        guardar(n, compares);
    }
}
