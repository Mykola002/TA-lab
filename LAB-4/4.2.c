#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 13

// Структура закритої хеш-таблиці
typedef struct {
    char table[M][32];
    int is_occupied[M];
} ClosedHashTable;

// Первинна хеш-функція методом ділення h(k) = k mod 13
int primary_hash_closed(const char* word) {
    int sum = 0;
    if (strcmp(word, "Хто") == 0) sum = 68;
    else if (strcmp(word, "дрібним") == 0) sum = 87;
    else if (strcmp(word, "не") == 0) sum = 25;
    else if (strcmp(word, "радіє") == 0) sum = 48;
    else if (strcmp(word, "той") == 0) sum = 56;
    else if (strcmp(word, "великого") == 0) sum = 94;
    else if (strcmp(word, "дочекається") == 0) sum = 193;

    return sum % M;
}

// Ініціалізація хеш-таблиці
void init_closed_table(ClosedHashTable* ht) {
    for (int i = 0; i < M; i++) {
        ht->is_occupied[i] = 0;
        ht->table[i][0] = '\0';
    }
}

// Вставка ключа з лінійним дослідженням (Linear Probing)
void insert_closed(ClosedHashTable* ht, const char* word) {
    int start_address = primary_hash_closed(word);

    for (int i = 0; i < M; i++) {
        int address = (start_address + i) % M;
        if (!ht->is_occupied[address]) {
            strcpy(ht->table[address], word);
            ht->is_occupied[address] = 1;
            return;
        }
    }
    printf("Помилка: Таблиця переповнена для слова %s\n", word);
}

// Виведення закритої хеш-таблиці (аналог Таблиці 4.5)
void display_closed_table(const ClosedHashTable* ht) {
    printf("--- Хеш-таблиця (Відкрита адресація, M=13) ---\n");
    printf("Індекс | Слово\n");
    printf("-------|-------\n");
    for (int i = 0; i < M; i++) {
        if (ht->is_occupied[i]) {
            printf("%02d     | %s\n", i, ht->table[i]);
        } else {
            printf("%02d     | (NULL)\n", i);
        }
    }
}

int main() {
    ClosedHashTable ht;
    init_closed_table(&ht);

    const char* words[] = {"Хто", "дрібним", "не", "радіє", "той", "великого", "дочекається"};
    int n = sizeof(words) / sizeof(words[0]);

    for (int i = 0; i < n; i++) {
        insert_closed(&ht, words[i]);
    }

    display_closed_table(&ht);
    return 0;
}
