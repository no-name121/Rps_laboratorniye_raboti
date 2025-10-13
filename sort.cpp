#include <iostream>
#include <limits>
#include <vector>

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
        cout << "Введите элемент массива: ";
        get_int(element);

        arr.push_back(element);
    } 
}

// заполнение рандомными числами
enum range_input {without_range = 1, with_range};

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
void file_input(){
    
}

// вывод массива
void print_array(vector<int>& array_to_print){
    cout << endl;
    for (int num : array_to_print)
        cout << num << " ";
    cout << endl << endl;
}

// главное меню
enum menu_items {keyboard = 1, random_items, file, prog_exit};

int main(){
    srand(0);
    
    vector<int> array_to_sort;
    int user_choice = 0;
   
    do {
        if (user_choice == 0){
        cout << "Гномья сортировка" << endl
             << "Выберите способ заполнения массива:" << endl
             << "1 - Заполнение с клавиатуры;" << endl
             << "2 - Заполнение случайными числами;" << endl
             << "3 - Загрузка данных из файла;" << endl
             << "4 - Выход." << endl;
        }

        cout << "Введите число: ";
        get_int(user_choice);

        switch (user_choice)
        {
        case keyboard:
            keyboard_input(array_to_sort);
            print_array(array_to_sort);
            array_to_sort.clear();
            user_choice = 0;
        break;

        case random_items:
            random_input(array_to_sort);
            print_array(array_to_sort);
            array_to_sort.clear();
            user_choice = 0;
        break;

        case file:
            file_input();
            print_array(array_to_sort);
            array_to_sort.clear();
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
