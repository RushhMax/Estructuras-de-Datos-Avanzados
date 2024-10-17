#include<iostream>
#include <fstream>
using namespace std;

template<class T>
class Nodo{
    public:
       T m_Dato;
       Nodo<T> * m_pSon[3];
       int m_Color;

       Nodo(T d){
           m_Dato = d;
           // Hijo Izquierdo
           m_pSon[0] = 0;
           // Hijo Derecho
           m_pSon[1] = 0;
           // Padre
           m_pSon[2] = 0;
           // Color 0 = N ; 1 = R 
           m_Color = 1;
       } 
};

template<class T>
class RedBlack_Tree{
    private:
       Nodo<T> * m_pRoot;
       
    public:
        RedBlack_Tree(){
            m_pRoot = 0;
        }

        void RR(Nodo<T> *p){
            Nodo<T> * NodoTMP = new Nodo<T>(p->m_Dato);
            if(p->m_pSon[0]->m_pSon[1]) NodoTMP->m_pSon[0] = p->m_pSon[0]->m_pSon[1];
            NodoTMP->m_pSon[1] = p->m_pSon[1];
            NodoTMP->m_Color = p->m_Color;

            p->m_Dato = p->m_pSon[0]->m_Dato;
            p->m_Color = p->m_pSon[0]->m_Color;
            p->m_pSon[1] = NodoTMP;

            if(NodoTMP->m_pSon[0]) NodoTMP->m_pSon[0]->m_pSon[2] = NodoTMP;
            if(NodoTMP->m_pSon[1]) NodoTMP->m_pSon[1]->m_pSon[2] = NodoTMP;

            NodoTMP->m_pSon[2] = p;

            if(p->m_pSon[0]->m_pSon[0]) p->m_pSon[0] = p->m_pSon[0]->m_pSon[0];
            else p->m_pSon[0] = 0;

            if(p->m_pSon[0]) p->m_pSon[0]->m_pSon[2] = p;
        }

        void LR(Nodo<T> *p){
            Nodo<T> * NodoTMP = new Nodo<T>(p->m_Dato);
            if(p->m_pSon[1]->m_pSon[0]) NodoTMP->m_pSon[1] = p->m_pSon[1]->m_pSon[0];
            NodoTMP->m_pSon[0] = p->m_pSon[0];
            NodoTMP->m_Color = p->m_Color;

            p->m_Dato = p->m_pSon[1]->m_Dato;
            p->m_pSon[0] = NodoTMP;

            if(NodoTMP->m_pSon[0]) NodoTMP->m_pSon[0]->m_pSon[2] = NodoTMP;
            if(NodoTMP->m_pSon[1]) NodoTMP->m_pSon[1]->m_pSon[2] = NodoTMP;

            NodoTMP->m_pSon[2] = p;

            if(p->m_pSon[1]->m_pSon[1]) p->m_pSon[1] = p->m_pSon[1]->m_pSon[1];
            else p->m_pSon[1] = 0;

            if(p->m_pSon[1]) p->m_pSon[1]->m_pSon[2] = p;
        }
        
        bool Add(T D){
            return Add(D, m_pRoot, NULL);
        }

        bool Add(T D, Nodo<T> *&p, Nodo<T> *padre){
            if (!p){ p = new Nodo<T>(D); p->m_pSon[2] = padre; FixInsert(p); return true; }
            if (D == p->m_Dato) return false;
            return Add(D, p->m_pSon[p->m_Dato < D], p);
        }

