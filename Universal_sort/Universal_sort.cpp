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
        cout << endl;
    }

    return 0;
}


//
// Ниже пишете каждый свой алгортим и выше вставляете его вызов (на счет передачи данных в функцию потом решим(копию или сами данные)))
//Замер времени реализуете в своём алгоритме + вывод каких-то данных (оговорить формат)
//




