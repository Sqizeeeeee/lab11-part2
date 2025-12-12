import json
import networkx as nx
import matplotlib.pyplot as plt
from pathlib import Path


def load_tree_from_json(json_path):
    """Загружает дерево из JSON файла"""
    with open(json_path, 'r') as f:
        data = json.load(f)
    return data


def build_graph(node_data, G=None, parent=None, pos=None, x=0, y=0, layer=1):
    """Рекурсивно строит граф из дерева с позициями"""
    if G is None:
        G = nx.DiGraph()
        pos = {}
    
    if node_data is None:
        return G, pos
    
    key = node_data['key']
    G.add_node(key)
    pos[key] = (x, y)
    
    if parent is not None:
        G.add_edge(parent, key)
    
    # Вычисляем ширину для текущего уровня
    width = 40 / (2 ** layer)
    
    # Обрабатываем левое поддерево
    if node_data.get('left'):
        G, pos = build_graph(node_data['left'], G, key, pos, x - width, y - 1, layer + 1)
    
    # Обрабатываем правое поддерево
    if node_data.get('right'):
        G, pos = build_graph(node_data['right'], G, key, pos, x + width, y - 1, layer + 1)
    
    return G, pos


def visualize_tree(json_path, output_path):
    """Основная функция для визуализации дерева"""
    # Загружаем дерево
    tree_data = load_tree_from_json(json_path)
    
    # Строим граф с позициями
    G, pos = build_graph(tree_data)
    
    # Создаем большую фигуру
    plt.figure(figsize=(40, 24))
    
    # Рисуем граф
    nx.draw(G, pos, 
            with_labels=True,
            node_color='lightblue',
            node_size=3000,
            font_size=10,
            font_weight='bold',
            font_color='black',
            edge_color='gray',
            linewidths=2,
            edgecolors='darkblue',
            arrows=True,
            arrowsize=20,
            arrowstyle='->')
    
    plt.axis('off')
    plt.tight_layout()
    
    # Сохраняем
    output_path.parent.mkdir(parents=True, exist_ok=True)
    plt.savefig(output_path, dpi=300, bbox_inches='tight', 
                facecolor='white', edgecolor='none')
    plt.close()
    print(f"Дерево сохранено в {output_path}")


if __name__ == "__main__":
    # Пути к файлам
    json_path = Path(__file__).parent.parent / "results" / "json" / "avl_example.json"
    output_path = Path(__file__).parent.parent / "results" / "trees" / "avl_example.png"
    
    # Визуализируем дерево
    visualize_tree(json_path, output_path)
