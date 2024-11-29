#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "modules.h";
#include <unordered_map>
#include "maps.h";
#include "player.h";
#include "enemy.h";
#include "spawn.h";

using namespace std;

// Фукнции дл¤ получени¤ разрешени¤ действий, св¤занных с мобом
bool getActionOnEnemyX(Player player, Enemy enemy) {
    return (enemy.life && (enemy.pos_y == player.pos_y && (enemy.pos_x - 1 == player.pos_x || enemy.pos_x + 1 == player.pos_x)));
}

bool getActionOnEnemyY(Player player, Enemy enemy) {
    return (enemy.life && (enemy.pos_x == player.pos_x && (enemy.pos_y - 1 == player.pos_y || enemy.pos_y + 1 == player.pos_y)));
}

bool getActionOnEnemyLeft(Player player, Enemy enemy) {
    return (enemy.life && (enemy.pos_y == player.pos_y && (enemy.pos_x + 1 == player.pos_x)));
}

bool getActionOnEnemyRight(Player player, Enemy enemy) {
    return (enemy.life && (enemy.pos_y == player.pos_y && (enemy.pos_x - 1 == player.pos_x)));
}

bool getActionOnEnemyUp(Player player, Enemy enemy) {
    return (enemy.life && (enemy.pos_x == player.pos_x && (enemy.pos_y + 1 == player.pos_y)));
}
bool getActionOnEnemyDown(Player player, Enemy enemy) {
    return (enemy.life && (enemy.pos_x == player.pos_x && (enemy.pos_y - 1 == player.pos_y)));
}

string title = game.name; // Dummy

class ChecksOnMove {
public: // Останавливаем игрока, если...
    bool forward_border = (Maps[map_number][player.pos_y - 1][player.pos_x].id != objects.border.id); // Если впереди будет барьер
    bool back_border = (Maps[map_number][player.pos_y + 1][player.pos_x].id != objects.border.id); // Если сзади будет барьер
    bool left_border = (Maps[map_number][player.pos_y][player.pos_x - 1].id != objects.border.id); // Если слева будет барьер
    bool right_border = (Maps[map_number][player.pos_y][player.pos_x + 1].id != objects.border.id); // Если справа будет барьер

    bool forward_space_for_enemy = (Maps[map_number][enemy.pos_y - 1][enemy.pos_x].id == objects.space.id); // Если впереди будет барьер
    bool back_space_for_enemy = (Maps[map_number][enemy.pos_y + 1][enemy.pos_x].id == objects.space.id); // Если сзади будет барьер
    bool left_space_for_enemy = (Maps[map_number][enemy.pos_y][enemy.pos_x - 1].id == objects.space.id); // Если слева будет барьер
    bool right_space_for_enemy = (Maps[map_number][enemy.pos_y][enemy.pos_x + 1].id == objects.space.id); // Если справа будет барьер

    bool forward_enemy = !enemy.life || (Maps[map_number][player.pos_y - 1][player.pos_x].id != objects.enemy.id); // Если впереди будет противник
    bool back_enemy = !enemy.life || (Maps[map_number][player.pos_y + 1][player.pos_x].id != objects.enemy.id); // Если сзади будет противник
    bool left_enemy = !enemy.life || (Maps[map_number][player.pos_y][player.pos_x - 1].id != objects.enemy.id); // Если слева будет противник
    bool right_enemy = !enemy.life || (Maps[map_number][player.pos_y][player.pos_x + 1].id != objects.enemy.id); // Если справа будет противник
};

