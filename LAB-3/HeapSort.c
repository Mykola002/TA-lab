#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sink(int arr[], int i, int n, int trace) {
    int k = i;
    while (1) {
        int j = 2 * k + 1; // Індекс лівого дочірнього елемента
        if (j >= n) break;

        // Знаходимо індекс найбільшого дочірнього елемента
        if (j + 1 < n && arr[j + 1] > arr[j]) {
            j += 1;
        }

        if (arr[k] >= arr[j]) break;

        if (trace) {
            printf("  [Sink] Міняємо місцями батька %d (індекс %d) та дочірній елемент %d (індекс %d)\n", 
                   arr[k], k, arr[j], j);
        }
        swap(&arr[k], &arr[j]);
        k = j;
    }
}

void printArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

void heapSort(int arr[], int n) {
    printf("Початковий масив: ");
    printArray(arr, n);
    printf("\n--- Фаза 1: Побудова максимальної купи ---\n");
    
    for (int i = (n / 2) - 1; i >= 0; i--) {
        printf("Занурюємо елемент з індексу %d: %d\n", i, arr[i]);
        sink(arr, i, n, 1);
    }
    
    printf("\nМасив після побудови купи: ");
    printArray(arr, n);
    printf("\n--- Фаза 2: Сортування ---\n");
    
    for (int i = n - 1; i > 0; i--) {
        printf("Міняємо місцями корінь (%d) та останній активний елемент (%d)\n", arr[0], arr[i]);
        swap(&arr[0], &arr[i]);
        printf("Розмір купи зменшився до %d. Відновлюємо властивості купи.\n", i);
        sink(arr, 0, i, 1);
        printf("Масив на поточному кроці: ");
        printArray(arr, n);
        printf("\n");
    }
}

int main() {
    int A[] = {53, 100, 44, 74, 53, 38, 82, 65, 28};
    int n = sizeof(A) / sizeof(A[0]);

    heapSort(A, n);

    printf("Відсортований масив: ");
    printArray(A, n);
    return 0;
}
