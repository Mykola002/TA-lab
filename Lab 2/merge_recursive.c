#include <stdio.h>
#include <stdlib.h>

long long rec_comparisons = 0;
long long rec_assignments = 0;
long long rec_calls = 0;

void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void merge_recursive(int a[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Копіюємо дані у тимчасові масиви L[] та R[]
    for (int i = 0; i < n1; i++) {
        L[i] = a[left + i];
        rec_assignments++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = a[mid + 1 + j]; // ЗВЕРНИ УВАГУ: mid + 1 + j !
        rec_assignments++;
    }

    int i = 0, j = 0, k = left;
    rec_assignments += 3;

    // Злиття тимчасових масивів назад у a[left..right]
    while (i < n1 && j < n2) {
        rec_comparisons++;
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        rec_assignments += 2;
        k++;
    }

    // Докопіювання залишків L[], якщо є
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
        rec_assignments += 2;
    }

    // Докопіювання залишків R[], якщо є
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
        rec_assignments += 2;
    }

    free(L);
    free(R);
}

void merge_sort_recursive(int a[], int left, int right) {
    rec_calls++;
    if (left < right) {
        int mid = left + (right - left) / 2;
        rec_assignments++;

        merge_sort_recursive(a, left, mid);
        merge_sort_recursive(a, mid + 1, right);

        merge_recursive(a, left, mid, right);
    }
}

int main() {
    int arr[] = {53, 100, 44, 74, 53, 38, 82, 65, 28};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("--- РЕКУРСИВНЕ СОРТУВАННЯ ЗЛИИТЯМ ---\n");
    printf("Початковий масив: ");
    print_array(arr, n);

    merge_sort_recursive(arr, 0, n - 1);

    printf("Відсортований масив: ");
    print_array(arr, n);

    printf("\nРЕЗУЛЬТАТИ:\n");
    printf("Кількість порівнянь: %lld\n", rec_comparisons);
    printf("Кількість присвоювань: %lld\n", rec_assignments);
    printf("Рекурсивні виклики: %lld\n", rec_calls);

    return 0;
}
