#pragma once
#include <unordered_map>

using namespace std;

// Создаём некоторую информацию о нашем приложении
class Game {
public:
    const string version = "0.1.0 reloaded";
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

// Создаём координаты спавна для каждого объекта
class Spawn {
public:
    int action_pos_y = 4, action_pos_x = 4; // Прописываем спавн действия на координатах по x и y
};

struct object {
    int id;
    string name;
    string designation;
};

// Создаём список всех объектов на карте игры
class Objects {
public:
    const object _void = { 0, "void", " X " }; // Создаём обозначение пустого объекта
    const object space = { 1, "space", " . " }; // Создаём обозначение пространства
    const object border = { 2, "border", " # " }; // Создаём обозначение границ
    const object action = { 3, "action", " * " }; // Создаём обозначение действия
    const object player = { 4, "player", " P " }; // Создаём обозначение игрока
    const object enemy = { 5, "enemy", " A " }; // Создаём обозначение противника (моба)

};


bool pick_loot_item = false; // Поднят ли предмет игроком

// Параметры игры для игрока
bool fight = false; // Идёт бой для игрока или нет
bool can_go = true; // Может ли передвигаться игрок
bool more_by_coordinate = false; // Получение рандомного bool числа для передвижения моба по действию игрока

int map_number = 0; // Указываем, что по умолчанию загружается первая (нулевая по программе) карта
const int maps_size = 6; // Создаём размер барьера

Player player; // Создаём переменную игрока для взаимодействия с игроком
Spawn spawn; // Создаём переменную для взаимодействия со спавнами объектов
Game game;
Objects objects;

object border = objects.border;
object space = objects.space;
object Maps[][maps_size][maps_size]{


    { // Map 0 - Создаём карту 1
        {border, border, border, border, border, border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, border, border, border, border, border}
    },

    { // Map 1 - Создаём карту 2
        {border, border, border, space, space, border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {space, space , space , space , space , border},
        {border, space , space , space , space , space},
        {border, border, border, border, space, space}
    },

    { // Map 2 - Создаём карту 3
        {border, border, border, space, space, border},
        {space, space , space , space , space , border},
        {space, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space, border},
        {border, border, border, border, space, border}
    }

};

// Создаём противника (моба) игрока 
class Enemy {
public:
    string designation = " A "; // Создаём интерфейс моба
    int hp = 10; // Здоровья моба
    int dmg = 2; // Урон моба
    int pos_x = 3, pos_y = 3; // Позиция спавна моба
    bool fight = false; // Определение боя для моба
    bool moves = true; // Может ли моб передвигаться
    bool life = false; // Жив ли моб

    bool hpHas(int map_number) {
        bool notHave = (hp <= 0);
        if (notHave) {
            life = false;
            Maps[map_number][pos_y][pos_x] = objects.space;
            pos_x = -1;
            pos_y = -1;
        }
        return notHave ? false : true;
    }

    bool initialization() {
        life = true;
        Maps[0][pos_y][pos_x] = objects.enemy;
        return life ? true : false;
    }
};

Enemy enemy; // Создаём свойства моба

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
