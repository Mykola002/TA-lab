#include <stdio.h>
#include <stdlib.h>

long long iter_comparisons = 0;
long long iter_assignments = 0;

void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void merge_iterative(int a[], int left, int mid, int right) {
    int n1 = mid - left;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = a[left + i];
        iter_assignments++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = a[mid + j];
        iter_assignments++;
    }

    int it1 = 0, it2 = 0, k = left;
    iter_assignments += 3;

    while (it1 < n1 && it2 < n2) {
        iter_comparisons++;
        if (L[it1] <= R[it2]) { // Забезпечення стійкості
            a[k] = L[it1];
            it1++;
        } else {
            a[k] = R[it2];
            it2++;
        }
        iter_assignments += 2;
        k++;
    }

    while (it1 < n1) {
        a[k] = L[it1];
        it1++;
        k++;
        iter_assignments += 2;
    }

    while (it2 < n2) {
        a[k] = R[it2];
        it2++;
        k++;
        iter_assignments += 2;
    }

    free(L);
    free(R);
}

void merge_sort_iterative(int a[], int n) {
    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < n - i; j += 2 * i) {
            int left = j;
            int mid = j + i;
            int right = (j + 2 * i < n) ? (j + 2 * i) : n;
            merge_iterative(a, left, mid, right);
        }
    }
}

int main() {
    int arr[] = {53, 100, 44, 74, 53, 38, 82, 65, 28};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("ІТЕРАТИВНЕ СОРТУВАННЯ ЗЛИИТЯМ \n");
    printf("Початковий масив: ");
    print_array(arr, n);

    merge_sort_iterative(arr, n);

    printf("Відсортований масив: ");
    print_array(arr, n);

    printf("\nРЕЗУЛЬТАТИ:\n");
    printf("Кількість порівнянь: %lld\n", iter_comparisons);
    printf("Кількість присвоювань: %lld\n", iter_assignments);

    return 0;
}