        void FixInsert(Nodo<T> *p){
            if(!p->m_pSon[2]) {m_pRoot->m_Color = 0; return; }
            while (p->m_pSon[2]->m_Color == 1){
                Nodo<T> *abuelo = p->m_pSon[2]->m_pSon[2];
                Nodo<T> *tio = m_pRoot;
                if (p->m_pSon[2] == abuelo->m_pSon[0]){
                    if (abuelo->m_pSon[1]) tio = abuelo->m_pSon[1];
                    if (tio->m_Color == 1){ // CASO 1: PAPA Y TIO SON ROJOS
                        // CAMBIA DE COLOR
                        p->m_pSon[2]->m_Color = 0; // PAPA
                        tio->m_Color = 0; // TIO
                        abuelo->m_Color = 1; // ABUELO
                        if (abuelo->m_Dato != m_pRoot->m_Dato) p = abuelo;
                        else break;
                    } // CASO 2: PAPA ES ROJO, TIO NEGRO Y ADEMAS P ES HIJO DERECHO Y PADRE DE P ES HIJO IZQUIERDO /**tio->m_Color == 0 &&**/ 
                    else if (p == abuelo->m_pSon[0]->m_pSon[1]) LR(p->m_pSon[2]);
                    else { // CASO 3: PAPA ES ROJO, TIO NEGRO Y P ES HIJO IZQUIERDO
                        p->m_pSon[2]->m_Color = 0;
                        abuelo->m_Color = 1;
                        RR(abuelo);
                        if (abuelo->m_Dato != m_pRoot->m_Dato) p = abuelo;
                        else break;
                    }
                } else {
                    if (abuelo->m_pSon[0]) tio = abuelo->m_pSon[0];
                    if (tio->m_Color == 1) {
                        p->m_pSon[2]->m_Color = 0;
                        tio->m_Color = 0;
                        abuelo->m_Color = 1;
                        if (abuelo->m_Dato != m_pRoot->m_Dato) p = abuelo;
                        else break;
                    } else if (p == abuelo->m_pSon[1]->m_pSon[0]) RR(p->m_pSon[2]);
                    else {
                        p->m_pSon[2]->m_Color = 0;
                        abuelo->m_Color = 1;
                        LR(abuelo);
                        if (abuelo->m_Dato != m_pRoot->m_Dato) p = abuelo;   
                        else break;
                    }
                }
            }
            m_pRoot->m_Color = 0;
        }

        bool Remove(T D){
            return Remove(D, &(m_pRoot));
        }

        bool Remove(T D, Nodo<T> **p_tmp){
            if (!(*p_tmp)) return false;
            if ((*p_tmp)->m_Dato == D){
                if ((*p_tmp)->m_pSon[0] && !(*p_tmp)->m_pSon[1]){
                    Nodo<T> *p_tmp1 = *p_tmp;
                    (*p_tmp) = (*p_tmp)->m_pSon[0];
                    FixRemove(*p_tmp);
                    delete p_tmp1;
                    p_tmp1 = 0;
                    return true;
                }else if (!(*p_tmp)->m_pSon[0] && (*p_tmp)->m_pSon[1]){
                    Nodo<T> *p_tmp1 = *p_tmp;
                    (*p_tmp) = (*p_tmp)->m_pSon[1];
                    FixRemove(*p_tmp);
                    delete p_tmp1;
                    p_tmp1 = 0;
                    return true;
                }else if ((*p_tmp)->m_pSon[0] && (*p_tmp)->m_pSon[1]){
                    Nodo<T> *p_tmp1 = *p_tmp;
                    Nodo<T> *p_tmp2 = (*p_tmp)->m_pSon[1], *p_tmp3 = (*p_tmp)->m_pSon[1], *p;
                    while (p_tmp2->m_pSon[0]){
                        p = p_tmp2;
                        p_tmp2 = p_tmp2->m_pSon[0];
                    }
                    Nodo<T> *p_tmpSon = p_tmp2->m_pSon[1];
                    p_tmp2->m_pSon[0] = (*p_tmp)->m_pSon[0];
                    if (p_tmp2 != p_tmp3){
                        p_tmp2->m_pSon[1] = p_tmp3;
                        p->m_pSon[0] = p_tmpSon;
                    }

                    *p_tmp = p_tmp2;
                    FixRemove(*p_tmp);
                    delete p_tmp1;
                    p_tmp1 = 0;
                    return true;
                }else{
                    FixRemove(*p_tmp);
                    delete *p_tmp;
                    *p_tmp = 0;
                    return true;
                }
            }
            return Remove(D, &((*p_tmp)->m_pSon[(*p_tmp)->m_Dato < D]));
        }

