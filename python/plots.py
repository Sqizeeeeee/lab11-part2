import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# -----------------------------
# Первый кусок: график деревьев (не трогаем)
# -----------------------------
sns.set(style="whitegrid", palette="muted", font_scale=1.2)

plot_dir = "../plots"
os.makedirs(plot_dir, exist_ok=True)

# График времени построения деревьев
tree_csv = "../results/trees/tree.csv"
df_tree = pd.read_csv(tree_csv)
df_tree = df_tree.sort_values("size")

plt.figure(figsize=(10, 6))
sns.lineplot(x="size", y="avl_ms", data=df_tree, marker="o", label="AVL дерево")
sns.lineplot(x="size", y="t23_ms", data=df_tree, marker="s", label="2-3 дерево")
plt.xscale("log")
plt.yscale("log")
plt.xlabel("Размер массива")
plt.ylabel("Время построения (ms)")
plt.title("Сравнение времени построения AVL и 2-3 деревьев")
plt.legend()
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "trees_build_time.png"), dpi=300)
plt.close()
print(f"[OK] График деревьев сохранён: {plot_dir}/trees_build_time.png")

# -----------------------------
# Новый блок: графики сортировок по отдельным CSV
# -----------------------------
data_types = ["random", "sorted", "reversed"]
algorithms = ["merge", "quick", "heap"]

for dt in data_types:
    df_list = []
    for algo in algorithms:
        file_path = f"results/{dt}/{algo}.csv"
        if os.path.exists(file_path):
            df = pd.read_csv(file_path)
            df["algorithm"] = algo
            df_list.append(df)
    
    if not df_list:
        print(f"[WARN] Нет данных для {dt}")
        continue

    subset = pd.concat(df_list)
    subset = subset.sort_values("size")
    
    plt.figure(figsize=(10, 6))
    sns.lineplot(x="size", y="time_ms", hue="algorithm", style="algorithm",
                 markers=True, dashes=False, data=subset)
    
    plt.xscale("log")
    plt.yscale("log")
    plt.xlabel("Размер массива")
    plt.ylabel("Время сортировки (ms)")
    plt.title(f"Сравнение алгоритмов сортировки ({dt} массив)")
    plt.legend(title="Алгоритм")
    plt.tight_layout()
    
    filename = f"sorting_{dt}.png"
    plt.savefig(os.path.join(plot_dir, filename), dpi=300)
    plt.close()
    print(f"[OK] График сортировок сохранён: {plot_dir}/{filename}")