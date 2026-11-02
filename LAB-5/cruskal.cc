#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define edge pair<int,int>

class Graph {
private:
    vector<pair<int, edge>> G; // усі ребра (вага, (u, v))
    vector<pair<int, edge>> T; // ребра МКД
    int *parent;
    int V;
public:
    Graph(int V);
    void AddWeightedEdge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
};

Graph::Graph(int V) {
    this->V = V;
    parent = new int[V];
    for (int i = 0; i < V; i++)
        parent[i] = i;
    G.clear();
    T.clear();
}

void Graph::AddWeightedEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}

int Graph::find_set(int i) {
    if (i == parent[i])
        return i;
    return parent[i] = find_set(parent[i]); // оптимізація шляху
}

void Graph::union_set(int u, int v) {
    int root_u = find_set(u);
    int root_v = find_set(v);
    if (root_u != root_v) {
        parent[root_u] = root_v;
    }
}

void Graph::kruskal() {
    sort(G.begin(), G.end()); // сортування ребер за зростанням ваги
    for (int i = 0; i < G.size(); i++) {
        int uRep = find_set(G[i].second.first);
        int vRep = find_set(G[i].second.second);

        if (uRep != vRep) {
            T.push_back(G[i]); // додаємо до дерева
            union_set(uRep, vRep);
        }
    }
}

void Graph::print() {
    int total_weight = 0; // Змінна для підрахунку загальної ваги МКД
    
    cout << "Алгоритм Крускала (Результат)" << endl;
    cout << "Edge : Weight" << endl;
    for (int i = 0; i < T.size(); i++) {
        cout << (T[i].second.first + 1) << " - " << (T[i].second.second + 1) << " : " << T[i].first << endl;
        total_weight += T[i].first; // Додаємо вагу ребра до загальної суми
    }
    
    // Виведення загальної ваги мінімального кістякового дерева
    cout << "\nЗагальна вага мінімального кістякового дерева: " << total_weight << endl;
}

int main() {
    Graph g(8); // 8 вершин (від 0 до 7)
    
    // Додавання ребер згідно з Варіантом 12 (неорієнтований граф)
    g.AddWeightedEdge(0, 2, 1); // 1-3
    g.AddWeightedEdge(0, 3, 5); // 1-4
    g.AddWeightedEdge(0, 4, 3); // 1-5
    g.AddWeightedEdge(1, 4, 6); // 2-5
    g.AddWeightedEdge(1, 5, 1); // 2-6
    g.AddWeightedEdge(2, 3, 6); // 3-4
    g.AddWeightedEdge(2, 5, 7); // 3-6
    g.AddWeightedEdge(2, 7, 3); // 3-8
    g.AddWeightedEdge(3, 4, 2); // 4-5
    g.AddWeightedEdge(4, 6, 9); // 5-7
    g.AddWeightedEdge(5, 6, 3); // 6-7
    g.AddWeightedEdge(5, 7, 1); // 6-8
    g.AddWeightedEdge(6, 7, 4); // 7-8

    g.kruskal();
    g.print();

    return 0;
}
