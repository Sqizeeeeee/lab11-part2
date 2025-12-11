#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>

/// Пространство имён для алгоритмов сортировки.
namespace sorting {

/**
 * Выполняет сортировку массива методом QuickSort.
 *
 * Реализация использует рекурсивный алгоритм Хоара с разбиением.
 * Для уменьшения вероятности худшего случая pivot выбирается как средний из трёх:
 * arr[left], arr[right], arr[(left+right)/2].
 *
 * Асимптотика:
 * - Лучший случай:  O(n log n)
 * - Средний случай: O(n log n)
 * - Худший случай:  O(n²)
 *
 * @param arr Вектор целых чисел, который будет отсортирован на месте.
 */
void quick_sort(std::vector<int>& arr);

} // namespace sorting

#endif // QUICKSORT_H