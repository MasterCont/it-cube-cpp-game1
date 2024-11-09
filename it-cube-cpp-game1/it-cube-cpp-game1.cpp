#include <iostream>
#include <string>

using namespace std;

// Создаём некоторую информацию о нашем приложении
string version = "0.0.5";
string name = "@it_cube_cpp_game1";
bool debug = false; // если активна, то отображаем раскладку

// Создаём игрока
class Player {
    public:
        string designation = " P "; // Создаём интерфейс игрока
        string name; // Создаём переменную, в котором запишем имя игрока
        string className = "@player_class_name"; // Создаём переменную, в котором записываем "класс" игрока
        int pos_x = 2, pos_y = 2; // Прописываем спавн игрока на координатах по x и y
        int hp = 10; // Создаём хп игроку
        int dmg = 2;
};

// Создаём противника (моба) игрока
class Enemy {
    public:
        string designation = " A "; // Создаём интерфейс моба
        int hp = 20; // Здоровья моба
        int dmg = 2; // Урон моба
        int pos_x = 4, pos_y = 3; // Позиция спавна моба
        bool fight = false; // Определение боя для моба
        bool moves = true; // Может ли моб передвигаться
        bool life = true; // Жив ли моб
};


Player player; // Создаём переменную игрока для взаимодействия с игроком
Enemy enemy; // Создаём свойства моба


string loot_item = " * "; // Создаём интерфейс действия
int li_y = 4, li_x = 4; // Прописываем спавн действия на координатах по x и y

string hero_invent[6] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
int player_inv_i = 0;
bool pick_loot_item = false; // Поднят ли предмет игроком

// Параметры игры для игрока
bool fight = false; // Идёт бой для игрока или нет
bool player_moves = false; // Можешь ли игрок ходить независимо от боя
bool can_go = true; // Может ли передвигаться игрок

int map_number = 0; // Указываем, что по умолчанию загружается первая (нулевая по программе) карта

