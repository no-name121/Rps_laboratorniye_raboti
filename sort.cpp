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
        cout << "Введите размер массива: " << endl;
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
void random_input(){
    
}

// ввод из файла
void file_input(){
    
}

// вывод массива
void print_array(vector<int>& array_to_print){
    for (int num : array_to_print)
        cout << num << " ";
    cout << endl;
}

// главное меню
enum menu_items {keyboard = 1, random_items, file, prog_exit};

int main(){

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
            break;

        case random_items:
            random_input();
            break;

        case file:
            file_input();
        break;  

        case prog_exit:
            return 0;
        
        default:
            cout << "Некорректный пункт меню." << endl;
            break;
        }

    } while(user_choice != prog_exit);

}
