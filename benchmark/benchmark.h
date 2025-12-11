#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <vector>
#include <functional>
#include <string>

/// Пространство имён для бенчмарков.
namespace benchmark {

/**
 * Тип функции сортировки.
 *
 * SortFunction — это функция, которая принимает ссылку на std::vector<int>
 * и выполняет сортировку на месте.
 *
 * Пример:
 * SortFunction f = [](std::vector<int>& arr){ quicksort(arr); };
 */
using SortFunction = std::function<void(std::vector<int>&)>;

/**
 * Выполняет замер времени выполнения сортировки.
 *
 * Алгоритм:
 *  1. получает копию массива (исходный не изменяется)
 *  2. вызывает функцию сортировки
 *  3. возвращает время в миллисекундах
 *
 * @param func Функция сортировки.
 * @param data Массив данных, который нужно отсортировать.
 * @return Время выполнения в миллисекундах.
 */
double measure_sort_time(const SortFunction& func, const std::vector<int>& data);

/**
 * Выполняет несколько прогонов сортировки и возвращает среднее время.
 *
 * Используется для стабилизации результатов.
 *
 * @param func Функция сортировки.
 * @param data Массив данных.
 * @param runs Количество прогонов (по умолчанию 3).
 * @return Среднее время в миллисекундах.
 */
double measure_sort_time_avg(const SortFunction& func, const std::vector<int>& data, int runs = 3);

} // namespace benchmark

#endif // BENCHMARK_H