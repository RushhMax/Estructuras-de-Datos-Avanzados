#include <iostream>
#include <list>
#include <math.h>
#include <fstream>
#include <utility> // Para std::make_p
#include <vector>

using namespace std;

struct NodoF {
    int                 m_Grado;
    pair<string,int>    m_Dato;
    NodoF*              m_Padre;
    list<NodoF*>        m_Sons;
    bool                m_Color;

    NodoF(const pair<string,int>& d){
        m_Dato = d;
        m_Grado = 0;
        m_Padre = nullptr;
        m_Color = false;
    }
};

class Fibonaci_Heap {
    public:
    list<NodoF*>     m_Roots;
    NodoF*           m_pMin;
    int              m_size;

    Fibonaci_Heap(){
        m_pMin = nullptr;
        m_size = 0;
    }
    ~Fibonaci_Heap();

    NodoF* Insert(const pair<string,int>& d);
    void Extrac_Min();
    void Delete(NodoF* e);
    void Decrease_Key(NodoF* e, const pair<string,int>& val);
    NodoF * GetMin();
    void showList();
    void ShowDot(NodoF* actual, ostream& out);
    void ShowDot(const string& filename);
    void Compactar();
    NodoF* Unir(NodoF* p, NodoF* q);
    void Update(const string& str);
};

/// IMplementacion para pares
void Fibonaci_Heap::Update(const string& str) {
    int veces = 0;
    bool doit = false;
    if(m_pMin->m_Dato.first == str) {
        cout << m_pMin->m_Dato.first << " " << m_pMin->m_Dato.second << endl;
        veces = m_pMin->m_Dato.second;
        Extrac_Min();
        doit = true;
    }else{
        for (auto it = m_Roots.begin(); !doit && it != m_Roots.end(); ++it) {
            if((*it)->m_Dato.first == str) {
                cout << (*it)->m_Dato.first << " " << (*it)->m_Dato.second << endl;
                veces = (*it)->m_Dato.second;
                m_Roots.remove(*it);
                Delete(*it);
                doit = true;
                break;
            }
            auto it2 = (*it)->m_Sons.begin();
            while (it2 != (*it)->m_Sons.end() && !doit) {
                if ((*it2)->m_Dato.first == str) {
                    cout << (*it2)->m_Dato.first << " " << (*it2)->m_Dato.second << endl;
                    veces = (*it2)->m_Dato.second;

                    // Almacenar un iterador temporal antes de eliminar
                    auto temp = it2;
                    ++it2;  // Avanzar el iterador antes de eliminar

                    // Eliminar el nodo de los hijos
                    (*it)->m_Sons.remove(*temp);
                    Delete(*temp);
                    doit = true;
                    break;
                } else {
                    ++it2;  // Solo avanzar si no se ha eliminado
                }
            }
        }
    }
    
    cout << "Se actualizo el valor de " << str << " a " << veces + 1 << endl;
    if(doit) Insert(make_pair(str, veces + 1));
}

void Fibonaci_Heap::showList() {
    for (auto it = m_Roots.begin(); it != m_Roots.end(); ++it) {
        cout << (*it)->m_Dato.first << " / " << (*it)->m_Dato.second << " [" << (*it)->m_Grado << "] \n ";
        for(auto it2 = (*it)->m_Sons.begin(); it2 != (*it)->m_Sons.end(); ++it2) {
            cout << "-> " << (*it2)->m_Dato.first << " / " << (*it2)->m_Dato.second << "[" << (*it2)->m_Grado << "] -> ";
        }
        cout << endl;
    }
}

NodoF* Fibonaci_Heap::Insert(const pair<string, int>& d) {
    NodoF* pNew = new NodoF(d);
    if (!m_pMin || d.second < m_pMin->m_Dato.second) m_pMin = pNew;
    m_Roots.push_back(pNew);
    m_size++;
    return pNew;
}

