#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;
const int V = 8; // Кількість вершин

void dijkstra(int graph[V][V], int src) {
    vector<int> dist(V, INF);
    vector<int> pred(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && graph[u][v] != INF) {
                if (dist[v] > dist[u] + graph[u][v]) {
                    dist[v] = dist[u] + graph[u][v];
                    pred[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    cout << "Алгоритм Дейкстри (Стартова вершина: 1)" << endl;
    cout << "Вершина \t Відстань \t Попередник" << endl;
    for (int i = 0; i < V; i++) {
        cout << (i + 1) << " \t\t " << dist[i] << " \t\t " << (pred[i] != -1 ? pred[i] + 1 : 0) << endl;
    }
}

int main() {
    int graph[V][V] = {
        {0,   INF, 1,   5,   3,   INF, INF, INF},
        {INF, 0,   INF, INF, 6,   1,   INF, INF},
        {1,   INF, 0,   6,   INF, 7,   INF, 3},
        {5,   INF, 6,   0,   2,   INF, INF, INF},
        {3,   6,   INF, 2,   0,   INF, 9,   INF},
        {INF, 1,   7,   INF, INF, 0,   3,   1},
        {INF, INF, INF, INF, 9,   3,   0,   4},
        {INF, INF, 3,   INF, INF, 1,   4,   0}
    };

    dijkstra(graph, 0); // Вершина 1 має індекс 0
    return 0;
}
