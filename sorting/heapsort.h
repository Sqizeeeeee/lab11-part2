#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>

/// Пространство имён для алгоритмов сортировки.
namespace sorting {

/**
 * Выполняет сортировку массива методом HeapSort (пирамидальная сортировка).
 *
 * Используется двоичная max-куча.
 *
 * Асимптотика:
 * - Лучший случай:  O(n log n)
 * - Средний случай: O(n log n)
 * - Худший случай:  O(n log n)
 *
 * Память: O(1), сортировка неустойчивая.
 *
 * @param arr Вектор целых чисел, который будет отсортирован на месте.
 */
void heap_sort(std::vector<int>& arr);

} // namespace sorting

#endif // HEAPSORT_H