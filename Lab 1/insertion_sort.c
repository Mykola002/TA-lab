#include <stdio.h>

void insertion_sort(int arr[], int n, int *comparisons, int *assignments) {
    *comparisons = 0;
    *assignments = 0;

    // Цикл ітерується від другого елемента (індекс 1) до кінця
    for (int i = 1; i < n; i++) {
        // Зберігаємо поточний елемент для вставки
        int key = arr[i];
        (*assignments)++;

        // j - індекс попереднього елемента
        int j = i - 1;
        (*assignments)++;

        // Пересуваємо елементи, що більші за key, вправо
        while (j >= 0 && arr[j] > key) {
            (*comparisons)++; // Порівняння в умові while (arr[j] > key)
            arr[j + 1] = arr[j];
            (*assignments)++;
            j--;
            (*assignments)++;
        }

        // Додаткове порівняння, коли умова while стає false (якщо j >= 0)
        if (j >= 0) {
            (*comparisons)++;
        }

        // Вставляємо key на його правильне місце
        arr[j + 1] = key;
        (*assignments)++;
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

    // Виклик функції сортування вставками
    insertion_sort(sorted_list, n, &comps, &assigns);

    // Вивід результатів
    printf("Оригінальний список: ");
    print_array(my_list, n);

    printf("Відсортований список: ");
    print_array(sorted_list, n);

    printf("Кількість порівнянь: %d\n", comps);
    printf("Кількість присвоєнь: %d\n", assigns);

    return 0;
}
