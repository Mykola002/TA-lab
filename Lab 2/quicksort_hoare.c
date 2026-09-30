#include <stdio.h>

long long qs_comparisons = 0;
long long qs_assignments = 0;
long long qs_recursive_calls = 0;

void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int partition_hoare(int a[], int l, int r) {
    int pivot = a[l];
    qs_assignments++;

    int i = l - 1;
    int j = r + 1;
    qs_assignments += 2;

    while (1) {
        do {
            i++;
            qs_assignments++;
            qs_comparisons++;
        } while (a[i] < pivot);

        do {
            j--;
            qs_assignments++;
            qs_comparisons++;
        } while (a[j] > pivot);

        qs_comparisons++;
        if (i >= j) {
            return j;
        }
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        qs_assignments += 3;
    }
}

void quicksort_hoare(int a[], int l, int r) {
    qs_recursive_calls++;
    if (l < r) {
        int q = partition_hoare(a, l, r);
        qs_assignments++;

        quicksort_hoare(a, l, q);
        quicksort_hoare(a, q + 1, r);
    }
}

int main() {
    int arr[] = {53, 100, 44, 74, 53, 38, 82, 65, 28};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("ШВИДКЕ СОРТУВАННЯ (СХЕМА ХОАРА)\n");
    printf("Початковий масив: ");
    print_array(arr, n);

    quicksort_hoare(arr, 0, n - 1);

    printf("Відсортований масив: ");
    print_array(arr, n);

    printf("\nРЕЗУЛЬТАТИ:\n");
    printf("Кількість порівнянь: %lld\n", qs_comparisons);
    printf("Кількість присвоювань: %lld\n", qs_assignments);
    printf("Рекурсивні виклики: %lld\n", qs_recursive_calls);

    return 0;
}
