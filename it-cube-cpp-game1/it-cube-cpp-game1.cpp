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
#include <vector>

using namespace std;

class ChecksOnMove {
public: // Останавливаем игрока, если...
    bool forward_border = (Maps[game.map_number][player.pos_y - 1][player.pos_x].id != objects.border.id); // Если впереди будет барьер
    bool back_border = (Maps[game.map_number][player.pos_y + 1][player.pos_x].id != objects.border.id); // Если сзади будет барьер
    bool left_border = (Maps[game.map_number][player.pos_y][player.pos_x - 1].id != objects.border.id); // Если слева будет барьер
    bool right_border = (Maps[game.map_number][player.pos_y][player.pos_x + 1].id != objects.border.id); // Если справа будет барьер

    bool forward_space_for_enemy(sEnemyObject enemy) { // Если впереди будет барьер
        return (Maps[game.map_number][enemy.pos_y - 1][enemy.pos_x].id == objects.space.id);
    }

    bool back_space_for_enemy(sEnemyObject enemy) { // Если сзади будет барьер
        return (Maps[game.map_number][enemy.pos_y + 1][enemy.pos_x].id == objects.space.id);
    };

    bool left_space_for_enemy(sEnemyObject enemy) { // Если слева будет барьер
        return (Maps[game.map_number][enemy.pos_y][enemy.pos_x - 1].id == objects.space.id);
    }

    bool right_space_for_enemy(sEnemyObject enemy) { // Если справа будет барьер
        return (Maps[game.map_number][enemy.pos_y][enemy.pos_x + 1].id == objects.space.id);
    }

};

// В этом классе будем хранить всю информацию о сущностях
class Entities {
public:

    class Enemy {
    public:
        vector<sEnemyObject> list; // Список всех enemy в игре

        int hp = 10;
        int dmg = 2;

        bool initialization(int map_number, sEnemyObject enemy) {
            enemy.life = true;
            list.push_back(enemy);
            Maps[map_number][enemy.pos_y][enemy.pos_x] = objects.enemy;
            return enemy.life ? true : false;
        }

        bool create(int map_number, int pos_x, int pos_y) {
            int enemyID = list.size();
            sEnemyObject enemy = { enemyID, hp, dmg, pos_x, pos_y, true }; // Создаём моба
            initialization(map_number, enemy);
            return true;
        }

        sEnemyObject getByCoord(int pos_x, int pos_y) {
            // Не очень перспективный метод, но работающий:
            for (const auto& enemy : list) {
                if (enemy.pos_x == pos_x && enemy.pos_y == pos_y) return enemy;
            }
        }

        sEnemyObject getById(int id) {
            // Не очень перспективный метод, но работающий:
            for (const auto& enemy : list) {
                if (enemy.id == id) return enemy;
            }
        }

        bool move_right(int id) {
            ++list[id].pos_x;
            return true;
        };

        bool move_left(int id) {
            --list[id].pos_x;
            return true;
        };

        bool move_up(int id) {
            --list[id].pos_y;
            return true;
        };

        bool move_down(int id) {
            ++list[id].pos_y;
            return true;
        };

