#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

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

// ввод из файла
void file_input(vector<int>& arr){
    ifstream file;
    string path;

    do {
        cout << "Введите путь к файлу: ";
        cin >> path;

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
