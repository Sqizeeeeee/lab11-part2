#include "benchmark.h"
#include <chrono>

namespace benchmark {

double measure_sort_time(const SortFunction& func, const std::vector<int>& data) {
    // Копируем входной массив, чтобы не портить исходные данные
    std::vector<int> copy = data;

    // Засекаем время
    auto start = std::chrono::high_resolution_clock::now();

    // Выполняем сортировку
    func(copy);

    // Останавливаем таймер
    auto end = std::chrono::high_resolution_clock::now();

    // Вычисляем длительность в миллисекундах
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

double measure_sort_time_avg(const SortFunction& func, const std::vector<int>& data, int runs) {
    double total = 0.0;

    for (int i = 0; i < runs; i++) {
        total += measure_sort_time(func, data);
    }

    return total / static_cast<double>(runs);
}

} // namespace benchmark