        bool attack(ChecksOnMove move, sEnemyObject enemy, bool x_true, bool y_true, bool x_true_right, bool x_true_left, bool y_true_up, bool y_true_down) {
            list[enemy.id].hp = list[enemy.id].hp - player.dmg; // Убавляем мобу хп
            more_by_coordinate = random(0, 4); // Откидываем моба рандомно

            // Откидываем моба на рандомные координаты
            if (x_true) { // Если удар наноситя по абциссе

                if (x_true_right) {

                    if (move.right_space_for_enemy(enemy)) { // Если моба можно откинуть от игрока
                        if (this->move_right(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][enemy.pos_y][++enemy.pos_x] = objects.enemy; // Передвигаем моба                    
                            Maps[game.map_number][player.pos_y][++player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }

                    else if (more_by_coordinate && move.forward_space_for_enemy(enemy)) { // Если откидываем вверх
                        if (this->move_up(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][--enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба                    
                            Maps[game.map_number][player.pos_y][++player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }

                    else if (move.back_space_for_enemy(enemy)) {
                        if (this->move_down(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][++enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба
                            Maps[game.map_number][player.pos_y][++player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }
                }

                else if (x_true_left) {

                    if (move.left_space_for_enemy(enemy)) { // Если моба можно откинуть от игрока
                        if (this->move_left(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][enemy.pos_y][--enemy.pos_x] = objects.enemy; // Передвигаем моба                    
                            Maps[game.map_number][player.pos_y][--player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }

                    else if (more_by_coordinate && (move.forward_space_for_enemy(enemy))) { // Если откидываем вверх
                        if (this->move_up(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][--enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба
                            Maps[game.map_number][player.pos_y][--player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }

                    else if (move.back_space_for_enemy(enemy)) {
                        if (this->move_down(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][++enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба
                            Maps[game.map_number][player.pos_y][--player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }
                }

            }

            else if (y_true) { // Если удар наноситя по абциссе

                if (y_true_up) {

                    if (move.forward_space_for_enemy(enemy)) { // Если моба можно откинуть от игрока
                        if (this->move_up(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][--enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба                    
                            Maps[game.map_number][--player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }

                    else if (more_by_coordinate && (move.left_space_for_enemy(enemy))) { // Если откидываем направо
                        if (this->move_right(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][enemy.pos_y][--enemy.pos_x] = objects.enemy; // Передвигаем моба
                            Maps[game.map_number][--player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }

                    else if (move.right_space_for_enemy(enemy)) {
                        if (this->move_right(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][enemy.pos_y][++enemy.pos_x] = objects.enemy; // Передвигаем моба
                            Maps[game.map_number][--player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }

                }

                else if (y_true_down) {

                    if (move.back_space_for_enemy(enemy)) { // Если моба можно откинуть от игрока
                        if (this->move_down(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][++enemy.pos_y][enemy.pos_x] = objects.enemy; // Передвигаем моба                    
                            Maps[game.map_number][++player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }

                    else if (more_by_coordinate && (move.left_space_for_enemy(enemy))) { // Если откидываем направо
                        if (this->move_left(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][enemy.pos_y][--enemy.pos_x] = objects.enemy; // Передвигаем моба
                            Maps[game.map_number][++player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }

                    else if (move.right_space_for_enemy(enemy)) {
                        if (this->move_right(enemy.id)) { // Если удаётся обновить мобу координаты
                            if (enemy.hpHas(enemy.id, list, game.map_number)) Maps[game.map_number][enemy.pos_y][++enemy.pos_x] = objects.enemy; // Передвигаем моба
                            Maps[game.map_number][++player.pos_y][player.pos_x] = objects.space /* = " . " */; // Передвигаем игрока на позицию моба
                        }
                    }

                }

            }

            // Убавляем игроку хп
            player.hp = player.hp - enemy.dmg;
            
            return true;
        }

    };

    Enemy enemy;

};

Entities entities;

// Фукнции дл¤ получени¤ разрешени¤ действий, св¤занных с мобом
bool getActionOnEnemyX(Player player, int map_number) {
   return (Maps[map_number][player.pos_y][player.pos_x - 1].id == objects.enemy.id || Maps[map_number][player.pos_y][player.pos_x + 1].id == objects.enemy.id);
}

bool getActionOnEnemyY(Player player, int map_number) {
    return (Maps[map_number][player.pos_y - 1][player.pos_x].id == objects.enemy.id || Maps[map_number][player.pos_y + 1][player.pos_x].id == objects.enemy.id);
}

sGetActionOnEnemies getActionOnEnemyLeft(Player player, int map_number) {
     // Создаём переменную для взаимодействия с объектами мобов
    return {
      Maps[map_number][player.pos_y][player.pos_x - 1].id == objects.enemy.id,
      entities.enemy.getByCoord(player.pos_x - 1, player.pos_y)
    };
}

sGetActionOnEnemies getActionOnEnemyRight(Player player, int map_number) {
     // Создаём переменную для взаимодействия с объектами мобов
    return {
      Maps[map_number][player.pos_y][player.pos_x + 1].id == objects.enemy.id,
      entities.enemy.getByCoord(player.pos_x + 1, player.pos_y)
    };
}

sGetActionOnEnemies getActionOnEnemyUp(Player player, int map_number) {
     // Создаём переменную для взаимодействия с объектами мобов
    return {
      Maps[map_number][player.pos_y - 1][player.pos_x].id == objects.enemy.id,
      entities.enemy.getByCoord(player.pos_x, player.pos_y - 1)
    };
}
sGetActionOnEnemies getActionOnEnemyDown(Player player, int map_number) {
     // Создаём переменную для взаимодействия с объектами мобов
    return {
      Maps[map_number][player.pos_y + 1][player.pos_x].id == objects.enemy.id,
      entities.enemy.getByCoord(player.pos_x, player.pos_y + 1)
    };
}

// -----------------------------------------------

string title = game.name; // Dummy

void static Move(char m, int map_number) { // Создаём функцию, отвечающую за передвижение игрока

        // Если игрок находится рядом с противником
        bool x_true = getActionOnEnemyX(player, map_number); // по абциссе (оси X)
        sGetActionOnEnemies x_true_right = getActionOnEnemyRight(player, map_number);
        sGetActionOnEnemies x_true_left = getActionOnEnemyLeft(player, map_number);

        bool y_true = getActionOnEnemyY(player, map_number); // по ординате (оси Y)
        sGetActionOnEnemies y_true_up = getActionOnEnemyUp(player, map_number);
        sGetActionOnEnemies y_true_down = getActionOnEnemyDown(player, map_number);

        ChecksOnMove move;
        
        if ((m == 'k' || m == 'l') && game.debug.active) {
            if (m == 'k') (game.debug.pages.max != game.debug.pages.page) && game.debug.pages.page > 0 ? --game.debug.pages.page : game.debug.pages.page = 0;
            else if (m == 'l') (game.debug.pages.max != game.debug.pages.page) ? ++game.debug.pages.page : game.debug.pages.page = 0;
            game.ui_update_permission = true;
        } 

        else if (m == 'e' && spawn.action_pos_x == player.pos_x && spawn.action_pos_y == player.pos_y && pick_loot_item == false) {
            // player_invent[player_inv_i] = loot_item;
            // ++player_inv_i; 
            Maps[map_number][player.pos_y][player.pos_x] = objects.space /* = " . " */; // Очищаем положение игрока на исходной карте 
            map_number == size(Maps) - 1 ? game.map_number = 0 : game.map_number++; // Переключение на следующую локацию
            Maps[map_number][player.pos_y][player.pos_x] = objects.player /* = " P " */; // Спавним игрока на новой карте
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }

        else if (m == 'q' && (x_true || y_true)) { // Если игрок наносит удар мобу, то
            if (getActionOnEnemyLeft(player, map_number).nearby) entities.enemy.attack(move, getActionOnEnemyLeft(player, map_number).enemy, x_true, y_true, x_true_right.nearby, x_true_left.nearby, y_true_up.nearby, y_true_down.nearby); // Удар влево
            else if (getActionOnEnemyRight(player, map_number).nearby) entities.enemy.attack(move, getActionOnEnemyRight(player, map_number).enemy, x_true, y_true, x_true_right.nearby, x_true_left.nearby, y_true_up.nearby, y_true_down.nearby); // Удар вправо
            else if (getActionOnEnemyUp(player, map_number).nearby) entities.enemy.attack(move, getActionOnEnemyUp(player, map_number).enemy, x_true, y_true, x_true_right.nearby, x_true_left.nearby, y_true_up.nearby, y_true_down.nearby); // Удар вверх
            else if (getActionOnEnemyDown(player, map_number).nearby) entities.enemy.attack(move, getActionOnEnemyDown(player, map_number).enemy, x_true, y_true, x_true_right.nearby, x_true_left.nearby, y_true_up.nearby, y_true_down.nearby); // Удар вниз

            if (!player.hpHas()) game.over = true; // Если у игрока не осталось хп, то прекращаем игру
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }

        else if (m == 'w' && move.forward_border && !y_true_up.nearby ) { // != " # "
            Maps[map_number][--player.pos_y][player.pos_x];
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }
        else if (m == 's' && move.back_border && !y_true_down.nearby) { // != " # "
            Maps[map_number][++player.pos_y][player.pos_x];
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }
        else if (m == 'a' && move.left_border && !x_true_left.nearby) { // != " # "
            Maps[map_number][player.pos_y][--player.pos_x];
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }
        else if (m == 'd' && move.right_border && !x_true_right.nearby) { // != " # "
            Maps[map_number][player.pos_y][++player.pos_x];
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }

        else if (m == 'i') !game.debug.active ? game.debug.active = true : game.debug.active = false; // Вызов отладки

        else game.ui_update_permission = false; // Если действие бесполезно, то останавливаем цикличное обновление интерфейса

}

void static UI_Update() { // Функцией обновляем данные в переменную UI_Interface
    UI_Interface[1][0] = " | Имя: " + player.name + "    ", " # ";
    UI_Interface[2][0] = " | Класс: " + player.className + "  ", " # ";
    UI_Interface[3][0] = " | HP: " + to_string(player.hp) + "        ", " # ";
    UI_Interface[4][0] = " | DMG: " + to_string(player.dmg) + "        ", " # ";
    UI_Interface[5][0] = " | MAP: #" + to_string(game.map_number);
}

void static getEnemyInDebug(sEnemyObject enemy, string direction) {
    // cout << endl;
    cout << "Enemy: " << enemy.id << " (" << direction << ")" << endl;
    cout << "  hp: " << enemy.hp << endl;
    cout << "  pos_x: " << enemy.pos_x << endl;
    cout << "  pos_y: " << enemy.pos_y << endl;
    cout << "  life: " << enemy.life << endl;
    cout << "  dmg: " << enemy.dmg << endl;
    cout << endl;
}

class Debug {
    public:
        void getGameInfo(Game game, int map_number) {
           // cout << endl;
            cout << "Version: " << game.version << endl;
            cout << "Map: " << map_number << endl;
            cout << "enemyies: " << entities.enemy.list.size() << endl;
            cout << "map_number: " << map_number << endl;
            cout << "pick_loot_item: " << pick_loot_item;
            cout << " fight: " << fight << endl;
        }

        void getPlayerInfo(Player player, int map_number) {
           // cout << endl;
            cout << "player.pos_x: " << player.pos_x << " | " << "player.pos_y: " << player.pos_y << endl;
            cout << "player_pos_name: " << Maps[map_number][player.pos_y][player.pos_x].name << endl;
            cout << "player.moves: " << player.moves << endl;
            cout << "player.hp: " << player.hp << endl;
            cout << "player.life: " << player.life << endl;
        }

        void getEnvironmentInfo(Player player, int map_number) {
           // cout << endl;
            if (getActionOnEnemyLeft(player, map_number).nearby) getEnemyInDebug(getActionOnEnemyLeft(player, map_number).enemy, "left");
            if (getActionOnEnemyRight(player, map_number).nearby) getEnemyInDebug(getActionOnEnemyRight(player, map_number).enemy, "right");
            if (getActionOnEnemyUp(player, map_number).nearby) getEnemyInDebug(getActionOnEnemyUp(player, map_number).enemy, "up");
            if (getActionOnEnemyDown(player, map_number).nearby) getEnemyInDebug(getActionOnEnemyDown(player, map_number).enemy, "down");
        }
        
        void getAvailableMovements(bool x_true, bool y_true, bool x_true_left, bool x_true_right, bool y_true_up, bool y_true_down) {
           // cout << endl;
            cout << "x_true: " << x_true;
            cout << " y_true: " << y_true << endl;
            cout << "x_true_left: " << x_true_left;
            cout << " x_true_right: " << x_true_right;
            cout << " | y_true_up: " << y_true_up;
            cout << " y_true_down: " << y_true_down << endl;
        }

        void getAllEnemyies() {
            for (const auto& enemy : entities.enemy.list) {
                getEnemyInDebug(enemy, "getAll");
            }
        }
};

void static UI_Map(int map_number) { // Функция, которая выводит интерфейс управления игрой

        // Если игрок находится рядом с противником
        bool x_true = getActionOnEnemyX(player, map_number); // по абциссе (оси X)
        bool x_true_right = getActionOnEnemyRight(player, map_number).nearby;
        bool x_true_left = getActionOnEnemyLeft(player, map_number).nearby;

        bool y_true = getActionOnEnemyY(player, map_number); // по ординате (оси Y)
        bool y_true_up = getActionOnEnemyUp(player, map_number).nearby;
        bool y_true_down = getActionOnEnemyDown(player, map_number).nearby;

        if (spawn.action_pos_x == player.pos_x && spawn.action_pos_y == player.pos_y) cout << " # e - Go       # " << endl; // Если игрок находится на координате действия
        if (x_true || y_true) cout << " # q - Action   # " << endl; // Если игрок находится возле противника
        else Maps[map_number][spawn.action_pos_y][spawn.action_pos_x] = objects.action;

    // Вывод интрефейса управления
    cout << endl << " #  #  #  #  #  #  #  #  #  #  #  # #" << endl;
    cout << objects.border.designation << " w-˄;" << " s-˅;" << " a-˂;" << " d-˃;" << " 0-E" << objects.border.designation;
    cout << endl << " #  #  #  #  #  #  #  #  #  #  #  # #" << endl;


    if (game.debug.active) { // Вывод интерфейса отладки, если она вызвана

        // Обновление заголовка терминала для Windows
        setWindowsConsoleTitle(title + " | " + game.version + " | " + game.author);
        ChecksOnMove move;
        Debug debug;
        
        game.debug.pages.max = 4;
        cout << "DEBUG PAGE #" << game.debug.pages.page << endl;
        if (game.debug.pages.page == 0) debug.getGameInfo(game, map_number);
        else if (game.debug.pages.page == 1) debug.getPlayerInfo(player, map_number);
        else if (game.debug.pages.page == 2) debug.getEnvironmentInfo(player, map_number);
        else if (game.debug.pages.page == 3) debug.getAvailableMovements(x_true, y_true, x_true_left, x_true_right, y_true_up, y_true_down);
        else if (game.debug.pages.page == 4) debug.getAllEnemyies();
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

    for (int i = 0; i < size(Maps[game.map_number]); i++) {
        for (int j = 0; j < size(Maps[game.map_number][i]); j++) { // Вывод карты игрока

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
            for (sEnemyObject enemy : entities.enemy.list) {
                if ((enemy.pos_y == i && enemy.pos_x == j) && (enemy.life && enemy.hpHas(enemy.id, entities.enemy.list, game.map_number)) && (Maps[game.map_number][enemy.pos_y][enemy.pos_x].id == objects.enemy.id)) {
                    position = { true, objects.enemy }; // Если на этой координате игрок, то добавляем его в приоритете отображения
                }
            }
            if ((player.pos_y == i && player.pos_x == j) && player.life) position = { true, objects.player }; // Если на этой координате игрок, то добавляем его в приоритете отображения

            if (position.special) cout << position.object.designation;
            else cout << Maps[game.map_number][i][j].designation;

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
    
    
    entities.enemy.create(0, 6, 8);
    entities.enemy.create(0, 3, 7);
    game.map_number = 0; // При запуске игры устанавливаем первую (нулевую в программе) карту
    while (!game.over) { // Запускаем бесконечный цикл, чтобы программа не останавливалась, если произведётся действие
        
        // Обновляем интерфейс по разрешению 
        if (game.ui_update_permission) {
            clearScreen(); // Обновляем интрфейс терминала, (если оно вообще у вас будет работать) чтобы не было большого вывода символов
            if (player.hp <= 0) game.over = true; // Если у игрока нет хп, то прекращаем игру
            Render_map(); // Обновляем интрефейс карты
            // Render_Invert();
            UI_Map(game.map_number); // Обновляем интрефейс управления
        }

        char ch;
        ch = _getch();
        if (ch == '0') { break; } // Остановка программы, если указан прописанный символ в ковычках
        Move(tolower(ch), game.map_number); // Совершаем некоторое действие, указанное от игрока

    }

    //Если игра закончена, то выводим интерфейс об окончании игры
    UI_Bye();

}
