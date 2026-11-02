#include <iostream>
#include <cstring>
using namespace std;

#define INF 9999999
#define V 8 // Кількість вершин

int main() {
    // Матриця суміжності для Варіанта 12 (індексація від 0 до 7, що відповідає вершинам 1-8)
    int G[V][V] = {
        {0,   INF, 1,   5,   3,   INF, INF, INF}, // 1
        {INF, 0,   INF, INF, 6,   1,   INF, INF}, // 2
        {1,   INF, 0,   6,   INF, 7,   INF, 3},   // 3
        {5,   INF, 6,   0,   2,   INF, INF, INF}, // 4
        {3,   6,   INF, 2,   0,   INF, 9,   INF}, // 5
        {INF, 1,   7,   INF, INF, 0,   3,   1},   // 6
        {INF, INF, INF, INF, 9,   3,   0,   4},   // 7
        {INF, INF, 3,   INF, INF, 1,   4,   0}    // 8
    };

    int selected[V];
    memset(selected, false, sizeof(selected));
    selected[0] = true; // Починаємо з першої вершини (індекс 0)

    int no_edge = 0;
    int total_weight = 0; // Змінна для підрахунку загальної ваги МКД

    cout << "--- Алгоритм Прима (Результат) ---" << endl;
    cout << "Edge : Weight" << endl;

    while (no_edge < V - 1) {
        int min = INF;
        int x = 0, y = 0;

        for (int i = 0; i < V; i++) {
            if (selected[i]) {
                for (int j = 0; j < V; j++) {
                    if (!selected[j] && G[i][j] && G[i][j] != INF) {
                        if (min > G[i][j]) {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        
        // Виводимо ребро та його вагу (номери вершин від 1 до 8)
        cout << (x + 1) << " - " << (y + 1) << " : " << min << endl;
        
        total_weight += min; // Додаємо вагу поточного ребра до загальної суми
        selected[y] = true;
        no_edge++;
    }

    // Виведення загальної ваги мінімального кістякового дерева
    cout << "\nЗагальна вага мінімального кістякового дерева: " << total_weight << endl;

    return 0;
}
