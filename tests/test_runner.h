#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <string>
#include <vector>

/// Пространство имён для тестового модуля.
namespace tests {

/**
 * Структура для хранения результата одного теста сортировки.
 *
 * Пример:
 *  algorithm = "quicksort"
 *  data_type = "random"
 *  size = 100000
 *  time_ms = 12.45
 */
struct SortTestResult {
    std::string algorithm;   ///< Название алгоритма сортировки.
    std::string data_type;   ///< Тип входных данных: random, sorted, reversed.
    int size;                ///< Размер массива.
    double time_ms;          ///< Время выполнения сортировки в миллисекундах.
};

/**
 * Запускает все сортировки (merge, quick, heap) на всех CSV-файлах
 * в каталоге ../data, замеряет время выполнения и возвращает таблицу результатов.
 *
 * Формат результата:
 * [
 *    { "quicksort", "random",   1000, 0.45 },
 *    { "mergesort", "sorted",   1000, 0.67 },
 *    { "heapsort",  "reversed", 1000, 0.88 }
 * ]
 *
 * @param data_directory Путь к папке с CSV-файлами.
 * @return Вектор результатов тестов.
 */
std::vector<SortTestResult> run_all_sort_tests(const std::string& data_directory);

/**
 * Сохраняет результаты тестов в CSV-файл.
 *
 * Формат CSV:
 *  algorithm,size,data_type,time_ms
 *  quicksort,10000,random,12.45
 *  mergesort,10000,sorted,10.33
 *
 * @param filepath Путь к CSV файлу.
 * @param results Вектор результатов тестов.
 */
void save_test_results_to_csv(
    const std::string& filepath,
    const std::vector<SortTestResult>& results
);

} // namespace tests

#endif // TEST_RUNNER_H