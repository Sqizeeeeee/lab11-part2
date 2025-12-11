#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>

/// Пространство имён для алгоритмов сортировки.
namespace sorting {

/**
 * Выполняет сортировку массива методом Merge Sort.
 *
 * Сортировка устойчивая, асимптотика:
 * - Лучший случай:  O(n log n)
 * - Средний случай: O(n log n)
 *
 * @param arr Вектор целых чисел, который будет отсортирован на месте.
 */
void merge_sort(std::vector<int>& arr);

} // namespace sorting

#endif // MERGESORT_H