void static Move(char m) { // Создаём функцию, отвечающую за передвижение игрока

    // Если игрок находится рядом с противником
    bool x_true = getActionOnEnemyX(player, enemy); // по абциссе (оси X)
    bool x_true_right = getActionOnEnemyRight(player, enemy);
    bool x_true_left = getActionOnEnemyLeft(player, enemy);

    bool y_true = getActionOnEnemyY(player, enemy); // по ординате (оси Y)
    bool y_true_up = getActionOnEnemyUp(player, enemy);
    bool y_true_down = getActionOnEnemyDown(player, enemy);

    ChecksOnMove move;


    if (m == 'e' && spawn.action_pos_x == player.pos_x && spawn.action_pos_y == player.pos_y && pick_loot_item == false) {
        // player_invent[player_inv_i] = loot_item;
        // ++player_inv_i; 
        Maps[map_number][player.pos_y][player.pos_x] = objects.space /* = " . " */; // Очищаем положение игрока на исходной карте 
        map_number == size(Maps) - 1 ? map_number = 0 : map_number++; // Переключение на следующую локацию
        Maps[map_number][player.pos_y][player.pos_x] = objects.player /* = " P " */; // Спавним игрока на новой карте
        game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
    }

    else if (m == 'q' && (x_true || y_true)) { // Если игрок наносит удар мобу, то

        enemy.hp = enemy.hp - player.dmg; // Убавляем мобу хп
        more_by_coordinate = random(0, 4); // Откидываем моба рандомно

        // Откидываем моба на рандомные координаты
        if (x_true) { // Если удар наноситя по абциссе

            if (x_true_right) {

                if (move.right_space_for_enemy) { // Если моба можно откинуть от игрока
                    if (enemy.hpHas(map_number)) Maps[map_number][enemy.pos_y][++enemy.pos_x] = objects.enemy; // Передвигаем моба                    
                    Maps[map_number][player.pos_y][++player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }

                else if (more_by_coordinate && move.forward_space_for_enemy) { // Если откидываем вверх
                    if (enemy.hpHas(map_number)) Maps[map_number][--enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба                    
                    Maps[map_number][player.pos_y][++player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }

                else if (move.back_space_for_enemy) {
                    if (enemy.hpHas(map_number)) Maps[map_number][++enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба
                    Maps[map_number][player.pos_y][++player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }
            }

            else if (x_true_left) {

                if (move.left_space_for_enemy) { // Если моба можно откинуть от игрока
                    if (enemy.hpHas(map_number)) Maps[map_number][enemy.pos_y][--enemy.pos_x] = objects.enemy; // Передвигаем моба                    
                    Maps[map_number][player.pos_y][--player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }

                else if (more_by_coordinate && (move.forward_space_for_enemy)) { // Если откидываем вверх
                    if (enemy.hpHas(map_number)) Maps[map_number][--enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба
                    Maps[map_number][player.pos_y][--player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }

                else if (move.back_space_for_enemy) {
                    if (enemy.hpHas(map_number)) Maps[map_number][++enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба
                    Maps[map_number][player.pos_y][--player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }
            }

        }

        else if (y_true) { // Если удар наноситя по абциссе

            if (y_true_up) {

                if (move.forward_space_for_enemy) { // Если моба можно откинуть от игрока
                    if (enemy.hpHas(map_number)) Maps[map_number][--enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба                    
                    Maps[map_number][--player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }

                else if (more_by_coordinate && (move.left_space_for_enemy)) { // Если откидываем направо
                    if (enemy.hpHas(map_number)) Maps[map_number][enemy.pos_y][--enemy.pos_x] = objects.enemy; // Передвигаем моба
                    Maps[map_number][--player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }

                else if (move.right_space_for_enemy) {
                    if (enemy.hpHas(map_number)) Maps[map_number][enemy.pos_y][++enemy.pos_x] = objects.enemy; // Передвигаем моба
                    Maps[map_number][--player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }

            }

            else if (y_true_down) {

                if (move.back_space_for_enemy) { // Если моба можно откинуть от игрока
                    if (enemy.hpHas(map_number)) Maps[map_number][++enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба                    
                    Maps[map_number][++player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }

                else if (more_by_coordinate && (move.left_space_for_enemy)) { // Если откидываем направо
                    if (enemy.hpHas(map_number)) Maps[map_number][enemy.pos_y][--enemy.pos_x] = objects.enemy; // Передвигаем моба
                    Maps[map_number][++player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }

                else if (move.right_space_for_enemy) {
                    if (enemy.hpHas(map_number)) Maps[map_number][enemy.pos_y][++enemy.pos_x] = objects.enemy; // Передвигаем моба
                    Maps[map_number][++player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                }

            }

        }

        // Убавляем игроку хп
        player.hp = player.hp - enemy.dmg;
        if (!player.hpHas()) game.over = true; // Если у игрока не осталось хп, то прекращаем игру
        game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
    }

    else if (m == 'w' && move.forward_border && move.forward_enemy) { // != " # "
        Maps[map_number][--player.pos_y][player.pos_x];
        game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
    }
    else if (m == 's' && move.back_border && move.back_enemy) { // != " # "
        Maps[map_number][++player.pos_y][player.pos_x];
        game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
    }
    else if (m == 'a' && move.left_border && move.left_enemy) { // != " # "
        Maps[map_number][player.pos_y][--player.pos_x];
        game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
    }
    else if (m == 'd' && move.right_border && move.right_enemy) { // != " # "
        Maps[map_number][player.pos_y][++player.pos_x];
        game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
    }

    else if (m == 'i') !game.debug ? game.debug = true : game.debug = false; // Вызов отладки

    else game.ui_update_permission = false; // Если действие бесполезно, то останавливаем цикличное обновление интерфейса

}

void static UI_Update() { // Функцией обновляем данные в переменную UI_Interface
    UI_Interface[1][0] = " | Имя: " + player.name + "    ", " # ";
    UI_Interface[2][0] = " | Класс: " + player.className + "  ", " # ";
    UI_Interface[3][0] = " | HP: " + to_string(player.hp) + "        ", " # ";
    UI_Interface[4][0] = " | DMG: " + to_string(player.dmg) + "        ", " # ";
    UI_Interface[5][0] = " | MAP: #" + to_string(map_number);
}

void static UI_Map() { // Функция, которая выводит интерфейс управления игрой

    // Если игрок находится рядом с противником
    bool x_true = getActionOnEnemyX(player, enemy); // по абциссе (оси X)
    bool x_true_right = getActionOnEnemyRight(player, enemy);
    bool x_true_left = getActionOnEnemyLeft(player, enemy);

    bool y_true = getActionOnEnemyY(player, enemy); // по ординате (оси Y)
    bool y_true_up = getActionOnEnemyUp(player, enemy);
    bool y_true_down = getActionOnEnemyDown(player, enemy);

    if (spawn.action_pos_x == player.pos_x && spawn.action_pos_y == player.pos_y) cout << " # e - Go       # " << endl; // Если игрок находится на координате действия
    if (x_true || y_true) cout << " # q - Action   # " << endl; // Если игрок находится возле противника
    else Maps[map_number][spawn.action_pos_y][spawn.action_pos_x] = objects.action;

    // Вывод интрефейса управления
    cout << endl << " #  #  #  #  #  #  #  #  #  #  #  # #" << endl;
    cout << objects.border.designation << " w-˄;" << " s-˅;" << " a-˂;" << " d-˃;" << " 0-E" << objects.border.designation;
    cout << endl << " #  #  #  #  #  #  #  #  #  #  #  # #" << endl;

    if (game.debug) { // Вывод интерфейса отладки, если она вызвана

        // Обновление заголовка терминала для Windows
        setWindowsConsoleTitle(title + " | " + game.version + " | " + game.author);
        ChecksOnMove move;

        cout << endl;
        cout << "Version: " << game.version << endl;
        cout << endl;
        cout << "player.pos_x: " << player.pos_x << " | " << "player.pos_y: " << player.pos_y << endl;
        cout << "player_pos_name: " << Maps[map_number][player.pos_y][player.pos_x].name << endl;
        cout << "player.moves: " << player.moves << endl;
        cout << "player.hp: " << player.hp << endl;
        cout << "player.life: " << player.life << endl;
        cout << endl;
        cout << "enemy.pos_x: " << enemy.pos_x << " | " << "enemy.pos_y: " << enemy.pos_y << endl;
        cout << "enemy_pos_name: " << Maps[map_number][enemy.pos_y][enemy.pos_x].name << endl;
        cout << "enemy.moves: " << enemy.moves << endl;
        cout << "enemy.hp: " << enemy.hp << endl;
        cout << "enemy.life: " << enemy.life << endl;
        cout << "enemy.hpHas(map_number): " << enemy.hpHas(map_number) << endl;
        cout << endl;
        cout << "map_number: " << map_number << endl;
        cout << "pick_loot_item: " << pick_loot_item;
        cout << " fight_for_enemy: " << enemy.fight;
        cout << " fight: " << fight << endl;
        // cout << "life: " << life;
        cout << "x_true: " << x_true;
        cout << " y_true: " << y_true << endl;
        cout << "x_true_left: " << x_true_left;
        cout << " x_true_right: " << x_true_right;
        cout << " | y_true_up: " << y_true_up;
        cout << " y_true_down: " << y_true_down << endl;
        cout << "more_by_coordinate: " << more_by_coordinate << endl;
        cout << endl;
        cout << "move.back_border: " << move.back_border << " | " << "move.back_enemy: " << move.back_enemy << endl;
        cout << "move.forward_border: " << move.forward_border << " | " << "move.forward_enemy: " << move.forward_enemy << endl;
        cout << "move.left_border: " << move.left_border << " | " << "move.left_enemy: " << move.left_enemy << endl;
        cout << "move.right_border: " << move.right_border << " | " << "move.right_enemy: " << move.right_enemy << endl;
    }
    else {
        // Cброс заголовка терминала для Windows
        setWindowsConsoleTitle(title);
    }
}

void static Render_map() { // Функция, которая обновляет интерфейс карты при изменении действий в игре
    UI_Update(); // Обновляем интерфейс информации игрока

    // Метод для проверки нахождения объекта на координате
     /* bool checkСoordinate(int el_pos_y, int el_pos_x) {
            return (el_pos_y == i && j == el_pos_x) ? true : false;
        }*/

    for (int i = 0; i < size(Maps[map_number]); i++) {
        for (int j = 0; j < size(Maps[map_number][i]); j++) { // Вывод карты игрока

            // Созданим структуру объекта, в которой будет хранится позиция координаты
            struct thisObject {
                bool special = false;
                object object;
            };

            // Инициализируем координату
            thisObject position;

            // if (checkСoordinate(player.pos_y, player.pos_x)) position = {true, objects.player}; // Если на этой координате игрок, то добавляем его в приоритете отображения
            // if (checkСoordinate(enemy.pos_y, enemy.pos_x)) position = { true, objects.enemy }; // Если на этой координате игрок, то добавляем его в приоритете отображения

             // Отображение идёт по приоритетам, например, если игрок находится на действии, то последним отображать игрока
            if (spawn.action_pos_y == i && spawn.action_pos_y == j) position = { true, objects.action }; // Если на этой координате игрок, то добавляем его в приоритете отображения
            if ((enemy.pos_y == i && enemy.pos_x == j) && (enemy.life && enemy.hpHas(map_number)) && (Maps[map_number][enemy.pos_y][enemy.pos_x].id == objects.enemy.id)) position = { true, objects.enemy }; // Если на этой координате игрок, то добавляем его в приоритете отображения
            if ((player.pos_y == i && player.pos_x == j) && player.life) position = { true, objects.player }; // Если на этой координате игрок, то добавляем его в приоритете отображения

            if (position.special) cout << position.object.designation;
            else cout << Maps[map_number][i][j].designation;

        }
        for (int J = 0; J < size(UI_Interface[i]); J++) { // Вывод информации игрока
            cout << UI_Interface[i][J];
        }
        cout << endl;
    }
}


int main() { // Главная функция
    setlocale(LC_ALL, "Russian.UTF-8"); // Устанавливаем русский язык в консоли

    // Установка заголовка терминала для Windows
    setWindowsConsoleTitle(title);

    // Выводим интрфейс приветствия
    UI_Hello(title, game.version, game.author, game.git);

    // Добавляем персонажу имя/название
    string name = getUserData().name;
    UI_Interface[1][1] = name;
    

    map_number = 0; // При запуске игры устанавливаем первую (нулевую в программе) карту
    while (!game.over) { // Запускаем бесконечный цикл, чтобы программа не останавливалась, если произведётся действие
        enemy.initialization(); // Указываем, что в этой координате будет спавниться моб
        
        // Обновляем интерфейс по разрешению 
        if (game.ui_update_permission) {
            system("cls"); // Обновляем интрфейс терминала, (если оно вообще у вас будет работать) чтобы не было большого вывода символов
            if (player.hp <= 0) game.over = true; // Если у игрока нет хп, то прекращаем игру
            Render_map(); // Обновляем интрефейс карты
            // Render_Invert();
            UI_Map(); // Обновляем интрефейс управления
        }

        char ch;
        ch = _getch();
        if (ch == '0') { break; } // Остановка программы, если указан прописанный символ в ковычках
        Move(tolower(ch)); // Совершаем некоторое действие, указанное от игрока

    }

    //Если игра закончена, то выводим интерфейс об окончании игры
    UI_Bye();

}
