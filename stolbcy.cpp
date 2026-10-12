#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Student {
    int id;              
    string fullName;     
    string course;       
    string groupName;    
    float averageGrade;  
    int missedHours;     
    int passedExams;     
};

void readDataFromFile(Student*& list, int& size);
void displayData(const Student* list, int size);
void editDataRow(Student* list, int size);
void addStudent(Student*& list, int& size);       
void deleteStudent(Student*& list, int& size);    
void calculateStats(const Student* list, int size);
void saveDataToFile(const Student* list, int size);

int main() {
    setlocale(LC_ALL, "Russian");

    Student* list = nullptr;
    int size = 0;
    int choice;

    do {
        cout << "\n===== СИСТЕМА УПРАВЛЕНИЯ БД \"УНИВЕРСИТЕТ\" =====\n";
        cout << "1. Чтение данных из файла в динамический массив\n";
        cout << "2. Просмотр данных, хранящихся в массиве\n";
        cout << "3. Корректировка данных заданной строки\n";
        cout << "4. Добавление новой записи студента\n";
        cout << "5. Удаление записи студента по номеру зачётки\n";
        cout << "6. Функция \"Вычисления\"\n";
        cout << "7. Функция \"Сохранение данных в новом файле\"\n";
        cout << "8. Выход из программы\n";
        cout << "Выберите действие (1-8): ";
        cin >> choice;

        switch (choice) {
            case 1: readDataFromFile(list, size); break;
            case 2: displayData(list, size); break;
            case 3: editDataRow(list, size); break;
            case 4: addStudent(list, size); break;
            case 5: deleteStudent(list, size); break;
            case 6: calculateStats(list, size); break;
            case 7: saveDataToFile(list, size); break;
            case 8: break; 
            default: cout << "Неверный выбор! Повторите ввод.\n";
        }
    } while (choice != 8);

    delete[] list; 
    return 0;
}

void readDataFromFile(Student*& list, int& size) {
    if (list != nullptr) {
        delete[] list;
        list = nullptr;
        size = 0;
    }

    ifstream fin("input.txt");
    if (!fin) {
        cout << "Ошибка: Файл input.txt не найден!\n"; 
        return;
    }

    int count = 0;
    int temp_id;
    string temp_name, temp_course, temp_group;
    float temp_grade;
    int temp_hours;
    int temp_exams;

    while (fin >> temp_id >> temp_name >> temp_course >> temp_group >> temp_grade >> temp_hours >> temp_exams) {
        count++;
    }

    if (count == 0) {
        fin.close();
        return;
    }

    size = count;
    list = new Student[size];

    fin.clear();
    fin.seekg(0, ios::beg);

    for (int i = 0; i < size; i++) {
        fin >> list[i].id >> list[i].fullName >> list[i].course >> list[i].groupName >> list[i].averageGrade >> list[i].missedHours >> list[i].passedExams;
    }

    fin.close();
}

void displayData(const Student* list, int size) {
    if (list == nullptr || size == 0) {
        cout << "База данных пуста! Сначала выполните пункт 1.\n";
        return;
    }

    cout << "\n" << setfill('-') << setw(115) << "-" << setfill(' ') << endl;
    cout << "| " << setw(8) << "Зачетка" << " | " << setw(25) << "ФИО Студента" << " | " << setw(10) << "Курс" << " | " << setw(10) << "Группа" << " | " << setw(8) << "Ср.балл" << " | " << setw(10) << "Пропуски(ч)" << " | " << setw(10) << "Экзамены" << " |\n";
    cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl;

    for (int i = 0; i < size; i++) {
        cout << "| " << setw(8) << list[i].id 
             << " | " << setw(25) << list[i].fullName 
             << " | " << setw(10) << list[i].course 
             << " | " << setw(10) << list[i].groupName 
             << " | " << setw(8) << fixed << setprecision(2) << list[i].averageGrade 
             << " | " << setw(10) << list[i].missedHours 
             << " | " << setw(10) << list[i].passedExams << " |\n";
    }
    cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl;
}

