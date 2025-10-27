#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// Предварительные объявления шаблонных функций
template<typename T>
void insert_sort_Sokolov(vector<T>& aVector);

template<typename T>
void pivnenko_shell(vector<T>& aVector);

template<typename T>
void quickSort_byOsadchiy(vector<T>& arr);

template<typename T>
void mergeSort_byKirsanov(vector<T>& arr);

// Функция для чтения данных из файла
vector<string> readDataFromFileUnity(const string& filename) {
    vector<string> data;
    ifstream file(filename);

    if (!file.is_open()) {
        return data;
    }

    string token;
    while (file >> token) {
        data.push_back(token);
    }

    file.close();
    return data;
}

template<typename T>
float measureSortTimeUnity(void (*sortFunction)(vector<T>&), vector<T> data) {
    auto start = chrono::high_resolution_clock::now();
    sortFunction(data);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double, std::milli>(end - start).count();
}

int main() {

    setlocale(LC_ALL, "Russian");
    // Список файлов для обработки
    vector<string> files = { "sorted_double.txt", "sorted_int.txt", "sorted_letter.txt", "sorted_string.txt", "sorted_time.txt", "sorted_one.txt" };

    // Список алгоритмов сортировки
    vector<pair<string, void (*)(vector<string>&)>> algorithms;
    algorithms.push_back(make_pair("InsertionSort (Sokolov)", insert_sort_Sokolov<string>));
    algorithms.push_back(make_pair("QuickSort (Osadchiy)", quickSort_byOsadchiy<string>));
    algorithms.push_back(make_pair("ShellSort (Pivnenko)", pivnenko_shell<string>));
    algorithms.push_back(make_pair("MergeSort (Kirsanov)", mergeSort_byKirsanov<string>));

    // Обрабатываем каждый файл
    for (const auto& filename : files) {
        vector<string> data = readDataFromFileUnity(filename);

        if (data.empty()) {
            cout << "File " << filename << " not found or empty, skip" << endl;
            continue;
        }

        cout << "File: " << filename << " (" << data.size() << " elements)" << endl;

        // Сортируем каждым алгоритмом и замеряем время
        for (const auto& algorithm : algorithms) {
            string algoName = algorithm.first;
            auto algoFunc = algorithm.second;
            vector<string> dataCopy = data; // Копируем данные для каждого алгоритма
            float time = measureSortTimeUnity(algoFunc, dataCopy);
            cout << "  " << algoName << ": " << time << "ms" << endl;
        }
        cout << endl;
    }

    return 0;
}

template<typename T>
void insert_sort_Sokolov(vector<T>& aVector) {
    if (aVector.empty()) return;

    unsigned n = aVector.size();

    unsigned min_index = 0;
    for (unsigned i = 1; i < n; ++i) {
        if (aVector[i] < aVector[min_index]) {
            min_index = i;
        }
    }
    if (min_index != 0) {
        swap(aVector[0], aVector[min_index]);
    }

    for (unsigned i = 2; i < n; ++i) {
        T value = aVector[i];
        unsigned j = i;

        while (j > 0 && aVector[j - 1] > value) {
            aVector[j] = aVector[j - 1];
            --j;
        }
        aVector[j] = value;
    }
}

template<typename T>
void pivnenko_shell(vector<T>& aVector) {
    if (aVector.empty()) return;

    int n = aVector.size();

    // Используем последовательность Кнута для выбора промежутков
    int gap = 1;
    while (gap < n / 3) {
        gap = 3 * gap + 1;
    }

    // Последовательно уменьшаем промежуток
    while (gap >= 1) {
        // Сортируем элементы на расстоянии gap
        for (int i = gap; i < n; i++) {
            T temp = aVector[i];
            int j = i;

            // Сдвигаем элементы, пока не найдем правильную позицию для temp
            while (j >= gap && aVector[j - gap] > temp) {
                aVector[j] = aVector[j - gap];
                j -= gap;
            }
            aVector[j] = temp;
        }
        gap = gap / 3;
    }
}

template<typename T>
void quickSort_byOsadchiy(vector<T>& arr) {
    if (arr.size() <= 1) return;

    T pivot = arr[arr.size() / 2];
    vector<T> left, right, equal;

    for (const auto& x : arr) {
        if (x < pivot) left.push_back(x);
        else if (x > pivot) right.push_back(x);
        else equal.push_back(x);
    }

    quickSort_byOsadchiy(left);
    quickSort_byOsadchiy(right);

    arr = left;
    arr.insert(arr.end(), equal.begin(), equal.end());
    arr.insert(arr.end(), right.begin(), right.end());
}

template<typename T>
void merge_Kirsanov(vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template<typename T>
void mergeSort_byKirsanov(vector<T>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort_byKirsanov(arr, left, mid);
    mergeSort_byKirsanov(arr, mid + 1, right);
    merge_Kirsanov(arr, left, mid, right);
}

template<typename T>
void mergeSort_byKirsanov(vector<T>& arr) {
    if (arr.empty()) return;
    mergeSort_byKirsanov(arr, 0, arr.size() - 1);
}