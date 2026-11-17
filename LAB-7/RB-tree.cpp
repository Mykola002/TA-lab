#include <iostream>
#include <vector>

using namespace std;

// Перелік кольорів вузла
enum Color { RED, BLACK };

// Структура вузла Червоно-Чорного дерева
struct Node {
    int key;
    Color color;
    Node *left, *right, *parent;
};

// Глобальний лист (NIL-вузол) для позначення меж дерева
Node* NIL = nullptr;

// Функція створення нового вузла
Node* createNode(int key) {
    Node* n = new Node();
    n->key = key; 
    n->color = RED; // Новий вузол завжди червоний
    n->left = n->right = n->parent = NIL;
    return n;
}

// Лівий поворот навколо вузла x
void leftRotate(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Правий поворот навколо вузла x
void rightRotate(Node** root, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// Балансування після вставки (виправлення порушень ЧЧД)
void fixInsert(Node** root, Node* k) {
    while (k->parent && k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            Node* u = k->parent->parent->left; // Дядько
            if (u->color == RED) {
                u->color = BLACK; 
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) { 
                    k = k->parent; 
                    rightRotate(root, k); 
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(root, k->parent->parent);
            }
        } else {
            Node* u = k->parent->parent->right; // Дядько
            if (u->color == RED) {
                u->color = BLACK; 
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) { 
                    k = k->parent; 
                    leftRotate(root, k); 
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(root, k->parent->parent);
            }
        }
        if (k == *root) break;
    }
    (*root)->color = BLACK;
}

// Вставка ключа в Червоно-Чорне дерево
void insertRB(Node** root, int key) {
    Node* node = createNode(key);
    Node *y = nullptr, *x = *root;
    while (x != NIL) {
        y = x;
        x = (node->key < x->key) ? x->left : x->right;
    }
    node->parent = y;
    if (!y) *root = node;
    else if (node->key < y->key) y->left = node;
    else y->right = node;
    
    if (!node->parent) { node->color = BLACK; return; }
    if (!node->parent->parent) return;
    
    fixInsert(root, node);
}

// 1. Симетричний обхід (Inorder)
void inorderRB(Node* x) {
    if (x != NIL) {
        inorderRB(x->left);
        cout << x->key << "(" << (x->color == RED ? 'R' : 'B') << ") ";
        inorderRB(x->right);
    }
}

// 2. Прямий обхід (Preorder)
void preorderRB(Node* x) {
    if (x != NIL) {
        cout << x->key << "(" << (x->color == RED ? 'R' : 'B') << ") ";
        preorderRB(x->left);
        preorderRB(x->right);
    }
}

// 3. Зворотний обхід (Postorder)
void postorderRB(Node* x) {
    if (x != NIL) {
        postorderRB(x->left);
        postorderRB(x->right);
        cout << x->key << "(" << (x->color == RED ? 'R' : 'B') << ") ";
    }
}

int main() {
    // Кодування для коректного виведення українських символів у консолі
    system("chcp 65001 > nul");

    // Ініціалізація NIL-вузла
    NIL = new Node();
    NIL->color = BLACK; 
    NIL->left = NIL->right = NIL->parent = nullptr;

    Node* root = NIL;

    // Вхідні дані згідно з твоїм варіантом: {11, 42, 67, 55, 65, 78, 25, 50, 69}
    int arr[] = {11, 42, 67, 55, 65, 78, 25, 50, 69};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        insertRB(&root, arr[i]);
    }

    int choice;
    do {
        cout << "\n\n";
        cout << " МЕНЮ ЧЕРВОНО-ЧОРНОГО ДЕРЕВА\n";
        cout << "\n";
        cout << "1. Вивести результати обходів дерева\n";
        cout << "2. Додати новий елемент до дерева\n";
        cout << "3. Вихід\n";
        cout << "Оберіть дію: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nРезультати обходів побудованого дерева\n";
                cout << "Симетричний (Inorder):   ";
                inorderRB(root);
                cout << "\nПрямий (Preorder):       ";
                preorderRB(root);
                cout << "\nЗворотний (Postorder):   ";
                postorderRB(root);
                cout << "\n\n";
                break;
            case 2: {
                int val;
                cout << "Введіть число для вставки: ";
                cin >> val;
                insertRB(&root, val);
                cout << "Елемент " << val << " успішно додано та збалансовано!\n";
                break;
            }
            case 3:
                cout << "Вихід з програми...\n";
                break;
            default:
                cout << "Невірний вибір! Спробуйте ще раз.\n";
        }
    } while (choice != 3);

    return 0;
}
