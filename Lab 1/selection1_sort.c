#include <stdio.h>

void print_step(int A[], int n, int step) {
    for (int i = 0; i < n; i++) {
        if (i == step) {
            printf("| ");
        }
        printf("%d ", A[i]);
    }
    if (step == n) {
        printf("|");
    }
    printf("\n");
}

int main() {
    // Вхідний масив для 12 варіанту
    int A[] = {53, 100, 44, 74, 53, 38, 82, 65, 28};
    int n = sizeof(A) / sizeof(A[0]);
    int B; // Тимчасова змінна для обміну

    printf("Початковий стан масиву:\n");
    print_step(A, n, 0);
    printf("\nПроцес сортування вибором:\n");

    // Реалізація алгоритму згідно з Лістингом 1.1
    for (int i = 0; i <= n - 2; i++) { // зовнішній цикл (0 to n-2)
        int min = i;
        
        for (int j = i + 1; j <= n - 1; j++) { // внутрішній цикл (i+1 to n-1)
            if (A[j] < A[min]) {
                min = j;
            }
        }
        
        // Обмін A[i] та A[min]
        B = A[i];
        A[i] = A[min];
        A[min] = B;

        // Вивід стану масиву після ітерації
        print_step(A, n, i + 1);
    }

    return 0;
}
