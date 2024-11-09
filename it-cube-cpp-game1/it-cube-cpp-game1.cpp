#include <iostream>
#include <string>

using namespace std;

// Создаём некоторую информацию о нашем приложении
string version = "0.0.7";
string name = "@it_cube_cpp_game1";
bool debug = false; // если активна, то отображаем раскладку

// Создаём игрока
class Player {
    public:
        string name; // Создаём переменную, в котором запишем имя игрока
        string className = "@player_class_name"; // Создаём переменную, в котором записываем "класс" игрока
        string player_invent[6] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
        int pos_x = 2, pos_y = 2; // Прописываем спавн игрока на координатах по x и y
        int hp = 10; // Создаём хп игроку
        int dmg = 2;
        int inv_i = 0;
        bool moves = false; // Можешь ли игрок ходить независимо от боя
        bool life = true; // Жив ли игрок
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

Player player; // Создаём переменную игрока для взаимодействия с игроком
Enemy enemy; // Создаём свойства моба
Spawn spawn; // Создаём переменную для взаимодействия со спавнами объектов
Designations designations;


bool pick_loot_item = false; // Поднят ли предмет игроком

// Параметры игры для игрока
bool fight = false; // Идёт бой для игрока или нет
bool can_go = true; // Может ли передвигаться игрок

int map_number = 0; // Указываем, что по умолчанию загружается первая (нулевая по программе) карта

const int maps_size = 6; // Создаём размер барьера
string border = designations.border;
string space = designations.space;
string Maps[][maps_size][maps_size]{


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
bool static getActionOnEnemyX(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y) {
    return (enemy_pos_y == player_pos_y && (enemy_pos_x - 1 == player_pos_x || enemy_pos_x + 1 == player_pos_x));
}

bool static getActionOnEnemyY(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y) {
    return (enemy_pos_x == player_pos_x && (enemy_pos_y - 1 == player_pos_y || enemy_pos_y + 1 == player_pos_y));
}


void static Move(char m) { // Создаём функцию, отвечающую за передвижение игрока

    // Если игрок находится рядом с противником
    bool x_true = getActionOnEnemyX(player.pos_x, player.pos_y, enemy.pos_x, enemy.pos_y); // по абциссе (оси X)
    bool y_true = getActionOnEnemyY(player.pos_x, player.pos_y, enemy.pos_x, enemy.pos_y); // по ординате (оси Y)

    class ChecksOnMove {
    public: // Останавливаем игрока, если...
        bool forward_border = (Maps[map_number][player.pos_y - 1][player.pos_x] != designations.border); // Если впереди будет барьер
        bool back_border = (Maps[map_number][player.pos_y + 1][player.pos_x] != designations.border); // Если сзади будет барьер
        bool left_border = (Maps[map_number][player.pos_y][player.pos_x - 1] != designations.border); // Если слева будет барьер
        bool right_border = (Maps[map_number][player.pos_y][player.pos_x + 1] != designations.border); // Если справа будет барьер

        bool forward_enemy = Maps[map_number][player.pos_y - 1][player.pos_x] != Maps[map_number][enemy.pos_y][enemy.pos_x]; // Если впереди будет противник
        bool back_enemy = Maps[map_number][player.pos_y + 1][player.pos_x] != Maps[map_number][enemy.pos_y][enemy.pos_x]; // Если сзади будет противник
        bool left_enemy = Maps[map_number][player.pos_y][player.pos_x - 1] != Maps[map_number][enemy.pos_y][enemy.pos_x]; // Если слева будет противник
        bool right_enemy = Maps[map_number][player.pos_y][player.pos_x + 1] != Maps[map_number][enemy.pos_y][enemy.pos_x]; // Если справа будет противник
    };

    ChecksOnMove move;


    if (m == 'e' && spawn.li_pos_x == player.pos_x && spawn.li_pos_y == player.pos_y && pick_loot_item == false) {
        // player_invent[player_inv_i] = loot_item;
        // ++player_inv_i; 
        Maps[map_number][player.pos_y][player.pos_x] = designations.space /* = " . " */; // Очищаем положение игрока на исходной карте 
        map_number == size(Maps) - 1 ? map_number = 0 : map_number++; // Переключение на следующую локацию
        Maps[map_number][player.pos_y][player.pos_x] = designations.player /* = " P " */; // Спавним игрока на новой карте
    }

    else if (m == 'w' && move.forward_border && move.forward_enemy) { // != " # "
        Maps[map_number][player.pos_y][player.pos_x] = designations.space /* = " . " */; Maps[map_number][--player.pos_y][player.pos_x] = designations.player;
    }
    else if (m == 's' && move.back_border && move.back_enemy) { // != " # "
        Maps[map_number][player.pos_y][player.pos_x] = designations.space /* = " . " */;; Maps[map_number][++player.pos_y][player.pos_x] = designations.player;
    }
    else if (m == 'a' && move.left_border && move.left_enemy) { // != " # "
        Maps[map_number][player.pos_y][player.pos_x] = designations.space /* = " . " */;; Maps[map_number][player.pos_y][--player.pos_x] = designations.player;
    }
    else if (m == 'd' && move.right_border && move.right_enemy) { // != " # "
        Maps[map_number][player.pos_y][player.pos_x] = designations.space /* = " . " */;; Maps[map_number][player.pos_y][++player.pos_x] = designations.player;
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

    // Если игрок находится рядом с противником
    bool x_true = getActionOnEnemyX(player.pos_x, player.pos_y, enemy.pos_x, enemy.pos_y); // по абциссе (оси X)
    bool y_true = getActionOnEnemyY(player.pos_x, player.pos_y, enemy.pos_x, enemy.pos_y); // по ординате (оси Y)

    if (spawn.li_pos_x == player.pos_x && spawn.li_pos_y == player.pos_y) cout << " # e - Go       # " << endl; // Если игрок находится на координате действия
    if (x_true || y_true) cout << " # q - Action   # " << endl; // Если игрок находится возле противника
    else Maps[map_number][spawn.li_pos_y][spawn.li_pos_x] = designations.loot_item;

    // Вывод интрефейса управления
    cout << endl << " #  #  #  #  #  #  #  #  #  #  #  # #" << endl;
    cout << designations.border << " w-˄;" << " s-˅;" << " a-˂;" << " d-˃;" << " 0-E" << designations.border;
    cout << endl << " #  #  #  #  #  #  #  #  #  #  #  # #" << endl;

    if (debug) { // Вывод интерфейса отладки, если она вызвана
        cout << endl;
        cout << "Version: " << version << endl;
        cout << endl;
        cout << "player.pos_x: " << player.pos_x << " | " << "player.pos_y: " << player.pos_y << endl;
        cout << "player.moves: " << player.moves << endl;
        cout << "player.hp: " << player.hp << endl;
        cout << "player.life: " << player.life << endl;
        cout << endl;
        cout << "enemy.pos_x: " << enemy.pos_x << " | " << "player.pos_y: " << enemy.pos_y << endl;
        cout << "enemy.moves: " << enemy.moves << endl;
        cout << "enemy.hp: " << enemy.hp << endl;
        cout << "enemy.life: " << enemy.life << endl;
        cout << endl;
        cout << "map_number: " << map_number << endl;
        cout << "pick_loot_item: " << pick_loot_item;
        cout << "fight_for_enemy: " << enemy.fight;
        cout << " fight: " << fight << endl;
       // cout << "life: " << life;
       // cout << " f_string: " << f_string << endl;
        // cout << " can_go: " << can_go << endl;
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
    Maps[map_number][player.pos_y][player.pos_x] = designations.player; // Указываем, что в этой координате спанится игрок и выводим его
    Maps[map_number][spawn.li_pos_y][spawn.li_pos_x] = designations.loot_item; // Указываем, что в этой координате спанится действие и выводим его
    Maps[map_number][enemy.pos_y][enemy.pos_x] = designations.enemy; // Указываем, что в этой координате будет спавниться моб
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