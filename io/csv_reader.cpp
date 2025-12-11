#include "csv_reader.h"
#include <fstream>
#include <sstream>

namespace io {

std::vector<int> read_csv_int_one_column(const std::string& filepath, bool has_header) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw CsvReadError("Не удалось открыть файл: " + filepath);
    }

    std::vector<int> values;
    std::string line;
    int line_number = 0;

    // Пропускаем заголовок, если требуется
    if (has_header) {
        if (!std::getline(file, line)) {
            throw CsvReadError("Файл пустой или повреждён: " + filepath);
        }
        line_number++;
    }

    // Чтение строк
    while (std::getline(file, line)) {
        line_number++;

        // Пропуск пустых строк
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        int value;

        // Пробуем прочитать int
        if (!(ss >> value)) {
            throw CsvReadError("Ошибка преобразования строки в число в файле " +
                               filepath + " на строке " + std::to_string(line_number));
        }

        values.push_back(value);
    }

    return values;
}

} // namespace io