#ifndef TREE23_H
#define TREE23_H

#include <vector>

/// Пространство имён для 2-3 дерева
namespace tree23 {

/// Узел 2-3 дерева
struct Node {
    std::vector<int> keys;   ///< ключи (1 или 2 ключа)
    std::vector<Node*> children; ///< дети (0, 2 или 3)
    Node() : keys(), children() {}
};

/**
 * Вставка ключа в 2-3 дерево.
 *
 * @param root Корень дерева.
 * @param key Ключ для вставки.
 * @return Новый корень дерева после вставки.
 */
Node* insert(Node* root, int key);

/**
 * Построение 2-3 дерева из массива.
 *
 * @param arr Массив целых чисел.
 * @return Корень 2-3 дерева.
 */
Node* build_tree23_from_array(const std::vector<int>& arr);

/**
 * Освобождение памяти 2-3 дерева.
 *
 * @param root Корень дерева.
 */
void free_tree(Node* root);

} // namespace tree23

#endif // TREE23_H