const int maps_size = 6;
string Maps[][maps_size][maps_size]{

    { // Map 0 - Создаём карту 1
        {" # ", " # ", " # ", " # ", " # ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " # ", " # ", " # ", " # ", " # "}
    },

    { // Map 1 - Создаём карту 2
        {" # ", " # ", " # ", "   ", "   ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {"   ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", "   "},
        {" # ", " # ", " # ", " # ", "   ", "   "}
    },

    { // Map 2 - Создаём карту 3
        {" # ", " # ", " # ", "   ", "   ", " # "},
        {"   ", " . ", " . ", " . ", " . ", " # "},
        {"   ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " # ", " # ", " # ", "   ", " # "}
    }
    
};

// Фукнции для получения разрешения действий, связанных с мобом
bool static getActionOnEnemyX(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y) {
    return (enemy_pos_y == player_pos_y && (enemy_pos_x - 1 == player_pos_x || enemy_pos_x + 1 == player_pos_x));
}

bool static getActionOnEnemyY(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y) {
    return (enemy_pos_x == player_pos_x && (enemy_pos_y - 1 == player_pos_y || enemy_pos_y + 1 == player_pos_y));
}


void static Move(char m) { // Создаём функцию, отвечающую за передвижение игрока
    if (m == 'e' && li_x == player.pos_x && li_y == player.pos_y && pick_loot_item == false) {
        // player_invent[player_inv_i] = loot_item;
        // ++player_inv_i; 
        Maps[map_number][player.pos_y][player.pos_x] = " . "; // Очищаем положение игрока на исходной карте
        map_number == size(Maps) - 1 ? map_number = 0 : map_number++; // Переключение на следующую локацию
        Maps[map_number][player.pos_y][player.pos_x] = " P "; // Спавним игрока на новой карте
    }

    else if (m == 'w' && (Maps[map_number][player.pos_y - 1][player.pos_x] != " # ")) {
        Maps[map_number][player.pos_y][player.pos_x] = " . "; Maps[map_number][--player.pos_y][player.pos_x] = player.designation;
    }
    else if (m == 's' && (Maps[map_number][player.pos_y + 1][player.pos_x] != " # ")) {
        Maps[map_number][player.pos_y][player.pos_x] = " . "; Maps[map_number][++player.pos_y][player.pos_x] = player.designation;
    }
    else if (m == 'a' && (Maps[map_number][player.pos_y][player.pos_x - 1] != " # ")) {
        Maps[map_number][player.pos_y][player.pos_x] = " . "; Maps[map_number][player.pos_y][--player.pos_x] = player.designation;
    }
    else if (m == 'd' && (Maps[map_number][player.pos_y][player.pos_x + 1] != " # ")) {
        Maps[map_number][player.pos_y][player.pos_x] = " . "; Maps[map_number][player.pos_y][++player.pos_x] = player.designation;
    }

    else if (m == 'i') !debug ? debug = true : debug = false; // Вызов отладки
}

string interface[][4] = { // Создаём переменную, в которой храним информацию игрока для вывода в терминал
     {" |#", " # ", " # ", " #  #  # #"}, {}, {}, {}, {}, {}, {" |#", " # ", " # ", " #  #  # #"}
};

void static UI_Update() { // Функцией обновляем данные в переменную interface
    interface[1][0] = " | Имя: " + player.name + "    ", " # ";
    interface[2][0] = " | Класс: " + player.className + "  ", " # ";
    interface[3][0] = " | HP: " + to_string(player.hp) + "        ", " # ";
    interface[4][0] = " | DMG: " + to_string(player.dmg) + "        ", " # ";
    interface[5][0] = " | MAP: #" + to_string(map_number);
}



void static UI_Map() { // Функция, которая выводит интерфейс управления игрой
    bool x_true = getActionOnEnemyX(player.pos_x, player.pos_y, enemy.pos_x, enemy.pos_y);
    bool y_true = getActionOnEnemyY(player.pos_x, player.pos_y, enemy.pos_x, enemy.pos_y);
    if (li_x == player.pos_x && li_y == player.pos_y) {
        cout << " # e - Go       # " << endl;

    }
    else { Maps[map_number][li_y][li_x] = loot_item; }
    cout << " # w - ↑ || s - ↓ || a - ← || d - → # " << endl;
    cout << " # 0 - exit                         # " << endl;
    cout << " #  #  #  #  #  #  #  #  #  #  #  # #" << endl;

    if (debug) {
       cout << "player_moves: " << player_moves;
       // cout << " can_go: " << can_go << endl;
        cout << "HP: " << player.hp << endl;
        cout << "map_number: " << map_number << endl;
        cout << "pick_loot_item: " << pick_loot_item;
        cout << " enemy_entity_HP: " << enemy.hp << endl;
        cout << "fight_for_enemy: " << enemy.fight;
        cout << " fight: " << fight << endl;
        cout << "enemy_life: " << enemy.life;
        cout << " enemy_moves: " << enemy.moves << endl;
       // cout << "life: " << life;
       // cout << " f_string: " << f_string << endl;
       cout << "x_true: " << x_true;
       cout << " y_true: " << y_true << endl;
    }
}

void static Render_map() { // Функция, которая обновляет интерфейс карты при изменении действий в игре
    UI_Update(); // Обновляем интерфейс информации игрока
    for (int i = 0; i < size(Maps[map_number]); i++) {
        for (int j = 0; j < size(Maps[map_number][i]); j++) { // Вывод карты игрока
             cout << Maps[map_number][i][j];
        }
        for (int J = 0; J < size(interface[i]); J++) { // Вывод информации игрока
            cout << interface[i][J];
        }
        cout << endl;
    }
}


int main() { // Главная функция
    setlocale(LC_ALL, "ru.utf-8"); // Устанавливаем русский язык в консоли

    cout << "Введите имя вашего персонажа: ";
    cin >> interface[1][1];
    interface[1][1] += "  #";

    map_number = 0; // При запуске игры устанавливаем первую (нулевую в программе) карту
    Maps[map_number][player.pos_y][player.pos_x] = player.designation; // Указываем, что в этой координате спанится игрок и выводим его
    Maps[map_number][li_y][li_x] = loot_item; // Указываем, что в этой координате спанится действие и выводим его
    while (true) { // Запускаем бесконечный цикл, чтобы программа не останавливалась, если произведётся действие
        system("cls"); // Обновляем интрфейс терминала, (если оно вообще у вас будет работать) чтобы не было большого вывода символов
        Render_map(); // Обновляем интрефейс карты
        // Render_Invert();
        UI_Map(); // Обновляем интрефейс управления
        char ch;
        cin >> ch;
        if (ch == '0') { break; } // Остановка программы, если указан прописанный символ в ковычках
        Move(ch); // Совершаем некоторое действие, указанное от игрока
    }
}