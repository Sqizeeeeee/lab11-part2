import numpy as np
import pandas as pd
import os

# Папка, куда сохраняются CSV
DATA_DIR = "../data"

# Создаём папку, если её нет
os.makedirs(DATA_DIR, exist_ok=True)

# Размеры массивов
sizes = [10, 100, 1000, 10_000, 100_000, 1_000_000]

def save_array(arr, filename):
    """Сохраняем массив в CSV файл одной колонкой."""
    df = pd.DataFrame(arr, columns=["value"])
    df.to_csv(os.path.join(DATA_DIR, filename), index=False)

def main():
    for n in sizes:
        print(f"Генерация массивов для n = {n} ...")

        # случайный массив
        arr_random = np.random.randint(0, 10_000_000, size=n)
        save_array(arr_random, f"random_{n}.csv")

        # отсортированный
        arr_sorted = np.sort(arr_random)
        save_array(arr_sorted, f"sorted_{n}.csv")

        # отсортированный наоборот
        arr_reverse = arr_sorted[::-1]
        save_array(arr_reverse, f"reversed_{n}.csv")

    print("Готово! Файлы сохранены в папку /data")

if __name__ == "__main__":
    main()