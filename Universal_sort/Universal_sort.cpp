// Universal_sort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

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


int main() {
    // Список файлов для обработки
    vector<string> files = { "sorted_double.txt", "sorted_int.txt", "sorted_letter.txt", "sorted_string.txt", "sorted_time.txt" };

    // Обрабатываем каждый файл
    for (const auto& filename : files) {
        vector<string> data = readDataFromFileUnity(filename);

        if (data.empty()) {
            cout << "Файл " << filename << " не найден или пуст, пропускаем" << endl;
            continue;
        }

        cout << "Файл: " << filename << " (" << data.size() << " элементов)" << endl;

        // Сортируем каждым алгоритмом и замеряем время
        // 
        //
        //
        //
        //
        //
        //
        double sortTime = measureSortTime(data);

        cout << "Время сортировки: " << sortTime << " секунд" << endl;

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
double measureSortTime(vector<T> data) {
    auto start = chrono::high_resolution_clock::now();

    insert_sort_Sokolov(data);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    return duration.count() / 1000000.0;
}

template<typename T>
double measureShellSortTime(vector<T> data) {
    auto start = chrono::high_resolution_clock::now();

    pivnenko_shell(data);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    return duration.count() / 1000000.0;
}

//
// Ниже пишете каждый свой алгортим и выше вставляете его вызов (на счет передачи данных в функцию потом решим(копию или сами данные)))
//Замер времени реализуете в своём алгоритме + вывод каких-то данных (оговорить формат)
//



