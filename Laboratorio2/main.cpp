#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <cstdlib>
#include "R_RBT.cpp"

using namespace std::chrono; 
using namespace std;

void guardar(int n, vector<double> &v){
    ofstream archivo("Times.txt",  ios::app);
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
    archivo.open("Times.txt",  ios::out);
    archivo.close();

    for(int n = 100 ; n <= 10000 ; n+=50){
        RedBlack_Tree<int> RBT;        
        vector<int> numbersRAN;

        cout<<"\nAgregando>>\n";
        for(int i=0; i<n; i++){
            int random = rand() % (n*10);
            numbersRAN.push_back(random);
            RBT.Add(random);
        }

        RBT.dibujar();

        vector<double> times;
        int repetitions = 1000; 
        for (int i = 0; i < 100; i++) {
            int search_value = numbersRAN[rand() % n];
            auto start_time = high_resolution_clock::now();
            for (int j = 0; j < repetitions; j++) {
                RBT.Find(search_value); 
            }
            auto end_time = high_resolution_clock::now();
            auto time_spent_ns = duration_cast<nanoseconds>(end_time - start_time);  

            times.push_back(time_spent_ns.count() / repetitions);
            cout<<" / T / "<<time_spent_ns.count() / repetitions;
        }


        cout<<"\n Promedio > "<<accumulate(times.begin(), times.end(), 0.0) / times.size() << " ns\n";
        guardar(n, times);
    }
}
