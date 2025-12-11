#include "test_runner.h"
#include "../io/csv_reader.h"
#include "../io/csv_writer.h"
#include "../sorting/mergesort.h"
#include "../sorting/quicksort.h"
#include "../sorting/heapsort.h"
#include "../benchmark/benchmark.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

namespace tests {

// Алиасы для использования существующих глобальных функций
namespace sorting = ::sorting;
namespace benchmark = ::benchmark;

/* --------------------------
 * Чтение существующего CSV
 * -------------------------- */
static std::vector<std::vector<std::string>> read_existing_csv(const std::string& filepath) {
    std::vector<std::vector<std::string>> rows;
    std::ifstream f_in(filepath);
    if (!f_in.is_open()) return rows;

    std::string line;
    std::getline(f_in, line); // пропускаем заголовок
    while (std::getline(f_in, line)) {
        std::stringstream ss(line);
        std::string col1, col2;
        if (!std::getline(ss, col1, ',')) continue;
        if (!std::getline(ss, col2, ',')) continue;
        rows.push_back({col1, col2});
    }
    return rows;
}

/* --------------------------
 * Запуск всех тестов сортировок
 * -------------------------- */
std::vector<SortTestResult> run_all_sort_tests(const std::string& data_directory) {
    std::vector<SortTestResult> all_results;

    for (const auto& entry : fs::directory_iterator(data_directory)) {
        if (!entry.is_regular_file()) continue;

        std::string filepath = entry.path().string();
        std::vector<int> arr = io::read_csv_int_one_column(filepath);

        struct Algo {
            std::string name;
            void(*func)(std::vector<int>&);
        };

        std::vector<Algo> algorithms = {
            {"merge", sorting::merge_sort},
            {"quick", sorting::quick_sort},
            {"heap",  sorting::heap_sort}
        };

        for (auto& algo : algorithms) {
            std::vector<int> copy = arr;
            double time_ms = benchmark::measure_sort_time_avg(algo.func, copy);
            all_results.push_back({algo.name, "random", static_cast<int>(arr.size()), time_ms});

            std::string dir = "results/random";
            fs::create_directories(dir);
            std::string out_file = dir + "/" + algo.name + ".csv";

            std::vector<std::vector<std::string>> rows;
            if (fs::exists(out_file)) rows = read_existing_csv(out_file);
            rows.push_back({std::to_string(arr.size()), std::to_string(time_ms)});
            io::write_csv(out_file, {"size","time_ms"}, rows);
        }
    }

    return all_results;
}

/* --------------------------
 * Сохранение результатов тестов в CSV
 * -------------------------- */
void save_test_results_to_csv(const std::string& filepath, const std::vector<SortTestResult>& results) {
    std::vector<std::vector<std::string>> rows;
    for (auto& r : results) {
        rows.push_back({r.algorithm, std::to_string(r.size), r.data_type, std::to_string(r.time_ms)});
    }
    fs::create_directories(fs::path(filepath).parent_path());
    io::write_csv(filepath, {"algorithm","size","data_type","time_ms"}, rows);
}

} // namespace tests