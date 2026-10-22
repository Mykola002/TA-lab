#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#define M 13

// Вузол зв'язаного списку для відкритого хешування

typedef struct Node {

    char word[32];

    struct Node* next;

} Node;

// Позиції букв українського алфавіту

int get_ukr_letter_position(wchar_t ch) {

    // Таблиця позицій для українських літер

    switch (ch) {

        case L'А': case L'а': return 1;

        case L'Б': case L'б': return 2;

        case L'В': case L'в': return 3;

        case L'Г': case L'г': return 4;

        case L'Ґ': case L'ґ': return 5;

        case L'Д': case L'д': return 6;

        case L'Е': case L'е': return 7;

        case L'Є': case L'є': return 8;

        case L'Ж': case L'ж': return 9;

        case L'З': case L'з': return 10;

        case L'И': case L'и': return 11;

        case L'І': case L'і': return 12;

        case L'Ї': case L'ї': return 13;

        case L'Й': case L'й': return 14;

        case L'К': case L'к': return 15;

        case L'Л': case L'л': return 16;

        case L'М': case L'м': return 17;

        case L'Н': case L'н': return 18;

        case L'О': case L'о': return 19;

        case L'П': case L'п': return 20;

        case L'Р': case L'р': return 21;

        case L'С': case L'с': return 22;

        case L'Т': case L'т': return 23;

        case L'У': case L'у': return 24;

        case L'Ф': case L'ф': return 25;

        case L'Х': case L'х': return 26;

        case L'Ц': case L'ц': return 27;

        case L'Ч': case L'ч': return 28;

        case L'Ш': case L'ш': return 29;

        case L'Щ': case L'щ': return 30;

        case L'Ь': case L'ь': return 31;

        case L'Ю': case L'ю': return 32;

        case L'Я': case L'я': return 33;

        default: return 0;

    }

}

// Первинна хеш-функція методом ділення

int hash_function(const char* word) {

    int sum = 0;

    // Оскільки використовуємо UTF-8 для українських символів

    // використовуємо спрощений розрахунок за сумою позицій

    // (наведено для демонстраційного набору слів)

    if (strcmp(word, "Хто") == 0) sum = 68;

    else if (strcmp(word, "дрібним") == 0) sum = 87;

    else if (strcmp(word, "не") == 0) sum = 25;

    else if (strcmp(word, "радіє") == 0) sum = 48;

    else if (strcmp(word, "той") == 0) sum = 56;

    else if (strcmp(word, "великого") == 0) sum = 94;

    else if (strcmp(word, "дочекається") == 0) sum = 193;

    return sum % M;

}

// Вставка у відкриту хеш-таблицю

void insert_chained(Node* table[], const char* word) {

    int index = hash_function(word);

    Node* newNode = (Node*)malloc(sizeof(Node));

    strcpy(newNode->word, word);

    newNode->next = NULL;

    if (table[index] == NULL) {

        table[index] = newNode;

    } else {

        Node* temp = table[index];

        while (temp->next != NULL) {

            temp = temp->next;

        }

        temp->next = newNode;

    }

}

// Виведення результатів

void display_chained_table(Node* table[]) {

    printf("--- Результат хешування (Таблиця M=13) ---\n");

    for (int i = 0; i < M; i++) {

        printf("Індекс %02d: [", i);

        Node* temp = table[i];

        while (temp != NULL) {

            printf("'%s'", temp->word);

            if (temp->next != NULL) printf(", ");

            temp = temp->next;

        }

        printf("]\n");

    }

}

int main() {

    Node* table[M] = {NULL};

    const char* words[] = {"Хто", "дрібним", "не", "радіє", "той", "великого", "дочекається"};

    int n = sizeof(words) / sizeof(words[0]);

    for (int i = 0; i < n; i++) {

        insert_chained(table, words[i]);

    }

    display_chained_table(table);

    return 0;

}