void editDataRow(Student* list, int size) {
    if (list == nullptr || size == 0) {
        return;
    }

    int target_id;
    cout << "Введите номер зачетки для изменения данных: ";
    cin >> target_id;

    int foundIndex = -1;
    for (int i = 0; i < size; i++) {
        if (list[i].id == target_id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "Студент не найден в базе.\n";
        return;
    }

    cout << "Новое ФИО (без пробелов): ";
    cin >> list[foundIndex].fullName;
    cout << "Новый курс: ";
    cin >> list[foundIndex].course;
    cout << "Новая группа: ";
    cin >> list[foundIndex].groupName;
    cout << "Новый средний балл :";
    cin >> list[foundIndex].averageGrade;
    cout << "Новое количество пропущенных часов : ";
    cin >> list[foundIndex].missedHours;
    cout << "Сколько экзаменов сдано : ";
    cin >> list[foundIndex].passedExams;
}

void addStudent(Student*& list, int& size) {

    Student* tempList = new Student[size + 1];


    for (int i = 0; i < size; i++) {
        tempList[i] = list[i];
    }

    cout << "Введите ID (номер зачетки): ";
    cin >> tempList[size].id;
    cout << "Введите ФИО (без пробелов): ";
    cin >> tempList[size].fullName;
    cout << "Введите курс: ";
    cin >> tempList[size].course;
    cout << "Введите группу: ";
    cin >> tempList[size].groupName;
    cout << "Введите средний балл (float): ";
    cin >> tempList[size].averageGrade;
    cout << "Введите пропущенные часы (int): ";
    cin >> tempList[size].missedHours;
    cout << "Введите сдано экзаменов (int): ";
    cin >> tempList[size].passedExams;


    delete[] list;
    list = tempList;
    size++; 
}


void deleteStudent(Student*& list, int& size) {
    if (list == nullptr || size == 0) {
        return;
    }

    int target_id;
    cout << "Введите ID (номер зачетки) для удаления: ";
    cin >> target_id;

    int deleteIndex = -1;
    for (int i = 0; i < size; i++) {
        if (list[i].id == target_id) {
            deleteIndex = i;
            break;
        }
    }

    if (deleteIndex == -1) {
        cout << "Студент с такой зачёткой не найден.\n";
        return;
    }

  
    if (size == 1) {
        delete[] list;
        list = nullptr;
        size = 0;
        return;
    }


    Student* tempList = new Student[size - 1];
    int tempIndex = 0;


    for (int i = 0; i < size; i++) {
        if (i != deleteIndex) {
            tempList[tempIndex] = list[i];
            tempIndex++;
        }
    }

    delete[] list;
    list = tempList;
    size--;
}

void calculateStats(const Student* list, int size) {
    if (list == nullptr || size == 0) {
        return;
    }

    double totalGrade = 0;
    int maxAbsences = list[0].missedHours; 
    int maxAbsenceIndex = 0;

    for (int i = 0; i < size; i++) {
        totalGrade += list[i].averageGrade;
        if (list[i].missedHours > maxAbsences) {
            maxAbsences = list[i].missedHours;
            maxAbsenceIndex = i;
        }
    }

    double totalAverageGrade = totalGrade / size;

    cout << "\n======= АНАЛИТИЧЕСКИЕ ВЫЧИСЛЕНИЯ =====\n";
    cout << "Средний балл успеваемости студентов: " << fixed << setprecision(2) << totalAverageGrade << "\n";
    cout << "Студент с максимальным количество пропусков: " << list[maxAbsenceIndex].fullName 
         << " (" << list[maxAbsenceIndex].missedHours << " ч.), Группа: " << list[maxAbsenceIndex].groupName << "\n";
    cout << "======================================\n";
}

void saveDataToFile(const Student* list, int size) {
    if (list == nullptr || size == 0) {
        return;
    }

    string outFileName;
    cout << "Введите имя нового файла для сохранения: ";
    cin >> outFileName;

    ofstream fout(outFileName);
    if (!fout) {
        cout << "Ошибка при создании файла!\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        fout << list[i].id << " " << list[i].fullName << " " << list[i].course << " " << list[i].groupName << " " << list[i].averageGrade << " " << list[i].missedHours << " " << list[i].passedExams << "\n";
    }

    fout.close();
}