        void FixRemove(Nodo<T> *p){
            while(p->m_Dato != m_pRoot->m_Dato && p->m_Color == 0){
                Nodo<T> * p_tmp = m_pRoot;
                if(p->m_pSon[2]->m_pSon[0] == p){
                    if(p->m_pSon[2]->m_pSon[1]) p_tmp = p->m_pSon[2]->m_pSon[1];
                    if(p_tmp){
                        if(p_tmp->m_Color == 1){
                            p_tmp->m_Color = 0;
                            p->m_pSon[2]->m_Color = 1;
                            LR(p->m_pSon[2]);
                            p_tmp = p->m_pSon[2]->m_pSon[1];
                        }
                        if(!p_tmp->m_pSon[0] && !p_tmp->m_pSon[1]){
                            p_tmp->m_Color = 1;
                            p = p->m_pSon[2];
                        } else if (p_tmp->m_pSon[0]->m_Color == 0 && p_tmp->m_pSon[1]->m_Color == 0) {
                            p_tmp->m_Color = 1;
                            p = p->m_pSon[2];
                        } else if(p_tmp->m_pSon[1]->m_Color == 0){
                            p_tmp->m_pSon[0]->m_Color = 0;
                            p_tmp->m_Color = 1;
                            RR(p_tmp);
                            p_tmp = p->m_pSon[2]->m_pSon[1];
                        } else {
                            p_tmp->m_Color = p->m_pSon[2]->m_Color;
                            p->m_pSon[2]->m_Color = 0;
                            if(p_tmp->m_pSon[1]) p_tmp->m_pSon[1]->m_Color = 0;
                            LR(p->m_pSon[2]);
                            p = m_pRoot;
                        }
                    }
                } else if(p->m_pSon[2]->m_pSon[1] == p) {
                    if(p->m_pSon[2]->m_pSon[0]) p_tmp = p->m_pSon[2]->m_pSon[0];
                    if(p_tmp){
                        if(p_tmp->m_Color == 1){
                            p_tmp->m_Color = 0;
                            p->m_pSon[2]->m_Color = 1;
                            RR(p->m_pSon[2]);
                            p_tmp = p->m_pSon[2]->m_pSon[0];
                        }
                        if(!p_tmp->m_pSon[0] && !p_tmp->m_pSon[1]){
                            p_tmp->m_Color = 1;
                            p = p->m_pSon[2];
                        } else if (p_tmp->m_pSon[0]->m_Color == 0 && p_tmp->m_pSon[1]->m_Color == 0) {
                            p_tmp->m_Color = 1;
                            p = p->m_pSon[2];
                        } else if(p_tmp->m_pSon[0]->m_Color == 0){
                            p_tmp->m_pSon[1]->m_Color = 0;
                            p_tmp->m_Color = 1;
                            RR(p_tmp);
                            p_tmp = p->m_pSon[2]->m_pSon[0];
                        } else {
                            p_tmp->m_Color = p->m_pSon[2]->m_Color;
                            p->m_pSon[2]->m_Color = 0;
                            if(p_tmp->m_pSon[0]) p_tmp->m_pSon[0]->m_Color = 0;
                            LR(p->m_pSon[2]);
                            p = m_pRoot;
                        }
                    }                    
                }
            }
            p->m_Color = 0;
        }

        void print(){
            print(m_pRoot);
        }

        void print(Nodo<T> *r){
            if (!r) return;
            cout<<r->m_Dato<<" ";
            //cout << " COLOR> " << r->m_Color << " dir> " << r << " _ data> " << r->m_Dato << " _ dirdirLEFT> " << &r->m_pSon[0] << " _ dirdirRIGHT> " << &r->m_pSon[1] << " _ dirdirPADRE> " << &r->m_pSon[2] << " _ dirLEFT> " << r->m_pSon[0] << " _dirRIGHT> " << r->m_pSon[1] << " _dirPADRE> " << r->m_pSon[2] << "\n";
            print(r->m_pSon[0]);
            print(r->m_pSon[1]);
        }
        void dibujar(){
            ofstream archivo;
            archivo.open("RBT.dot");
            archivo << "graph B {\n";
            dibujar(m_pRoot, archivo);
            archivo << "\n}";
            archivo.close();
            //system("E: & cd Projects & cd First_Year & cd Laboratorio_ED_II & cd Graphviz & cd bin & dot AVL_HEIGHT.dot -o AVL_HEIGHT.png -Tpng & AVL_HEIGHT.png");
        }

