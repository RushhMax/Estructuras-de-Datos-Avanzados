#include<bits/stdc++.h>

using namespace std;

int main(){
    int max;cin>>max;
    list<string> my_list;
    string str;

    cout<<"\nINSERTAR >> ";   
    while(cin>>str && str != "0"){
        bool found = false;
        for(auto it=my_list.begin();it!=my_list.end();it++){
            if(*it == str){
                cout<<">Encontrado!\n";
                my_list.erase(it);
                my_list.push_back(str);
                found = true;
            }
        }
        if(!found){
            cout<<">No encontrado!\n";
            if(my_list.size() == max){
                cout<<">>Eliminando: "<<my_list.front()<<endl;
                my_list.pop_front();
            }
            my_list.push_back(str);
        }

        cout<<"\n --- PRINTING FIFO --- \n\n";
        for(auto it=my_list.begin();it!=my_list.end();it++){
            cout<<*it<<" -- ";
        }
        cout<<endl;
        cout<<"-----------------------------------\n";

        cout<<"\nINSERTAR >> ";

    }
}
