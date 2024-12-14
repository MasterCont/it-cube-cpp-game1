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

// Необходимо для проигрывания звуков
#include <mmsystem.h> 
#pragma comment(lib, "winmm.lib")

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

    bool back_space_for_enemy(sEnemyObject enemy) { // Если сзади буде+т барьер+
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
        int dmg = 1;

        bool initialization(int map_number, sEnemyObject enemy) {
            enemy.life = true;
            list.push_back(enemy);
            Maps[map_number][enemy.pos_y][enemy.pos_x] = objects.enemy;
            return enemy.life ? true : false;
        }

        bool create(int map_number, int pos_x, int pos_y) {
            int enemyID = list.size();
            sEnemyObject enemy = { enemyID, hp, dmg, pos_x, pos_y, map_number, true }; // Создаём моба
            initialization(map_number, enemy);
            return true;
        }

        bool remove(int id) {
            // Не очень перспективный метод, но работающий:
            for (int i = 0; i < list.size(); i++) {
                if (list[i].id == id) {
                    list.erase(list.begin() + i);
                    break;
                }
            }
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

        sEnemyObjectGet getByIdwithIndex(int id) {
            // Не очень перспективный метод, но работающий:
            for (int i = 0; i < list.size(); i++) {
                if (list[i].id == id) return {list[i], i, true};
            }
        }

        bool move_right(int id) {
            if (getByIdwithIndex(id).passed) {
                ++list[getByIdwithIndex(id).index].pos_x;
                return true;
            }
            else return false;
        };

        bool move_left(int id) {
            if (getByIdwithIndex(id).passed) {
                --list[getByIdwithIndex(id).index].pos_x;
                return true;
            }
            else return false;
        };

        bool move_up(int id) {
            if (getByIdwithIndex(id).passed) {
                --list[getByIdwithIndex(id).index].pos_y;
                return true;
            }
            else return false;
        };

        bool move_down(int id) {
            if (getByIdwithIndex(id).passed) {
                ++list[getByIdwithIndex(id).index].pos_y;
                return true;
            }
            else return false;
        };

        bool attack(ChecksOnMove move, sEnemyObject enemy, bool x_true, bool y_true, bool x_true_right, bool x_true_left, bool y_true_up, bool y_true_down) {
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

            // Проверяем координаты перемещения
            if (this->getByIdwithIndex(enemy.id).passed) {
                sEnemyObject thisEnemy = this->getByIdwithIndex(enemy.id).enemy;

                if (thisEnemy.pos_x == enemy.pos_x && thisEnemy.pos_y == enemy.pos_y) { // Если всё успешно сработало

                    int index = this->getByIdwithIndex(enemy.id).index;
                    list[index].hp = list[index].hp - player.dmg; // Убавляем мобу хп
                    PlaySoundA(stringToLPCSTR("sound_enemy_getDmg" + to_string(random(0, 2)) + ".wav"), NULL, SND_FILENAME | SND_ASYNC);
                    more_by_coordinate = random(0, 4); // Откидываем моба рандомно

                    // Убавляем игроку хп
                    player.hp = player.hp - enemy.dmg;

                    if (!enemy.hpHas(index, list, enemy.map_number)) {
                        list[index].life = false;
                        Maps[game.map_number][list[index].pos_y][list[index].pos_x] = objects.space /* = " . " */; // Очищаем объект на карте
                        PlaySoundA(stringToLPCSTR("sound_enemy_death" + to_string(random(0, 2)) + ".wav"), NULL, SND_FILENAME | SND_ASYNC);
                        remove(enemy.id);

                        if (list.size() == 0) {
                            game.over.status = true; // Если противников не осталось
                            game.over.reason = messages.enemyiesDerstoyed;
                        }

                    }

                    return true;
                }

                else return false;
            }

            

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

void static Move(char m, int map_number, actionsOnEneies actionsOnEneies) { // Создаём функцию, отвечающую за передвижение игрока

        // Если игрок находится рядом с противником
        bool x_true = actionsOnEneies.x_true; // по абциссе (оси X)
        sGetActionOnEnemies x_true_right = actionsOnEneies.x_true_right;
        sGetActionOnEnemies x_true_left = actionsOnEneies.x_true_left;

        bool y_true = actionsOnEneies.y_true; // по ординате (оси Y)
        sGetActionOnEnemies y_true_up = actionsOnEneies.y_true_up;
        sGetActionOnEnemies y_true_down = actionsOnEneies.y_true_down;

        ChecksOnMove move;
        
        if ((m == 'k' || m == 'l') && game.debug.active) {
            if (m == 'k') (game.debug.pages.max != game.debug.pages.page) && game.debug.pages.page > 0 ? --game.debug.pages.page : game.debug.pages.page = 0;
            else if (m == 'l') (game.debug.pages.max != game.debug.pages.page) ? ++game.debug.pages.page : game.debug.pages.page = 0;
            PlaySoundA(stringToLPCSTR("sound_debug" + to_string(random(0, 2)) + ".wav"), NULL, SND_FILENAME | SND_ASYNC);
            game.ui_update_permission = true;
        } 

        else if (m == 'e' && spawn.action_pos_x == player.pos_x && spawn.action_pos_y == player.pos_y && pick_loot_item == false) {
            // player_invent[player_inv_i] = loot_item;
            // ++player_inv_i; 
            Maps[map_number][player.pos_y][player.pos_x] = objects.space /* = " . " */; // Очищаем положение игрока на исходной карте 
            map_number == size(Maps) - 1 ? game.map_number = 0 : game.map_number++; // Переключение на следующую локацию
            Maps[map_number][player.pos_y][player.pos_x] = objects.player /* = " P " */; // Спавним игрока на новой карте
            PlaySoundA("sound_player_locationTransition.wav", NULL, SND_FILENAME | SND_ASYNC);
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }

        else if (m == 'q' && (x_true || y_true)) { // Если игрок наносит удар мобу, то
            if (getActionOnEnemyLeft(player, map_number).nearby) entities.enemy.attack(move, getActionOnEnemyLeft(player, map_number).enemy, x_true, y_true, x_true_right.nearby, x_true_left.nearby, y_true_up.nearby, y_true_down.nearby); // Удар влево
            else if (getActionOnEnemyRight(player, map_number).nearby) entities.enemy.attack(move, getActionOnEnemyRight(player, map_number).enemy, x_true, y_true, x_true_right.nearby, x_true_left.nearby, y_true_up.nearby, y_true_down.nearby); // Удар вправо
            else if (getActionOnEnemyUp(player, map_number).nearby) entities.enemy.attack(move, getActionOnEnemyUp(player, map_number).enemy, x_true, y_true, x_true_right.nearby, x_true_left.nearby, y_true_up.nearby, y_true_down.nearby); // Удар вверх
            else if (getActionOnEnemyDown(player, map_number).nearby) entities.enemy.attack(move, getActionOnEnemyDown(player, map_number).enemy, x_true, y_true, x_true_right.nearby, x_true_left.nearby, y_true_up.nearby, y_true_down.nearby); // Удар вниз

            if (!player.hpHas()) game.over.status = true; // Если у игрока не осталось хп, то прекращаем игру
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }

        else if (m == 'w' && move.forward_border && !y_true_up.nearby ) { // != " # "
            Maps[map_number][--player.pos_y][player.pos_x];
            PlaySoundA("sound_player_move.wav", NULL, SND_FILENAME | SND_ASYNC);
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }
        else if (m == 's' && move.back_border && !y_true_down.nearby) { // != " # "
            Maps[map_number][++player.pos_y][player.pos_x];
            PlaySoundA("sound_player_move.wav", NULL, SND_FILENAME | SND_ASYNC);
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }
        else if (m == 'a' && move.left_border && !x_true_left.nearby) { // != " # "
            Maps[map_number][player.pos_y][--player.pos_x];
            PlaySoundA("sound_player_move.wav", NULL, SND_FILENAME | SND_ASYNC);
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }
        else if (m == 'd' && move.right_border && !x_true_right.nearby) { // != " # "
            Maps[map_number][player.pos_y][++player.pos_x];
            PlaySoundA("sound_player_move.wav", NULL, SND_FILENAME | SND_ASYNC);
            game.ui_update_permission = true; // Разрешаем обновление интерфейса игры
        }

        else if (m == 'i') { // Вызов отладки

            if (!game.debug.active) {
                game.debug.active = true;
                PlaySoundA("sound_debug_open.wav", NULL, SND_FILENAME | SND_ASYNC);
            } else {
                game.debug.active = false;
                PlaySoundA("sound_debug_close.wav", NULL, SND_FILENAME | SND_ASYNC);
            }

            game.ui_update_permission = true;
        }
        else game.ui_update_permission = false; // Если действие бесполезно, то останавливаем цикличное обновление интерфейса

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
        cout << "Window.Width: " << game.window.width << endl;
        cout << "Window.Height: " << game.window.height << endl;
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

void static UI_Update(int map_number, actionsOnEneies actionsOnEneies) { // Функцией обновляем данные в переменную UI_Interface
    UI_Interface[1][0] = " | Имя: " + player.name + "    ", " # ";
    UI_Interface[2][0] = " | Класс: " + player.className + "  ", " # ";
    UI_Interface[3][0] = " | HP: " + to_string(player.hp) + "        ", " # ";
    UI_Interface[4][0] = " | DMG: " + to_string(player.dmg) + "        ", " # ";
    UI_Interface[5][0] = " | MAP: #" + to_string(game.map_number);

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
        else if (game.debug.pages.page == 3) debug.getAvailableMovements(actionsOnEneies.x_true, actionsOnEneies.y_true, actionsOnEneies.x_true_left.nearby, actionsOnEneies.x_true_right.nearby, actionsOnEneies.y_true_up.nearby, actionsOnEneies.y_true_down.nearby);
        else if (game.debug.pages.page == 4) debug.getAllEnemyies();
    }
    else {
        // Cброс заголовка терминала для Windows
        setWindowsConsoleTitle(title);
    }
}

void static UI_Map(int map_number, actionsOnEneies actionsOnEneies) { // Функция, которая выводит интерфейс управления игрой

        // Если игрок находится рядом с противником
        bool x_true = actionsOnEneies.x_true; // по абциссе (оси X)
        bool y_true = actionsOnEneies.y_true; // по ординате (оси Y)

        if (spawn.action_pos_x == player.pos_x && spawn.action_pos_y == player.pos_y) cout << " # e - Go       # " << endl; // Если игрок находится на координате действия
        if (x_true || y_true) cout << " # q - Action   # " << endl; // Если игрок находится возле противника
        else Maps[map_number][spawn.action_pos_y][spawn.action_pos_x] = objects.action;

    // Вывод интрефейса управления
    cout << endl << " #  #  #  #  #  #  #  #  #  #  #  # #" << endl;
    cout << objects.border.designation << " w-˄;" << " s-˅;" << " a-˂;" << " d-˃;" << " 0-E" << objects.border.designation;
    cout << endl << " #  #  #  #  #  #  #  #  #  #  #  # #" << endl;
  
}

void static Render_map() { // Функция, которая обновляет интерфейс карты при изменении действий в игре

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
    PlaySoundA(stringToLPCSTR("sound_start_hello" + to_string(random(0, 2)) + ".wav"), NULL, SND_FILENAME | SND_ASYNC);
    UI_Hello(title, game.version, game.author, game.git);
    system("cls");

    // Добавляем персонажу имя/название
    PlaySoundA("sound_start_getData.wav", NULL, SND_FILENAME | SND_ASYNC); // пасхалка
    string name = getUserData().name;
    player.name = name;

    if (player.name == "gloomyman") {
        PlaySoundA("sound_bruh.wav", NULL, SND_FILENAME | SND_ASYNC); // пасхалка
        objects.player.designation = " K ";
    }
    
    
    entities.enemy.create(0, 6, 8);
    entities.enemy.create(0, 3, 7);
    game.map_number = 0; // При запуске игры устанавливаем первую (нулевую в программе) карту
    while (!game.over.status) { // Запускаем бесконечный цикл, чтобы программа не останавливалась, если произведётся действие

        if (entities.enemy.list.size() == 0) {
            game.over.status = true; // Если противников не осталось
            game.over.reason = messages.enemyiesDerstoyed;
        } 

        if (player.hp <= 0) { // Если у игрока нет хп, то прекращаем игру
            game.over.status = true;
            game.over.reason = messages.playerDestroyed;
        }

        // Получаем дескриптор стандартного вывода (консоли)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Если игрок находится рядом с противником
        actionsOnEneies actionsOnEneies;
        actionsOnEneies.x_true = getActionOnEnemyX(player, game.map_number); // по абциссе (оси X)
        actionsOnEneies.x_true_right = getActionOnEnemyRight(player, game.map_number);
        actionsOnEneies.x_true_left = getActionOnEnemyLeft(player, game.map_number);

        actionsOnEneies.y_true = getActionOnEnemyY(player, game.map_number); // по ординате (оси Y)
        actionsOnEneies.y_true_up = getActionOnEnemyUp(player, game.map_number);
        actionsOnEneies.y_true_down = getActionOnEnemyDown(player, game.map_number);

        // Получаем информацию о консоли
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            // Ширина и высота консоли в символах
            game.window.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            game.window.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }
        
        // Обновляем интерфейс по разрешению 
        if (game.ui_update_permission) {
            clearScreen(); // Обновляем интрфейс терминала, (если оно вообще у вас будет работать) чтобы не было большого вывода символов
            UI_Update(game.map_number, actionsOnEneies); // Обновляем интерфейс информации игрока
            Render_map(); // Обновляем интрефейс карты
            // Render_Invert();
            UI_Map(game.map_number, actionsOnEneies); // Обновляем интрефейс управления
        }

        char ch;
        ch = _getch();
        if (ch == '0') {  // Остановка программы, если указан прописанный символ в ковычках
            game.over.reason = messages.gameBreak;
            break;
        }
        Move(tolower(ch), game.map_number, actionsOnEneies); // Совершаем некоторое действие, указанное от игрока

    }

    //Если игра закончена, то выводим интерфейс об окончании игры
    if (entities.enemy.list.size() == 0) game.finished = true;
    if (player.name == "gloomyman") PlaySoundA("music_end_gloomyman.wav", NULL, SND_FILENAME | SND_ASYNC); // пасхалка
    else {
        if (!game.finished) PlaySoundA("sound_end_over.wav", NULL, SND_FILENAME | SND_ASYNC);
        else PlaySoundA("sound_end_finished.wav", NULL, SND_FILENAME | SND_ASYNC);
    }
    UI_Bye(game.finished, game.over.reason);
}
