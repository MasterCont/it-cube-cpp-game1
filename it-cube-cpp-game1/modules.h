#pragma once
#include <iostream>
#include <unordered_map>

using namespace std;

// Создаём некоторую информацию о нашем приложении
class Game {
public:

    struct Debug {

        struct Pages {
            int page;
            int max;
        };

        bool active = false;
        Pages pages;
    };

    const string version = "0.1.2";
    const string name = "@it_cube_cpp_game1";
    const string author = "MasterCont";
    const string git = "https://github.com/MasterCont/it-cube-cpp-game1.git";
    int map_number = 0; // ���������, ��� �� ��������� ����������� ������ (������� �� ���������) �����
    Debug debug; // если активна, то отображаем раскладку
    bool over = false; // Z`Закончена ли игра
    bool ui_update_permission = true; // Можно ли обновлять интерфейс игры (избавляет от постоянного обновления интерфейса, если действие цикличное и бесполезно)
};

bool pick_loot_item = false; // Поднят ли предмет игроком

// Параметры игры для игрока
bool fight = false; // Идёт бой для игрока или нет
bool more_by_coordinate = false; // Получение рандомного bool числа для передвижения моба по действию игрока
Game game;

string UI_Interface[][4] = { // Создаём переменную, в которой храним информацию игрока для вывода в терминал
     {" |#", " # ", " # ", " #  #  # #"}, {}, {}, {}, {}, {}, {" |#", " # ", " # ", " #  #  # #"}
};

// Функция для установки заголовка терминала Windows
void setWindowsConsoleTitle(string title);

// Функция для вывода окна запуска программы
void UI_Hello(string title, string version, string author, string git);

// Функция для вывода окна завершения программы
void UI_Bye();

// Функция для получения рандомного числа в диапазоне от min до max
int random(int min, int max);

struct userData {
    string name;
};

// Функция для записи данных в программу
userData getUserData();

void clearScreen();
