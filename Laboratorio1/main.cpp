#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <chrono>
#include <climits>

using namespace std;

void bubbleSort(vector<float> &v);      // O(n^2)
void heapSort(vector<float> &v);        // O(nlogn)
void insertionSort(vector<float> &v);   // O(n^2)
void selectionSort(vector<float> &v);   // O(n^2)
void shellSort(vector<float> &v);       // O(n^2)
void mergeSort(vector<float> &v);       // O(nlogn)
void quickSort(vector<float> &v, int p, int r); // O(nlogn)

void sorted(vector<float> &v){
    for(int i=0; i < v.size() -1 ; i++){
        if(v[i] > v[i+1]) {
            cout<<" It's not sorted! Check your algorithm "<<endl;
            return;
        }
    }
    cout<<" SORTED "<<endl;
}

void bubbleSort(vector<float> &v){ // O(n^2)
    for (int i = v.size() - 1; i > 0; i--){
        bool intercambio = false;
        for (int j = 0; j < i; j++){ // solo itera hasta i porque es seguro que en cada iteracion el ultimo elemento sera el mayor
            if (v[j] > v[j + 1]){
                swap(v[j], v[j + 1]);
                intercambio = true;
            }
        }
        if (!intercambio) break;
    }
}

void make_heap(vector<float> &v, int n, int i){
    int max = i;
    int left = 2*i +1;
    int right = 2*i + 2; 

    if(left < n && v[left] > v[max]) max = left;
    if(right< n && v[right] > v[max]) max = right; 

    if(max!=i){
        swap(v[i], v[max]);
        make_heap(v, n, max);
    }
}
void heapSort(vector<float> &v){ // O(nlogn)
    int n = v.size();
    for(int i=n/2-1; i>=0; i--) {
        make_heap(v, n, i);
    }

    for(int i=n-1; i>=0; i--){
        swap(v[0],v[i]);
        make_heap(v,i,0);
    }
}

void insertionSort(vector<float> &v){
    for(int j=0; j<v.size(); j++){
        float key = v[j];
        int i = j-1;
        while(i>=0 && v[i]>key ){
            v[i+1] = v[i];
            i--;
        }
        v[i+1] = key;
    }
}

void selectionSort(vector<float> &v){
    int n = v.size();
    for(int i=0; i<n-1; i++){
        int minI = i;
        for(int j=i+1; j<n; j++){
            if(v[j]<v[minI]) minI = j;
        }    
        if(minI!=i) swap(v[minI], v[i]);
    }
}

void shellSort(vector<float> &v){
    int n = v.size();
    for(int gap=n/2; gap>0; gap/=2){
        for(int i=gap; i<n; i++){
            int temp = v.size();
            int j;
            for( j = i; j>=gap && v[j-gap]>temp; j-=gap){
                v[j] = v[j-gap];
            }
            v[j] = temp;
        }
    }

}


void merge(vector<float> &v, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<float> L(n1 + 1);
    vector<float> R(n2 + 1);

    for (int i = 0; i < n1; i++) {
        L[i] = v[p + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = v[q + i + 1];
    }

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
    }
}
void mergeSort(vector<float> &v) {
    int n = v.size();
    for (int m = 1; m <= n - 1; m = 2 * m) {
        for (int left = 0; left < n - 1; left += 2 * m) {
            int mid = min(left + m - 1, n - 1);
            int right = min(left + 2 * m - 1, n - 1);

            merge(v, left, mid, right);
        }
    }
}


int partition(vector<float> &v, int p, int r){
    float x = v[r];
    int i = p-1;
    for(int j=p; j<=r-1; j++){
        if(v[j]<=x){
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i+1], v[r]);
    return i+1;
}
void quickSort(vector<float> &v, int p, int r){
    if(p<r){
        int q = partition(v, p,r);
        quickSort(v, p, q-1);
        quickSort(v, q+1, r);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "File faltante! " << endl;
        return 1;
    }

    map<int,vector<double>> tiempos;

    tiempos[0].push_back(0.25);
    tiempos[0].push_back(0.5);
    tiempos[0].push_back(1.0);

    int nro = 1;
    while(argv[nro]){
        vector<float> valores;  
        ifstream datos(argv[nro]); 
        if (!datos) {
            cerr << "Error: File no existente " << argv[1] << endl;
            return 1;
        }   
        float valor;
        while(datos >> valor){
            valores.push_back(valor);
        }
        datos.close();

        vector<float> bubble = valores;
        vector<float> heap = valores;
        vector<float> insertion = valores;
        vector<float> selection = valores;
        vector<float> shell = valores;
        vector<float> merge = valores;    
        vector<float> quick = valores;

        cout<<argv[nro]<<endl;

        // cout<<" Heap Sort -> ";
        // auto inicio = std::chrono::high_resolution_clock::now();
        // heapSort(heap);
        // auto fin = std::chrono::high_resolution_clock::now();    
        // std::chrono::duration<double, milli> duracion = fin - inicio;
        // std::cout << duracion.count() << " milisegundos";
        // tiempos[1].push_back(duracion.count());
        // sorted(heap);

        // cout<<" Shell Sort -> ";
        // inicio = std::chrono::high_resolution_clock::now();
        // shellSort(shell);
        // fin = std::chrono::high_resolution_clock::now();    
        // duracion = fin - inicio;
        // std::cout << duracion.count() << " milisegundos";
        // tiempos[2].push_back(duracion.count());
        // sorted(shell);
        
        // cout<<" Merge Sort -> ";
        // inicio = std::chrono::high_resolution_clock::now();
        // mergeSort(merge);
        // fin = std::chrono::high_resolution_clock::now();    
        // duracion = fin - inicio;
        // std::cout << duracion.count() << " milisegundos";
        // tiempos[3].push_back(duracion.count());
        // sorted(merge);

        // cout<<" Quick Sort -> ";
        // inicio = std::chrono::high_resolution_clock::now();
        // quickSort(quick, 0, quick.size() - 1);
        // fin = std::chrono::high_resolution_clock::now();    
        // duracion = fin - inicio;
        // std::cout << duracion.count() << " milisegundos";
        // tiempos[4].push_back(duracion.count());
        // sorted(quick);

        cout<<" Bubble Sort -> ";
        auto inicio = std::chrono::high_resolution_clock::now();
        bubbleSort(bubble);
        auto fin = std::chrono::high_resolution_clock::now();    
        std::chrono::duration<double,  std::ratio<60>> duracion = fin - inicio;
        std::cout << duracion.count() << " milisegundos";
        tiempos[5].push_back(duracion.count());
        sorted(bubble);

        cout<<" Insertion Sort -> ";
        inicio = std::chrono::high_resolution_clock::now();
        insertionSort(insertion);
        fin = std::chrono::high_resolution_clock::now();    
        duracion = fin - inicio;
        std::cout << duracion.count() << " milisegundos";
        tiempos[6].push_back(duracion.count());
        sorted(insertion);

        cout<<" Selection Sort -> ";
        inicio = std::chrono::high_resolution_clock::now();
        selectionSort(selection);
        fin = std::chrono::high_resolution_clock::now();    
        duracion = fin - inicio;
        std::cout << duracion.count() << " milisegundos";
        tiempos[7].push_back(duracion.count());
        sorted(selection);
        nro++;
    }

    ofstream fileOut("tiempos.txt");
    for(auto it = tiempos.begin(); it!=tiempos.end(); it++){
        for(int i=0; i<it->second.size(); i++){
            fileOut<<it->second[i]<<" ";
        }
        fileOut<<endl;
    }
    fileOut.close();
    
}
