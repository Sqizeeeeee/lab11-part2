#include "avl.h"
#include <algorithm>

namespace avl {

/* --------------------------
 * Вспомогательные функции
 * -------------------------- */

/**
 * Возвращает высоту узла.
 */
static int height(Node* node) {
    return node ? node->height : 0;
}

/**
 * Вычисляет баланс-фактор узла.
 */
static int get_balance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

/**
 * Правый поворот вокруг узла y.
 */
static Node* rotate_right(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

/**
 * Левый поворот вокруг узла x.
 */
static Node* rotate_left(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

/* --------------------------
 * Вставка ключа с балансировкой
 * -------------------------- */
Node* insert(Node* node, int key) {
    if (!node)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // дубликаты не вставляем

    // обновляем высоту
    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = get_balance(node);

    // Левый левый случай
    if (balance > 1 && key < node->left->key)
        return rotate_right(node);

    // Правый правый случай
    if (balance < -1 && key > node->right->key)
        return rotate_left(node);

    // Левый правый случай
    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // Правый левый случай
    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

/* --------------------------
 * Построение AVL из массива
 * -------------------------- */
Node* build_avl_from_array(const std::vector<int>& arr) {
    Node* root = nullptr;
    for (int key : arr) {
        root = insert(root, key);
    }
    return root;
}

/* --------------------------
 * Освобождение памяти дерева
 * -------------------------- */
void free_tree(Node* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    delete root;
}

} // namespace avl