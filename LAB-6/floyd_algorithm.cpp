#include <iostream>
#include <iomanip>

using namespace std;

const int INF = 1e9;
const int V = 8;

void floydWarshall(int graph[V][V]) {
    int dist[V][V];

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    cout << "\nАлгоритм Флойда (Матриця найкоротших відстаней)" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << setw(5) << "INF";
            else
                cout << setw(5) << dist[i][j];
        }
        cout << endl;
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

    floydWarshall(graph);
    return 0;
}
