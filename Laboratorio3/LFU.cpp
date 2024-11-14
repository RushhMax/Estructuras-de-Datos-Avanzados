#include <bits/stdc++.h>
#include "FibonaciHeap.cpp"

using namespace std;

int main(){
    Fibonaci_Heap * my_heap = new Fibonaci_Heap();
    map<string, NodoF*> my_hash;
    int max;cin>>max;
    string str; 
    
    cout<<"INSERTAR >> ";
    while(cin>>str && str != "-1"){
        if(my_hash.find(str) != my_hash.end()){
            cout<<">Encontrado!\n";
            int veces = (*my_hash[str]).m_Dato.second;
            my_heap->Delete(my_hash[str]);
            my_hash[str] = my_heap->Insert(make_pair(str,veces+1));
            //my_heap->Update(str);
        } else{
            // INSERT
            cout<<">No encontrado!\n";
            if(my_hash.size() < max){
                // HAY ESPACIO
                cout<<">>Insertar sin LFU \n";
                my_hash[str] = my_heap->Insert(make_pair(str,1));
            }
            else{
                // NO HAY ESPACIO
                // ELIMINAR LRU
                cout<<">> Eliminando "<<my_heap->GetMin()->m_Dato.first<<"\n";
                my_hash.erase(my_heap->GetMin()->m_Dato.first);
                my_heap->Extrac_Min();
                my_hash[str] = my_heap->Insert(make_pair(str,1));
            }
        }

        cout<<"\n --- MY HEAP ---\n\n";
        my_heap->showList();
        my_heap->ShowDot("My_dot.dot");

        cout<<"\n --- MY HASH ---\n\n";
        for(auto  it = my_hash.begin(); it != my_hash.end(); it++){
            cout<<it->first<<" "<<it->second<<" / "<<(*it->second).m_Dato.first<<endl;
        }
        cout<<endl;
        cout<<"-----------------------------------\n";

        cout<<"INSERTAR >> ";
    }
}
