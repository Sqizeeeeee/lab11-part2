#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include <fstream>

#include "avl/avl.h"
#include "tree23/tree23.h"
#include "io/csv_reader.h"
#include "io/csv_writer.h"
#include "benchmark/benchmark.h"
#include "sorting/mergesort.h"
#include "sorting/quicksort.h"
#include "sorting/heapsort.h"
#include "tests/test_runner.h"

// Подключаем nlohmann/json (json.hpp должен быть в include)
#include "json.hpp"
using json = nlohmann::json;

namespace fs = std::filesystem;

/* --------------------------
 * Сериализация AVL дерева в JSON
 * -------------------------- */
json avl_to_json(avl::Node* node) {
    if (!node) return nullptr;
    json j;
    j["key"] = node->key;
    j["left"] = avl_to_json(node->left);
    j["right"] = avl_to_json(node->right);
    return j;
}

int main() {
    std::cout << "Лабораторная работа: Деревья и Сортировки\n";

    std::string data_dir = "../data";

    // ---------------------------
    // Построение деревьев для всех случайных массивов
    // ---------------------------
    std::cout << "\nПостроение деревьев для всех random_*.csv файлов:\n";

    for (const auto& entry : fs::directory_iterator(data_dir)) {
        if (!entry.is_regular_file()) continue;

        std::string filepath = entry.path().string();
        std::string filename = entry.path().filename().string();

        if (filename.find("random_") == std::string::npos) continue;

        std::vector<int> arr = io::read_csv_int_one_column(filepath);

        std::cout << "\nФайл: " << filename << " (размер " << arr.size() << ")\n";

        // -------- AVL --------
        auto start = std::chrono::high_resolution_clock::now();
        avl::Node* avl_root = avl::build_avl_from_array(arr);
        auto end = std::chrono::high_resolution_clock::now();
        double avl_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        std::cout << "AVL дерево построено за " << avl_time_ms << " ms\n";

        // Сохраняем одно дерево в JSON
        if (filename == "random_100.csv") {
            json j = avl_to_json(avl_root);
            fs::create_directories("results/json");
            std::ofstream f("results/json/avl_example.json");
            f << j.dump(4);
            f.close();
            std::cout << "AVL дерево сохранено в results/json/avl_example.json\n";
        }

        avl::free_tree(avl_root);

        // -------- 2-3 дерево --------
        start = std::chrono::high_resolution_clock::now();
        tree23::Node* t23_root = tree23::build_tree23_from_array(arr);
        end = std::chrono::high_resolution_clock::now();
        double t23_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        std::cout << "2-3 дерево построено за " << t23_time_ms << " ms\n";
        tree23::free_tree(t23_root);
    }

    // ---------------------------
    // Тестирование сортировок
    // ---------------------------
    std::cout << "\nЗапуск тестов сортировок...\n";
    std::vector<tests::SortTestResult> results = tests::run_all_sort_tests(data_dir);
    std::string summary_file = "results/summary/all_results.csv";
    tests::save_test_results_to_csv(summary_file, results);
    std::cout << "Тесты сортировок завершены. Результаты сохранены в " << summary_file << "\n";

    return 0;
}