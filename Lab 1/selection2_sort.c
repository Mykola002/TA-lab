#include <stdio.h>

void selection_sort(int arr[], int n, int *comparisons, int *assignments) {
    *comparisons = 0;
    *assignments = 0;

    // Зовнішній цикл ітерується по всьому масиву від 0 до n-2 (n-1 проходів)
    for (int i = 0; i < n - 1; i++) {
        // Припускаємо, що поточний елемент є мінімальним
        int min_index = i;
        (*assignments)++; // Присвоєння змінній min_index

        // Внутрішній цикл шукає найменший елемент в решті масиву
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++; // Операція порівняння
            if (arr[j] < arr[min_index]) {
                min_index = j;
                (*assignments)++; // Присвоєння змінній min_index
            }
        }

        // Обмін елементів, якщо знайдено новий мінімальний
        (*comparisons)++; // Операція порівняння (min_index != i)
        if (min_index != i) {
            // Обмін елементів
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
            (*assignments) += 3; // Три присвоєння при обміні
        }
    }
}

// Допоміжна функція для виводу масиву
void print_array(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    // Варіант 12
    int my_list[] = {53, 100, 44, 74, 53, 38, 82, 65, 28};
    int n = sizeof(my_list) / sizeof(my_list[0]);

    // Створення копії масиву, щоб не змінювати оригінал
    int sorted_list[9];
    for (int i = 0; i < n; i++) {
        sorted_list[i] = my_list[i];
    }

    int comps = 0, assigns = 0;

    // Виклик функції сортування
    selection_sort(sorted_list, n, &comps, &assigns);

    // Вивід результатів
    printf("Оригінальний список: ");
    print_array(my_list, n);

    printf("Відсортований список: ");
    print_array(sorted_list, n);

    printf("Кількість порівнянь: %d\n", comps);
    printf("Кількість присвоєнь: %d\n", assigns);

    return 0;
}
