#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <string>
#include <vector>

/// Пространство имён для модулей ввода-вывода лабораторного проекта.
namespace io {

/**
 * Записывает двумерные табличные данные в CSV-файл.
 *
 * Формат входных данных:
 * - header: список названий колонок (например, {"algorithm", "size", "type", "time_ms"})
 * - rows:   каждая строка — это вектор значений, преобразуемых в строки
 *
 * Все значения автоматически экранируются, если содержат запятые.
 *
 *
 * @param filepath Путь, куда сохранить CSV файл.
 * @param header Вектор строк — заголовок таблицы.
 * @param rows Таблица строковых значений.
 * @throws std::runtime_error при ошибке записи файла.
 */
void write_csv(
    const std::string& filepath,
    const std::vector<std::string>& header,
    const std::vector<std::vector<std::string>>& rows
);

} // namespace io

#endif // CSV_WRITER_H