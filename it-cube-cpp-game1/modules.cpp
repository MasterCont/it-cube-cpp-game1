#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <unordered_map>
#include <string>
using namespace std;

// —оздаЄм некоторые "ответы" программы
class Responses {
public:
    const string undefined = "Undefined";
};

Responses res;


// ‘ункци¤ дл¤ установки заголовка терминала Windows
void setWindowsConsoleTitle(string title) {
    wstring wstr(title.begin(), title.end());
    const wchar_t* wstrPtr = wstr.c_str();
    SetConsoleTitle(wstrPtr);
}

// ‘ункци¤ дл¤ вывода окна запуска программы
void UI_Hello(string title = res.undefined, string version = res.undefined, string author = res.undefined, string git = res.undefined) {
    cout << "# # # # # # # # # # #" << endl;
    cout << "# Title: " << title << endl;
    cout << "# Version: " << version << endl;
    cout << "# Author: " << author << endl;
    cout << "# Git: " << git << endl;
    cout << "# # # # # # # # # # #" << endl;
    cout << endl;
}

// ‘ункци¤ дл¤ вывода окна завершени¤ программы
void UI_Bye() {
    system("cls");
    cout << "# # # # # # # # # # #" << endl;
    cout << "#     Game over!    #" << endl;
    cout << "# # # # # # # # # # #" << endl;
    cout << endl;
    system("pause");
}

// ‘ункци¤ дл¤ получени¤ рандомного числа в диапазоне от min до max
int random(int min, int max) {
    return rand() % max + min;
}

struct userData {
    string name;
};

// Функция для записи данных в программу
userData getUserData() {

    // Добавляем персонажу имя/название
    int count = 16;
    string name;

    cout << "# Введите имя вашего персонажа: ";
    cin >> name;

    if (name.size() <= count) return { name };
    else {
        cout << endl;
        cout << "Допустимое имя персонажа стостоит из " + to_string(count) + " символов!" << endl;
        getUserData();
    }
}