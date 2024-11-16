#pragma once

using namespace std;

// Создаём некоторую информацию о нашем приложении
class Game {
public:
    const string version = "0.0.9";
    const string name = "@it_cube_cpp_game1";
    const string author = "MasterCont";
    const string git = "https://github.com/MasterCont/it-cube-cpp-game1.git";
    bool debug = false; // если активна, то отображаем раскладку
    bool over = false; // Закончена ли игра
};

// Создаём игрока
class Player {
public:
    string name; // Создаём переменную, в котором запишем имя игрока
    string className = "@player_class_name"; // Создаём переменную, в котором записываем "класс" игрока
    string player_invent[6] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
    int pos_x = 2, pos_y = 2; // Прописываем спавн игрока на координатах по x и y
    int hp = 20; // Создаём хп игроку
    int dmg = 2;
    int inv_i = 0;
    bool moves = false; // Можешь ли игрок ходить независимо от боя
    bool life = true; // Жив ли игрок

    bool hpHas() {
        bool notHave = hp <= 0;
        if (notHave) life = false;
        return notHave ? false : true;
    }
};

// Создаём противника (моба) игрока 
class Enemy {
public:
    string designation = " A "; // Создаём интерфейс моба
    int hp = 10; // Здоровья моба
    int dmg = 2; // Урон моба
    int pos_x = 4, pos_y = 3; // Позиция спавна моба
    bool fight = false; // Определение боя для моба
    bool moves = true; // Может ли моб передвигаться
    bool life = true; // Жив ли моб

    bool hpHas() {
        bool notHave = hp <= 0;
        if (notHave) {
            life = false;
            pos_x = 0;
            pos_y = 0;
        }
        return notHave ? false : true;
    }
};

// Создаём координаты спавна для каждого объекта
class Spawn {
public:
    int li_pos_y = 4, li_pos_x = 4; // Прописываем спавн действия на координатах по x и y
};

class Designations {
public:
    const string loot_item = " * "; // Создаём обозначение действия
    const string border = " # "; // Создаём обозначение границ
    const string player = " P "; // Создаём обозначение игрока
    const string space = " . "; // Создаём обозначение пространства
    const string enemy = " A "; // Создаём обозначение противника (моба)
};

extern bool pick_loot_item = false; // Поднят ли предмет игроком

// Параметры игры для игрока
extern bool fight = false; // Идёт бой для игрока или нет
extern bool can_go = true; // Может ли передвигаться игрок
extern bool more_by_coordinate = false; // Получение рандомного bool числа для передвижения моба по действию игрока

extern int map_number = 0; // Указываем, что по умолчанию загружается первая (нулевая по программе) карта
extern const int maps_size = 6; // Создаём размер барьера

Player player; // Создаём переменную игрока для взаимодействия с игроком
Enemy enemy; // Создаём свойства моба
Spawn spawn; // Создаём переменную для взаимодействия со спавнами объектов
Designations designations;
Game game;

extern string border = designations.border;
extern string space = designations.space;
extern string Maps[][maps_size][maps_size]{


    { // Map 0 - Создаём карту 1
        {border, border, border, border, border, border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, border, border, border, border, border}
    },

    { // Map 1 - Создаём карту 2
        {border, border, border, "   ", "   ", border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {"   ", space , space , space , space , border},
        {border, space , space , space , space , "   "},
        {border, border, border, border, "   ", "   "}
    },

    { // Map 2 - Создаём карту 3
        {border, border, border, "   ", "   ", border},
        {"   ", space , space , space , space , border},
        {"   ", space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space, border},
        {border, border, border, border, "   ", border}
    }

};

// Фукнции для получения разрешения действий, связанных с мобом
bool getActionOnEnemyX(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y);
bool getActionOnEnemyY(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y);
bool getActionOnEnemyLeft(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y);
bool getActionOnEnemyRight(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y);
bool getActionOnEnemyUp(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y);
bool getActionOnEnemyDown(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y);

// Функция для установки заголовка терминала Windows
void setWindowsConsoleTitle(string title);

// Функция для вывода окна запуска программы
void UI_Hello(string title, string version, string author, string git);

// Функция для вывода окна завершения программы
void UI_Bye();

// Функция для получения рандомного числа в диапазоне от min до max
int random(int min, int max);
