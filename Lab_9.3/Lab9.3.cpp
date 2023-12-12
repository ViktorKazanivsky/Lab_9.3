#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // Функції, специфічні для Windows для консольного вводу/виводу
using namespace std;

// Структура, що представляє маршрут
struct Route
{
    string sname;  // Початковий пункт
    string ename;  // Кінцевий пункт
    int rnum{};    // Номер маршруту
};

// Прототипи функцій
void Create(Route* p, const int N);
void Print(Route* p, const int N);
void Sort(Route* p, const int N);
void PrintAll(Route* p, const int N);
void SaveToFile(Route* p, const int N, const char* filename);
void LoadFromFile(Route*& p, int& N, const char* filename);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;
    cout << "Введіть кількість маршрутів N: "; cin >> N;
    Route* p = new Route[N];
    double proc = 0, avg = 0, Kurs = 0, average = 0;
    string prizv;
    int found = 0;
    char filename[100]{};
    int menuItem;

    // Головний цикл меню
    do {
        cout << endl << endl;
        cout << "Оберіть дію:" << endl << endl;
        cout << " [1] - Введення даних з клавіатури" << endl;
        cout << " [2] - Вивід даних за номером маршруту" << endl;
        cout << " [3] - Сортування масиву" << endl;
        cout << " [4] - Вивід усіх даних" << endl;
        cout << " [5] - Збереження даних у файл" << endl;
        cout << " [6] - Завантаження даних з файлу" << endl;
        cout << " [0] - Вихід із програми" << endl << endl;
        cout << "Введіть номер дії: "; cin >> menuItem;
        cout << endl << endl << endl;

        // Обробка вибору користувача
        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;

        case 2:
            Print(p, N);
            break;

        case 3:
            Sort(p, N);
            PrintAll(p, N);
            break;

        case 4:
            Sort(p, N); // Викликати функцію сортування перед виведенням масиву
            PrintAll(p, N);
            break;

        case 5:
            cout << "Введіть ім'я файлу для збереження даних: "; cin >> filename;
            SaveToFile(p, N, filename);
            cout << "Дані збережено у файл." << endl;
            break;

        case 6:
            cout << "Введіть ім'я файлу для завантаження даних: "; cin >> filename;
            LoadFromFile(p, N, filename);
            cout << "Дані завантажено з файлу." << endl;
            break;

        case 0:
            break;

        default:
            cout << "Невірна дія! Будь ласка, введіть коректний номер дії." <<
                "Для виходу з програми введіть 0." << endl;
        }
    } while (menuItem != 0);

    delete[] p; // Не забувайте звільнювати виділену пам'ять
    return 0;
}

// Функція для введення даних з клавіатури
void Create(Route* p, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cin.get();
        cin.sync();
        cout << "Введіть початковий пункт: "; getline(cin, p[i].sname);
        cout << "Введіть кінцевий пункт: "; cin >> p[i].ename;
        cout << "Введіть номер маршруту: "; cin >> p[i].rnum;
        cout << endl;
    }
}

// Функція для виведення даних за номером маршруту
void Print(Route* p, const int N)
{
    int routenumber, count = 0;
    cout << "Введіть номер маршруту для виведення: "; cin >> routenumber;

    // Пошук та виведення даних за номером маршруту
    for (int i = 0; i < N; i++) {
        if (routenumber == p[i].rnum)
            count++;
    }

    if (count > 0) {
        cout << "============================================================"
            << endl;
        cout << "____________________________________________________________"
            << endl;
        cout << "|  Початковий Пункт  |  Кінцевий Пункт  |  Номер Маршруту  |"
            << endl;
        cout << "============================================================"
            << endl;
        for (int i = 0; i < N; i++)
        {
            if (routenumber == p[i].rnum) {
                cout << "| " << setw(17) << left << p[i].sname
                    << "| " << setw(15) << left << p[i].ename
                    << "| " << setw(14) << left << p[i].rnum << "|" << endl;
            }
        }
        cout << "============================================================"
            << endl;
        cout << endl;
    }
    else
        cout << "\nМаршрут із вказаним номером не знайдено!\n"
        "Перевірте правильність введеного номера серед існуючих у масиві." << endl;
}

// Функція для сортування масиву за номерами маршру
void Sort(Route* p, const int N)
{
    Route tmp;
    // Сортування методом "бульбашки" за номерами маршруту
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            if (p[i1].rnum > p[i1 + 1].rnum)
            {
                // Обмін елементів місцями для сортування
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
}

// Функція для виведення всіх даних
void PrintAll(Route* p, const int N)
{
    cout << "============================================================"
        << endl;
    cout << "____________________________________________________________"
        << endl;
    cout << "|  Початковий Пункт  |  Кінцевий Пункт  |  Номер Маршруту  |"
        << endl;
    cout << "============================================================"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(17) << left << p[i].sname
            << "| " << setw(15) << left << p[i].ename
            << "| " << setw(14) << left << p[i].rnum << "|" << endl;
    }
    cout << "============================================================"
        << endl;
    cout << endl;
}

// Функція для збереження даних у файл
void SaveToFile(Route* p, const int N, const char* filename)
{
    ofstream fout(filename, ios::binary); // Відкриття файлу для бінарного запису
    fout.write((char*)&N, sizeof(N)); // Запис розміру масиву
    for (int i = 0; i < N; i++)
        fout.write((char*)&p[i], sizeof(Route)); // Запис елементів масиву
    fout.close(); // Закриття файлу
}

// Функція для завантаження даних з файлу
void LoadFromFile(Route*& p, int& N, const char* filename)
{
    delete[] p; // Звільнення пам'яті від попереднього масиву
    ifstream fin(filename, ios::binary); // Відкриття файлу для бінарного читання
    fin.read((char*)&N, sizeof(N)); // Читання розміру масиву
    p = new Route[N]; // Виділення пам'яті для нового масиву
    for (int i = 0; i < N; i++)
        fin.read((char*)&p[i], sizeof(Route)); // Читання елементів масиву
    fin.close(); // Закриття файлу
}