void Fibonaci_Heap::Extrac_Min() {
    if (!m_pMin) return;
    for (auto it = m_pMin->m_Sons.begin(); it != m_pMin->m_Sons.end(); ++it) {
        (*it)->m_Color = false; 
        (*it)->m_Padre = nullptr;
        m_Roots.push_back(*it);
    }

    m_Roots.remove(m_pMin);
    m_size--;
    Compactar();

    m_pMin = nullptr; // Resetear m_pMin
    for (auto it = m_Roots.begin(); it != m_Roots.end(); ++it) {
        if (!m_pMin || (*it)->m_Dato.second < m_pMin->m_Dato.second) {
            m_pMin = *it;
        }
    }
}

void Fibonaci_Heap::Delete(NodoF* e) {
    Decrease_Key(e, make_pair(e->m_Dato.first, m_pMin->m_Dato.second - 1));
    m_pMin = e; //!
    Extrac_Min();
}

void Fibonaci_Heap::Decrease_Key(NodoF* e, const pair<string, int>& val) {
    e->m_Dato = val; 
    if (e->m_Dato.second < m_pMin->m_Dato.second && !e->m_Padre) m_pMin = e; 
    if (e->m_Padre && e->m_Padre->m_Dato.second > val.second) {
        do {
            e->m_Color = false;
            e->m_Padre->m_Sons.remove(e);
            e->m_Padre->m_Grado--;
            m_Roots.push_front(e);
            e = e->m_Padre;
        } while (e->m_Padre && e->m_Padre->m_Color);

        if (e->m_Padre) e->m_Color = true;
        else e->m_Color = false;
    } 
}

NodoF* Fibonaci_Heap::GetMin() {
    return m_pMin;
}

void Fibonaci_Heap::Compactar() {
    const int size = ceil(log2(m_size));
    vector<NodoF*> vec(size, nullptr); // Usar vector

    auto it = m_Roots.begin();
    while (it != m_Roots.end()) {
        int grado = (*it)->m_Grado;
        if (!vec[grado]) { 
            vec[grado] = *it; 
            it++; 
        } else {
            NodoF* r = Unir(*it, vec[grado]);
            m_Roots.remove(vec[grado]);
            it = m_Roots.erase(it);
            m_Roots.push_back(r);
            vec[grado] = nullptr;
        }
    }
}

NodoF* Fibonaci_Heap::Unir(NodoF* p, NodoF* q) {
    if (p->m_Dato.second > q->m_Dato.second)
        swap(p, q);
    p->m_Sons.push_back(q);
    q->m_Padre = p;
    p->m_Grado++;
    return p;
}

void Fibonaci_Heap::ShowDot(NodoF* actual, ostream& out) {
    if (!actual) return;
    out << actual->m_Dato.first << "[label = \"{ {f: " << actual->m_Dato.second << "} | <f1> " << actual->m_Dato.first << "} \"];" << endl;
    for (auto it = actual->m_Sons.begin(); it != actual->m_Sons.end(); ++it) {
        out << actual->m_Dato.first << " -> " << (*it)->m_Dato.first << ";" << endl;
        ShowDot((*it), out);
    }
}

void Fibonaci_Heap::ShowDot(const string& filename) {
    ofstream out(filename);
    out << "digraph G {" << endl;
    out << "label= \"Fibonaci Heap\";" << endl;
    out << "node [shape = record];" << endl;
    for (auto it = m_Roots.begin(); it != m_Roots.end(); ++it) ShowDot((*it), out);
    out << "}" << endl;
    out.close();
}
//
// int main() {
//     Fibonaci_Heap* heap = new Fibonaci_Heap();
//
//     heap->Insert(make_pair("C", 3));
//     heap->Insert(make_pair("A", 1));
//     heap->Insert(make_pair("B", 2));
//    
//     heap->showList(); // Mostrar lista
//
//     //heap->Update("A");
//     //heap->Update("A");
//     //heap->Update("B");
//
//     heap->showList(); // Mostrar lista actualizada
//
//     heap->Extrac_Min(); // Extraer el mínimo
//     heap->showList(); // Mostrar lista después de extraer el mínimo
//
//     heap->ShowDot("Heap.dot"); // Mostrar lista
//     return 0;
// }
//
