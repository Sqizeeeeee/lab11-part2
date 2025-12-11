#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>
#include <stdexcept>

/// Пространство имён для модулей ввода-вывода лабораторного проекта.
namespace io {

/// Исключение, выбрасываемое при ошибках чтения CSV.
class CsvReadError : public std::runtime_error {
public:
    /**
     * Конструктор исключения.
     * @param msg Описание ошибки.
     */
    explicit CsvReadError(const std::string& msg) : std::runtime_error(msg) {}
};

/**
 * Читает CSV-файл, содержащий один столбец целых чисел, и возвращает вектор значений.
 *
 * Поддерживаемый формат:
 * - Файл может содержать заголовок (например, "value") или не содержать заголовка.
 * - Значения должны быть целыми числами, разделёнными переводами строк.
 * - Пустые строки игнорируются.
 *
 *
 * @param filepath Путь к CSV-файлу.
 * @param has_header Указать true, если файл содержит заголовок в первой строке (по умолчанию true).
 * @return std::vector<int> с прочитанными значениями в том же порядке, в каком они идут в файле.
 * @throws io::CsvReadError при проблемах открытия файла, ошибке формата или при невозможности преобразовать значение в int.
 */
std::vector<int> read_csv_int_one_column(const std::string& filepath, bool has_header = true);

} // namespace io

#endif // CSV_READER_H