#include "input_output.h"
#include "check_functions.h"
#include <iostream>
#include <fstream>

using namespace std;

// ввод с клавиатуры
void keyboard_input(vector<int>& arr){

    int size = 0;
    do {
        cout << "Введите размер массива: ";
        get_int(size);

        if (size < 1)
            cout << "Некорректный размер массива.";
    } while(size < 1);

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
    int size = 0;
    do {
        cout << "Введите размер массива: ";
        get_int(size);

        if (size < 1)
            cout << "Некорректный размер массива.";
    } while(size < 1);

    int user_choice = 0;
    do {
        cout << "Выберите способ случайного заполнения: " << endl
             << "1 - Заполнение случайными числами без диапозона;" << endl
             << "2 - Заполнение случайными числами в выбранном диапозоне." << endl;

    cout << "Введите число: ";
    get_int(user_choice);

    if (user_choice != 1 && user_choice != 2)
        cout << "Некорректный пункт меню." << endl;

    } while (user_choice != 1 && user_choice != 2);

    switch (user_choice)
    {
    case without_range:
        for (size_t i = 0; i < size; i++)
            arr.push_back(rand());
    break;

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

    break;
    }
}

// ввод из файла
void file_input(vector<int>& arr){
    ifstream file;
    string path;

    do {
        cout << "Введите путь к файлу: ";
        getline(cin, path);

        if (!check_inp_file_path(path))
            cout << "Файл не найден." << endl;
    } while(!check_inp_file_path(path));

    file.open(path);

    int element = 0;
    while(!file.eof())
        if(file >> element)
            arr.push_back(element);
    
    file.close();

}

enum rewrite_menu_items {rewrite = 1, do_not_rewrite};
// меню на перезапись файла
bool rewrite_file_menu(){
    int user_choice = 0;

    cout << "Перезаписать данные файла?" << endl
         << "1 - Да" << endl
         << "2 - Нет" << endl;

    do {
        cout << "Введите число: ";
        get_int(user_choice);
        switch (user_choice)
        {
        case rewrite:
            return true;

        case do_not_rewrite:
            return false;
        
        default:
            cout << "Некорректный пункт меню." << endl;
            break;
        }
     } while(user_choice != 1 && user_choice != 2);

     return false;
}

// меню сохранения данных в файл
bool save_file_menu(){
    int user_choice = 0;

    cout << "Сохранить результат сортировки в файл?" << endl
         << "1 - Да" << endl
         << "2 - Нет" << endl;

    do {
        cout << "Введите число: ";
        get_int(user_choice);
        switch (user_choice)
        {
        case rewrite:
            return true;

        case do_not_rewrite:
            return false;
        
        default:
            cout << "Некорректный пункт меню." << endl;
            break;
        }
     } while(user_choice != 1 && user_choice != 2);

     return false;
}

// созпанение данных в файл
void file_output(vector<int>& arr){
    ofstream file;
    string path;

    do {
        cout << "Введите путь к файлу: ";
        getline(cin, path);

        if (check_inp_file_path(path)){
            cout << "Файл с таким названием уже существует." << endl;
            if (rewrite_file_menu())
                break;
        else { 
            if (!check_outp_file_path(path))
                cout << "Некорректный путь" << endl;
            path = "";
            }    
        }

    } while(!check_outp_file_path(path));

    file.open(path);
    for (int element : arr)
        file << element << " ";

    file.close();
}