#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <clocale>
#include "input.h"

using namespace std;

// функция сортировки
void gnome_sort(vector<int>& arr){

    for(size_t i = 1; i < arr.size();){

        if (i != 0 && arr[i] < arr[i-1]){

            int tmp = arr[i];
            arr[i] = arr[i-1];
            arr[i-1] = tmp;
            i--;
        }
        else
            i++;
    }
}

// проверка на ввод числа
void get_int(int& var){

    while(!(cin >> var)){  
        cout << "Некорректный ввод." << endl
             << "Введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


// проверка на запрещенные названия для windows
bool is_forbidden_name(string path) {
	const string forbidden_names[] = { "CON", "PRN", "AUX", "NUL", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6",
	"COM7", "COM8", "COM9", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9" };

	if (path.find_last_of('\\') != string::npos)
		path = path.substr(path.find_last_of('\\') + 1);

	transform(path.begin(), path.end(), path.begin(), [](unsigned char c) { return static_cast<unsigned char>(toupper(c)); });

	for (const string& name : forbidden_names)
		if (path == name)
			return true;

	return false;
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

// проверка пути файла на ввод данных
bool check_inp_file_path(string& path){
    ifstream file;

    file.open(path);

    if (!file.is_open())
        return false;
    
    file.close();

    return true;
}

// проверка пути файла на вывод данных
bool check_outp_file_path(string& path){

    if (is_forbidden_name(path))
        return false;

    ofstream file;
    file.open(path, ios::app);
    if (!file.is_open())
        return false;
    file.close();

    return true;
}

// созпанение данных в файл
void file_output(vector<int>& arr){
    ofstream file;
    string path;

    do {
        cout << "Введите путь к файлу: ";
        cin >> path;

        if (!check_outp_file_path(path))
            cout << "Некорректный путь" << endl;

        if (check_inp_file_path(path)){
            cout << "Файл с таким названием уже существует." << endl;
            if (rewrite_file_menu())
                break;
            else
                path = "";
        }
    } while(!check_outp_file_path(path));

    file.open(path);
    for (int element : arr)
        file << element << " ";

    file.close();
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

// вывод массива
void print_array(vector<int>& array_to_print){
    cout << endl;
    for (int num : array_to_print)
        cout << num << " ";
    cout << endl;
}

// ввод разными методами, обработка результатов
void results(void (*input) (vector<int>& arr)){
    vector<int> array_to_sort;

    input(array_to_sort);
    cout << endl << "Исходный массив: ";
    print_array(array_to_sort);

    gnome_sort(array_to_sort);
    cout << "Отсортированный массив: ";
    print_array(array_to_sort);
    cout << endl;

    if(save_file_menu()){
        file_output(array_to_sort);
        cout << "Данные сохранены в файл." << endl << endl;
    }

    array_to_sort.clear();
}

// главное меню
enum menu_items {keyboard = 1, random_items, file, prog_exit};

int main(){
    setlocale(LC_ALL, "");

    srand(0);
    
    int user_choice = 0;
   
    do {
        if (user_choice == 0){
        cout << "---------------------" << endl
             << "| Гномья сортировка |" << endl
             << "---------------------" << endl
             << "Выберите способ заполнения массива:" << endl
             << "1 - Заполнение с клавиатуры;" << endl
             << "2 - Заполнение случайными числами;" << endl
             << "3 - Загрузка данных из файла;" << endl
             << "4 - Выход." << endl;
        }

        cout << "Введите число: ";
        get_int(user_choice);
        cout << endl;

        switch (user_choice)
        {
        case keyboard:
            results(keyboard_input);
            user_choice = 0;
            break;

        case random_items:
            results(random_input);
            user_choice = 0;
            break;

        case file:
            results(file_input);
            user_choice = 0;
            break;  

        case prog_exit:
            return 0;
        
        default:
            cout << "Некорректный пункт меню." << endl;
            break;
        }

    } while(user_choice != prog_exit);
}
