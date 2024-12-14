#pragma once
#include <iostream>
#include <unordered_map>

using namespace std;

// Создаём некоторую информацию о нашем приложении
class Game {

    struct Debug {

        struct Pages {
            int page;
            int max;
        };

        bool active = false;
        Pages pages;
    };

    struct Window {
        int width = false; // �� ��������� ������ ������ ����� ����� 0
        int height = false; // �� ��������� ������ ������ ����� ����� 0
    };

    struct Over {
        bool status = false;
        string reason = "";
    };

public:
    const string version = "0.1.3";
    const string name = "@it_cube_cpp_game1";
    const string author = "MasterCont";
    const string git = "https://github.com/MasterCont/it-cube-cpp-game1.git";
    int map_number = 0; // ���������, ��� �� ��������� ����������� ������ (������� �� ���������) �����
    Debug debug; // если активна, то отображаем раскладку
    Over over; // Z`Закончена ли игра
    bool ui_update_permission = true; // Можно ли обновлять интерфейс игры (избавляет от постоянного обновления интерфейса, если действие цикличное и бесполезно)
    Window window;
    bool data_collection;
    bool hello_ui = true;
    bool finished = false;
};

class Messages {
    public:
        const string enemyiesDerstoyed = "All enemyies are destroyed.";
        const string playerDestroyed = "The player has run out of health.";
        const string gameBreak = "The program is completed by exiting.";
};

bool pick_loot_item = false; // Поднят ли предмет игроком

// Параметры игры для игрока
bool fight = false; // Идёт бой для игрока или нет
bool more_by_coordinate = false; // Получение рандомного bool числа для передвижения моба по действию игрока
Game game;
Messages messages;

string UI_Interface[][4] = { // Создаём переменную, в которой храним информацию игрока для вывода в терминал
     {" |#", " # ", " # ", " #  #  # #"}, {}, {}, {}, {}, {}, {" |#", " # ", " # ", " #  #  # #"}
};

// Функция для установки заголовка терминала Windows
void setWindowsConsoleTitle(string title);

void outputToCenter(const std::vector<std::string>& messages, int consoleWidth, int consoleHeight);

// Функция для вывода окна запуска программы
bool UI_Hello(string title, string version, string author, string git);

// Функция для вывода окна завершения программы
void UI_Bye(bool successfully = false, string reason = "");

// Функция для получения рандомного числа в диапазоне от min до max
int random(int min, int max);

struct userData {
    string name;
};

// Функция для записи данных в программу
userData getUserData();

void clearScreen();
LPCSTR stringToLPCSTR(string value);