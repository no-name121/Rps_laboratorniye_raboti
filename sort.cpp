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
bool check_int(int& var){

    if (cin >> var){  
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

// ввод с клавиатуры
void keyboard_input(){

}

// заполнение рандомными числами
void random_input(){
    
}

// ввод из файла
void file_input(){
    
}

// главное меню
enum menu_items {keyboard = 1, random, file, prog_exit};

void main_menu(){
    cout << "Гномья сортировка" << endl
         << "Выберите способ заполнения массива:" << endl
         << "1 - Заполнение с клавиатуры;" << endl
         << "2 - Заполнение случайными числами;" << endl
         << "3 - Загрузка данных из файла;" << endl
         << "4 - Выход." << endl;


    vector<int> array_to_sort;
    int user_choice;

    do {

        cout << "Введите число: ";
        if (!check_int(user_choice)){
            cout << "Некорректный ввод." << endl;
            continue;
        } 

        switch (user_choice)
        {
        case keyboard:
            keyboard_input();
            break;

        case random:
            random_input();
            break;

        case file:
            file_input();
        break;  

        case prog_exit:
            return;
        
        default:
            cout << "Некорректный пункт меню." << endl;
            break;
        }

    } while(true);
}

int main(){

    vector<int> arr = {9, 0, 11, 4, -5, 69, -666};

    gnome_sort(arr);
    
    for(int a : arr)
        cout << a << " ";
    cout << endl;

    main_menu();

    return 0;
}
