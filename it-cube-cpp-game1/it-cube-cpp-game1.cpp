#include <iostream>
#include <string>
#include <Windows.h>
#include "modules.h";

using namespace std;

string title = game.name;

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
   
    else if (m == 'i') !game.debug ? game.debug = true : game.debug = false; // Вызов отладки
}

string UI_Interface[][4] = { // Создаём переменную, в которой храним информацию игрока для вывода в терминал
     {" |#", " # ", " # ", " #  #  # #"}, {}, {}, {}, {}, {}, {" |#", " # ", " # ", " #  #  # #"}
};

void static UI_Update() { // Функцией обновляем данные в переменную UI_Interface
    UI_Interface[1][0] = " | Имя: " + player.name + "    ", " # ";
    UI_Interface[2][0] = " | Класс: " + player.className + "  ", " # ";
    UI_Interface[3][0] = " | HP: " + to_string(player.hp) + "        ", " # ";
    UI_Interface[4][0] = " | DMG: " + to_string(player.dmg) + "        ", " # ";
    UI_Interface[5][0] = " | MAP: #" + to_string(map_number);
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

    if (game.debug) { // Вывод интерфейса отладки, если она вызвана

        // Обновление заголовка терминала для Windows
        setWindowsConsoleTitle(title + " | " + game.version + " | " + game.author);

        cout << endl;
        cout << "Version: " << game.version << endl;
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
    else {
        // Cброс заголовка терминала для Windows
        setWindowsConsoleTitle(title);
    }
}

void static Render_map() { // Функция, которая обновляет интерфейс карты при изменении действий в игре
    UI_Update(); // Обновляем интерфейс информации игрока
    for (int i = 0; i < size(Maps[map_number]); i++) {
        for (int j = 0; j < size(Maps[map_number][i]); j++) { // Вывод карты игрока
             cout << Maps[map_number][i][j];
        }
        for (int J = 0; J < size(UI_Interface[i]); J++) { // Вывод информации игрока
            cout << UI_Interface[i][J];
        }
        cout << endl;
    }
}


int main() { // Главная функция
    setlocale(LC_ALL, "ru.utf-8"); // Устанавливаем русский язык в консоли

    // Установка заголовка терминала для Windows
    setWindowsConsoleTitle(title);

    // Выводим интрфейс приветствия
    UI_Hello(title, game.version, game.author, game.git);

    // Добавляем персонажу имя/название
    cout << "Введите имя вашего персонажа: ";
    cin >> UI_Interface[1][1];

    map_number = 0; // При запуске игры устанавливаем первую (нулевую в программе) карту
    Maps[map_number][player.pos_y][player.pos_x] = designations.player; // Указываем, что в этой координате спанится игрок и выводим его
    Maps[map_number][spawn.li_pos_y][spawn.li_pos_x] = designations.loot_item; // Указываем, что в этой координате спанится действие и выводим его
    while (true) { // Запускаем бесконечный цикл, чтобы программа не останавливалась, если произведётся действие
        Maps[map_number][enemy.pos_y][enemy.pos_x] = designations.enemy; // Указываем, что в этой координате будет спавниться моб
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