#include "mergesort.h"
#include "quicksort.h"
#include "heapsort.h"

#include <vector>
#include <algorithm>

namespace sorting {

/* ============================================================
 *                      MERGE SORT
 * ============================================================ */

/**
 * Вспомогательная функция: слияние двух отсортированных подмассивов.
 *
 * @param arr Исходный массив.
 * @param left Левая граница.
 * @param mid Середина.
 * @param right Правая граница.
 */
static void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    for (int i = 0; i < n2; i++) {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

/**
 * Рекурсивная часть Merge Sort.
 */
static void merge_sort_recursive(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    merge_sort_recursive(arr, left, mid);
    merge_sort_recursive(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void merge_sort(std::vector<int>& arr) {
    if (!arr.empty()) {
        merge_sort_recursive(arr, 0, static_cast<int>(arr.size()) - 1);
    }
}


/* ============================================================
 *                      QUICK SORT
 * ============================================================ */

/**
 * Выбор pivot методом median-of-three.
 */
static int choose_pivot(const std::vector<int>& arr, int left, int right) {
    int mid = left + (right - left) / 2;

    int a = arr[left];
    int b = arr[mid];
    int c = arr[right];

    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        return b;
    } else if ((b <= a && a <= c) || (c <= a && a <= b)) {
        return a;
    } else {
        return c;
    }
}

/**
 * Разбиение массива.
 */
static int partition(std::vector<int>& arr, int left, int right) {
    int pivot = choose_pivot(arr, left, right);

    while (left <= right) {
        while (arr[left] < pivot) {
            left++;
        }
        while (arr[right] > pivot) {
            right--;
        }
        if (left <= right) {
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    return left;
}

/**
 * Рекурсивная часть QuickSort.
 */
static void quick_sort_recursive(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int index = partition(arr, left, right);

    quick_sort_recursive(arr, left, index - 1);
    quick_sort_recursive(arr, index, right);
}

void quick_sort(std::vector<int>& arr) {
    if (!arr.empty()) {
        quick_sort_recursive(arr, 0, static_cast<int>(arr.size()) - 1);
    }
}


/* ============================================================
 *                      HEAP SORT
 * ============================================================ */

/**
 * Восстановление max-heap для поддерева.
 *
 * @param arr Массив.
 * @param n Размер кучи.
 * @param i Индекс узла.
 */
static void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());

    // Построение кучи
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Основной цикл сортировки
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);  // перемещение максимального в конец
        heapify(arr, i, 0);
    }
}

} // namespace sorting