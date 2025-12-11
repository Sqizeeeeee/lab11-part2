#include "tree23.h"
#include <algorithm>
#include <stdexcept>

namespace tree23 {

/* --------------------------
 * Вспомогательные функции
 * -------------------------- */

/**
 * Создание нового узла с ключом.
 */
static Node* create_node(int key) {
    Node* node = new Node();
    node->keys.push_back(key);
    return node;
}

/**
 * Освобождение памяти поддерева.
 */
void free_tree(Node* root) {
    if (!root) return;
    for (Node* child : root->children) {
        free_tree(child);
    }
    delete root;
}

/* --------------------------
 * Вставка в 2-3 дерево
 * -------------------------- */

/**
 * Вставка ключа в поддерево.
 *
 * @param node Текущий узел.
 * @param key Ключ для вставки.
 * @return Новый корень поддерева после возможного деления узла.
 */
static Node* insert_recursive(Node* node, int key, int* promoted_key = nullptr, Node** new_child = nullptr) {
    if (!node) {
        return create_node(key);
    }

    // Листовой узел
    if (node->children.empty()) {
        node->keys.push_back(key);
        std::sort(node->keys.begin(), node->keys.end());

        if (node->keys.size() > 2) {
            // Делим 3-ключевой узел
            Node* left = create_node(node->keys[0]);
            Node* right = create_node(node->keys[2]);
            *promoted_key = node->keys[1];

            Node* new_root = new Node();
            new_root->keys.push_back(*promoted_key);
            new_root->children.push_back(left);
            new_root->children.push_back(right);

            delete node;
            return new_root;
        }
        return node;
    }

    // Внутренний узел
    size_t i = 0;
    while (i < node->keys.size() && key > node->keys[i]) i++;
    Node* child_promoted = nullptr;
    int pk = 0;
    Node* new_c = nullptr;

    Node* child = insert_recursive(node->children[i], key, &pk, &new_c);

    node->children[i] = child;

    if (pk != 0) {
        // Вставляем продвинутый ключ
        node->keys.insert(node->keys.begin() + i, pk);
        node->children.insert(node->children.begin() + i + 1, new_c);

        if (node->keys.size() > 2) {
            // Делим 3-ключевой узел
            Node* left = new Node();
            left->keys.push_back(node->keys[0]);
            left->children.push_back(node->children[0]);
            left->children.push_back(node->children[1]);

            Node* right = new Node();
            right->keys.push_back(node->keys[2]);
            right->children.push_back(node->children[2]);
            right->children.push_back(node->children[3]);

            *promoted_key = node->keys[1];
            *new_child = right;

            node->keys = left->keys;
            node->children = left->children;

            delete left;
        }
    }

    return node;
}

Node* insert(Node* root, int key) {
    int promoted = 0;
    Node* new_child = nullptr;
    Node* new_root = insert_recursive(root, key, &promoted, &new_child);
    if (promoted != 0) {
        Node* root_node = new Node();
        root_node->keys.push_back(promoted);
        root_node->children.push_back(new_root);
        root_node->children.push_back(new_child);
        return root_node;
    }
    return new_root;
}

/* --------------------------
 * Построение 2-3 дерева из массива
 * -------------------------- */
Node* build_tree23_from_array(const std::vector<int>& arr) {
    Node* root = nullptr;
    for (int key : arr) {
        root = insert(root, key);
    }
    return root;
}

} // namespace tree23
