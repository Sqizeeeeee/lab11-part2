#ifndef AVL_H
#define AVL_H

#include <vector>

/// Пространство имён для AVL дерева
namespace avl {

/// Узел AVL дерева
struct Node {
    int key;        ///< значение узла
    Node* left;     ///< левый потомок
    Node* right;    ///< правый потомок
    int height;     ///< высота узла

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

/**
 * Вставка ключа в AVL дерево.
 *
 * @param root Корень дерева.
 * @param key Ключ для вставки.
 * @return Новый корень дерева после балансировки.
 */
Node* insert(Node* root, int key);

/**
 * Построение AVL дерева из массива.
 *
 * @param arr Массив целых чисел.
 * @return Корень AVL дерева.
 */
Node* build_avl_from_array(const std::vector<int>& arr);

/**
 * Освобождение памяти AVL дерева.
 *
 * @param root Корень дерева.
 */
void free_tree(Node* root);

} // namespace avl

#endif // AVL_H
