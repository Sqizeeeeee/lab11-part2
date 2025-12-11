#include "csv_writer.h"
#include <fstream>
#include <stdexcept>

namespace io {

/**
 * Экранирует значение CSV по правилам:
 * - если строка содержит запятую, кавычки или пробелы — она берётся в кавычки
 * - внутренние кавычки удваиваются (" → "")
 *
 * @param value Строка для экранирования.
 * @return Экранированная строка.
 */
static std::string escape_csv_value(const std::string& value) {
    bool needs_quotes = false;

    for (char c : value) {
        if (c == ',' || c == '"' || c == ' ') {
            needs_quotes = true;
            break;
        }
    }

    if (!needs_quotes) {
        return value;
    }

    std::string escaped;
    escaped.reserve(value.size() + 2);

    escaped.push_back('"');
    for (char c : value) {
        if (c == '"') {
            escaped.push_back('"');  // удваиваем кавычку
        }
        escaped.push_back(c);
    }
    escaped.push_back('"');

    return escaped;
}

void write_csv(
    const std::string& filepath,
    const std::vector<std::string>& header,
    const std::vector<std::vector<std::string>>& rows
) {
    std::ofstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + filepath);
    }

    // Запись заголовка
    for (std::size_t i = 0; i < header.size(); i++) {
        file << escape_csv_value(header[i]);
        if (i + 1 < header.size()) {
            file << ",";
        }
    }
    file << "\n";

    // Запись строк данных
    for (const auto& row : rows) {
        for (std::size_t i = 0; i < row.size(); i++) {
            file << escape_csv_value(row[i]);
            if (i + 1 < row.size()) {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
}

} // namespace io