        void dibujar(Nodo<T> *r, ofstream &archivo){
            if (!r)
                return;
            archivo << r->m_Dato << "[label = \"" << r->m_Dato << " | " << r->m_Color << "\" ]; \n";
            if (r->m_pSon[0])
                archivo << r->m_Dato << " -- " << r->m_pSon[0]->m_Dato << ";\n";
            if (r->m_pSon[1])
                archivo << r->m_Dato << " -- " << r->m_pSon[1]->m_Dato << ";\n";
            dibujar(r->m_pSon[0], archivo);
            dibujar(r->m_pSon[1], archivo);
        }

        Nodo<T> *Find(T D){
            if (!m_pRoot)
                return nullptr;
            Nodo<T> *p_tmp = m_pRoot;
            while (p_tmp){
                if (p_tmp->m_Dato == D)
                    return p_tmp;
                p_tmp = p_tmp->m_pSon[p_tmp->m_Dato < D];
            }
            return nullptr;
        }

        int FindCompares(T D){
            if (!m_pRoot)
                return 0;
            Nodo<T> *p_tmp = m_pRoot;
            int cont = 0;
            while (p_tmp){
                if (p_tmp->m_Dato == D)
                    return cont;
                p_tmp = p_tmp->m_pSon[p_tmp->m_Dato < D];
                cont++;
            }
            return 0;
        }

        Nodo<T> *Minimun(RedBlack_Tree<T> y){
            if (!y.m_pRoot)
                return NULL;
            Nodo<T> *p_tmp = y.m_pRoot;
            while (p_tmp->m_pSon[0]){
                p_tmp = p_tmp->m_pSon[0];
            }
            return p_tmp;
        }

};

// RDD
int test1()
{
    RedBlack_Tree<int> A;
    A.Add(4);
    A.print();
    A.Add(14);
    A.print();
    A.Add(24);
    A.print();
    cout << "The test1 work perfectly. Nice work :)" << endl;

    return 1;
}
// RII
int test2()
{
    RedBlack_Tree<int> A;
    A.Add(24);
    A.print();
    A.Add(14);
    A.print();
    A.Add(2);
    A.print();
    cout << "The test2 work perfectly. Good Work :)" << endl;
    return 1;
}
// RDI
int test3()
{
    RedBlack_Tree<int> A;
    A.Add(4);
    A.print();
    A.Add(14);
    A.print();
    A.Add(10);
    A.print();
    cout << "The test3 work perfectly. Good Work :)" << endl;
    return 1;
}
// RID
int test4()
{
    RedBlack_Tree<int> A;
    A.Add(24);
    A.print();
    A.Add(14);
    A.print();
    A.Add(18);
    A.print();
    cout << "The test4 work perfectly. Good Work :)" << endl;
    return 1;
}

int test5()
{
    RedBlack_Tree<int> A;
    A.Add(100);
    A.Add(50);
    A.Add(200);
    A.Add(80);
    A.Add(150);
    A.Add(400);
    A.Add(125);
    A.Add(600);

    A.print();

    A.dibujar();

    //A.Remove(80);
    //A.dibujar();

    return 1;
}

// FINAL
int test6()
{
    RedBlack_Tree<int> A;
    // Insert the correct includes
    srand(10);
    for (int i = 0; i < 100; i++)
    {
        // Insert the correct includes
        int a = rand() % 1000;
        //cout<<"\n INSERTANDO "<<a<<endl;
        A.Add(a);
    }

    //A.print();
    A.dibujar();

    int a;
    cout << " El menor elemento del arbol es > " << A.Minimun(A)->m_Dato;
    cout<<" Eliminando> ";cin>>a;
    A.Remove(a);

    A.dibujar();
    return 1;
}

// int main()
// {
//     cout << "Begin test " << endl;
//     //test1();
//     //test2();
//     //test3();
//     //test4();
//
//     //test5();
//
//     test6();
// }
