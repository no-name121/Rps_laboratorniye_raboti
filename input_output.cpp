#include "input_output.h"
#include "check_functions.h"
#include <iostream>
#include <fstream>

using namespace std;

// ввод с клавиатуры
void keyboard_input(vector<int>& arr){

    int size = get_array_size();

    int element;
    for (size_t i = 0; i < size; i++){
        cout << "Введите " << i+1 << " элемент массива: ";
        get_int(element);

        arr.push_back(element);
    } 
}

enum range_input {without_range = 1, with_range};
// заполнение рандомными числами
void random_input(vector<int>& arr){

    int size = get_array_size();

    int user_choice = 0;
    do {
        cout << "Выберите способ случайного заполнения: " << endl
             << "1 - Заполнение случайными числами без диапозона;" << endl
             << "2 - Заполнение случайными числами в выбранном диапозоне." << endl;

        cout << "Введите число: ";
        get_int(user_choice);

        if (user_choice == without_range || user_choice == with_range){

            switch (user_choice) {

            case without_range:

                for (size_t i = 0; i < size; i++)
                    arr.push_back(rand());
                return;

            case with_range:
                
                int first_range_num, second_range_num;
                do {
                    cout << "Введите первое число диапазона: ";
                    get_int(first_range_num);

                    cout << "Введите второе число диапазона: ";
                    get_int(second_range_num);

                    if (first_range_num > second_range_num)
                        cout << "Некорректный диапазон." << endl;
                } while(first_range_num > second_range_num);

                int range_size = second_range_num - first_range_num + 1;

                for (size_t i = 0; i < size; i++)
                    arr.push_back(rand() % range_size + first_range_num);
                return;
            }
        }
        else
            cout << "Некорректный пункт меню." << endl;

        } while (true);
}

// ввод из файла
void file_input(vector<int>& arr){
    ifstream file;
    string path;

    do {
        cout << "Введите путь к файлу: ";
        getline(cin, path);

        if (check_file_exits(path))
            break;
        else
            cout << "Файл не найден." << endl;

    } while(true);

    file.open(path);

    int element = 0;
    while(file >> element)
        arr.push_back(element);
    
    if (!file.eof() && file.fail()){
        cout << "Ошибка при чтении данных из файла." << endl << endl;
        arr.clear();
        file.close();
        return;
    }

    file.close();
}


enum menu_items {yes = 1, no};
// меню ответа да/нет для передаваемого сообщения
bool yes_no_menu(const string& message){
    int user_choice = 0;

    cout << message << endl
         << "1 - Да" << endl
         << "2 - Нет" << endl;

    do {
        cout << "Введите число: ";
        get_int(user_choice);
        switch (user_choice)
        {
        case yes:
            return true;

        case no:
            return false;
        
        default:
            cout << "Некорректный пункт меню." << endl;
        }
     } while(true);

     return false;
}

// сохранение данных в файл
void file_output(vector<int>& arr){
    ofstream file;
    string path;

    do {
        cout << "Введите путь к файлу: ";
        getline(cin, path);

        if (check_file_exits(path)){
            cout << "Файл с таким названием уже существует." << endl;
            if (yes_no_menu("Перезаписать данные файла?"))
                break;
        }       
        if (check_outp_file_path(path))
            break;
        else
            cout << "Некорректный путь" << endl;

    } while(true);

    file.open(path);
    for (int element : arr)
        file << element << " ";

    file.close();
}