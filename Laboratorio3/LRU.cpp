#include <bits/stdc++.h>

using namespace std;

int main(){
    list<string> my_list; 
    map<string, list<string>::iterator> my_hash;
    int max;cin>>max;
    string str;
    int count = 0;
    
    cout<<"INSERTAR >> ";
    while(cin>>str && str != "0"){
        if(my_hash.find(str) != my_hash.end()){
            cout<<">Encontrado!\n";
            my_list.remove(str);
            my_list.emplace_front(str);

            my_hash[str] = my_list.begin();
        } else{
            // INSERT
            cout<<">No encontrado!\n";
            if(my_hash.size() < max){
                // HAY ESPACIO
                cout<<">>Insertar sin LRU \n";
                my_list.emplace_front(str);
                my_hash[str] = my_list.begin();
            }
            else{
                // NO HAY ESPACIO
                // ELIMINAR LRU
                cout<<">>Insertar con LRU \n";
                my_hash.erase(my_list.back());
                my_list.pop_back();
                my_list.emplace_front(str);
                my_hash[str] = my_list.begin();;
            }
        }

        cout<<"\n --- MY LIST ---\n\n";
        for(auto it = my_list.begin(); it != my_list.end(); it++){
            cout<<*it<<" - ";
        }
        cout<<endl;

        cout<<"\n --- MY HASH ---\n\n";
        cout<<" KEY  |  VALUE apuntando a (Dir) -> (Value in List) \n";
        for(auto  it = my_hash.begin(); it != my_hash.end(); it++){
            cout<<it->first<<" apuntando a "<<&(it->second)<<"->"<<*(it->second)<<endl;
        }
        cout<<endl;
        cout<<"-----------------------------------\n";

        cout<<"INSERTAR >> ";
    }
}
