import re
import csv

# Входной файл с логами (вывод main.cpp)
input_file = "../data/logs.txt"
# Выходной CSV
output_file = "../results/trees/tree.csv"

# Регулярные выражения для парсинга
file_re = re.compile(r"Файл: (\S+) \(размер (\d+)\)")
avl_re = re.compile(r"AVL дерево построено за ([\d.]+) ms")
t23_re = re.compile(r"2-3 дерево построено за ([\d.]+) ms")

data = []

with open(input_file, "r", encoding="utf-8") as f:
    lines = f.readlines()

current_file = None
current_size = None
avl_time = None
t23_time = None

for line in lines:
    line = line.strip()
    file_match = file_re.match(line)
    if file_match:
        current_file = file_match.group(1)
        current_size = int(file_match.group(2))
        avl_time = None
        t23_time = None
        continue

    avl_match = avl_re.match(line)
    if avl_match:
        avl_time = float(avl_match.group(1))
        continue

    t23_match = t23_re.match(line)
    if t23_match:
        t23_time = float(t23_match.group(1))
    
    # Если есть все данные — добавляем в массив
    if current_file and avl_time is not None and t23_time is not None:
        data.append({
            "file": current_file,
            "size": current_size,
            "avl_ms": avl_time,
            "t23_ms": t23_time
        })
        # Сброс для следующего блока
        current_file = None
        current_size = None
        avl_time = None
        t23_time = None

# Сохраняем в CSV
with open(output_file, "w", newline="", encoding="utf-8") as f:
    writer = csv.DictWriter(f, fieldnames=["file", "size", "avl_ms", "t23_ms"])
    writer.writeheader()
    for row in data:
        writer.writerow(row)

print(f"Данные успешно сохранены в {output_file}")