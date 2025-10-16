#include <iostream>
#include <vector>
#include <clocale>
#include "input_output.h"
#include "check_functions.h"

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
