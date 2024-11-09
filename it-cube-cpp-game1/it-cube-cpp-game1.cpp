
#include <iostream>
#include <string>
using namespace std;

// массивы и переменные
string name = "АКШЫЛ";
string hero = " P ";
bool life = true;
int DMG = 2;
int HP = 10;
string class_hero = "Алкаш";
int hero_x = 2, hero_y = 2;

string Map[][6][6]{

{ // Map 0 - Создаём карту 1
    {" # ", " # ", " # ", " # ", " # ", " # "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" # ", " # ", " # ", " # ", " # ", " # "}
},

{ // Map 1 - Создаём карту 2
    {" + ", " + ", " + ", " + ", " + ", " + "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" # ", " # ", " # ", " # ", " # ", " # "}
},

};
string Interface[6][4] = {
            {" |#", " # ", " # ", " #  #  # #"},
            {" | Имя: ",name, "    ", " # "},
            {" | Класс: ", class_hero, "  ", " # "},
            {" | HP: ", to_string(HP), "        ", " # "},
            {" | DMG: ", to_string(DMG), "        ", " # "},
            {" |#", " # ", " # ", " #  #  # #"}
};





string loot_item = " * ";
int li_y = 4, li_x = 4;

string hero_invent[6] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
int hero_inv_i = 0;
int map_number = 0;
bool pick_loot_item = false;

string enemy_entity = " A ";
int enemy_entity_HP = 666;
int enemy_entity_DMG = 2;
int enemy_x = 4, enemy_y = 3;
bool fight_for_enemy = false;
bool enemy_moves = true;
bool enemy_life = true;

bool fight = false;
bool hero_moves = false;
bool can_go = true;

// не знаю,какая я то хрень связаная с боем
void Go_hero() {
    if (fight == false) { can_go = true; }
    else if (fight == true && hero_moves == true) { can_go = true; }
    else if (fight == true && hero_moves == false) { can_go = false; }
}

//Жизнь
void Life_all() {
    if (HP < 1) { life = false; }
    else { life = true; }
    if (enemy_entity_HP < 1) { enemy_life = false; }
    else { enemy_life = true; }
}

// карта
void Render_map() {
    for (int i = 0; i < size(Map[map_number]); i++) {
        for (int j = 0; j < size(Map[map_number][i]); j++) { // Вывод карты игрока
            cout << Map[map_number][i][j];
        }
        for (int J = 0; J < size(Interface[i]); J++) { // Вывод информации игрока
            cout << Interface[i][J];
        }
        cout << endl;
    }
}

//Тут проверка на близость врага
bool getActionOnEnemyX(int hero_x, int hero_y, int enemy_x, int enemy_y) {
    return (enemy_y == hero_y && (enemy_x - 1 == hero_x || enemy_x + 1 == hero_x));
}

bool getActionOnEnemyY(int hero_x, int hero_y, int enemy_x, int enemy_y) {
    return (enemy_x == hero_x && (enemy_y - 1 == hero_y || enemy_y + 1 == hero_y));
}

bool debug = false; // переменная клавиши для управления,которую вытащили из main потому,что ее используют в UI_Map,который выше main

// интерфейc
void UI_Map() {
    bool f_string = false;
    bool x_true = getActionOnEnemyX(hero_x, hero_y, enemy_x, enemy_y);
    bool y_true = getActionOnEnemyY(hero_x, hero_y, enemy_x, enemy_y);
    cout << " ####################################" << endl;
    cout << " #";
    if (li_x == hero_x && li_y == hero_y && pick_loot_item == false) {
        cout << " e-!;";
    }
    else { Map[map_number][li_y][li_x] = loot_item; }
    if (x_true || y_true) {
        cout << " q-*;";
    }
    cout << " w-˄;";
    cout << " s-˅;";
    cout << " a-˂;";
    cout << " d-˃;";
    cout << " 0-E";
    if (li_x == hero_x && li_y == hero_y && pick_loot_item == false) {
        cout << "#" << endl;
    }
    else if (x_true || y_true) {
        cout << "     #" << endl;
    }
    else { cout << "          #" << endl; }
    cout << " ####################################" << endl;
    if (fight == false) {
        cout << " #Бой не идет                       #" << endl;
    }
    else {
        cout << " #Бой идет                          #" << endl;
    }
    if (can_go == false) {
        cout << " #Не ваш ход                        #" << endl;
    }
    else {
        cout << " #Ваш ход                           #" << endl;
    }
    cout << " ####################################" << endl;
    //доп.информация для кодера
    if (debug) {
        cout << "hero_moves: " << hero_moves;
        cout << " can_go: " << can_go << endl;
        cout << "HP: " << HP;
        cout << " map_number: " << map_number << endl;
        cout << "pick_loot_item: " << pick_loot_item;
        cout << " enemy_entity_HP: " << enemy_entity_HP << endl;
        cout << "fight_for_enemy: " << fight_for_enemy;
        cout << " fight: " << fight << endl;
        cout << "enemy_life: " << enemy_life;
        cout << " enemy_moves: " << enemy_moves << endl;
        cout << "life: " << life;
        cout << " f_string: " << f_string << endl;
        cout << "x_true: " << x_true;
        cout << " y_true: " << y_true << endl;
    }
}

// управление
void Move(char m) {
    bool x_true = getActionOnEnemyX(hero_x, hero_y, enemy_x, enemy_y);
    bool y_true = getActionOnEnemyY(hero_x, hero_y, enemy_x, enemy_y);
    //Ход игрока проверяется
    if (can_go == true) {
        // взять
        if (m == 'e' && li_x == hero_x && li_y == hero_y && pick_loot_item == false) {
            hero_invent[hero_inv_i] = loot_item;
            pick_loot_item = true;
            ++hero_inv_i;
            if (map_number == 0) { map_number = 1;Map[map_number][hero_y][hero_x] = hero; }
            else if (map_number == 1) { map_number = 0;Map[map_number][hero_y][hero_x] = hero; }
        }
        //рядом враг и начать бой
        if (m == 'q' && (x_true || y_true) && fight == false) {
            fight = true;
            fight_for_enemy = true;
            enemy_moves = true;
            Go_hero();
        }

        //Ходьба
        if (m == 'w' && Map[map_number][hero_y - 1][hero_x] != " # " && Map[map_number][hero_y - 1][hero_x] != Map[map_number][enemy_y][enemy_x]) { //вверх
            Map[map_number][hero_y][hero_x] = " . "; Map[map_number][--hero_y][hero_x] = hero;
            if (fight) { hero_moves = false;Go_hero(); }
        }
        if (m == 's' && Map[map_number][hero_y + 1][hero_x] != " # " && Map[map_number][hero_y + 1][hero_x] != Map[map_number][enemy_y][enemy_x]) { //вниз
            Map[map_number][hero_y][hero_x] = " . "; Map[map_number][++hero_y][hero_x] = hero;
            if (fight) { hero_moves = false;Go_hero(); }
        }
        if (m == 'a' && Map[map_number][hero_y][hero_x - 1] != " # " && Map[map_number][hero_y][hero_x - 1] != Map[map_number][enemy_y][enemy_x]) { //влево
            Map[map_number][hero_y][hero_x] = " . "; Map[map_number][hero_y][--hero_x] = hero;
            if (fight) { hero_moves = false;Go_hero(); }
        }
        if (m == 'd' && Map[map_number][hero_y][hero_x + 1] != " # " && Map[map_number][hero_y][hero_x + 1] != Map[map_number][enemy_y][enemy_x]) { //вправо
            Map[map_number][hero_y][hero_x] = " . "; Map[map_number][hero_y][++hero_x] = hero;
            if (fight) { hero_moves = false;Go_hero(); }
        }
        if (m == 'i') !debug ? debug = true : debug = false;
    }
}

void Move_enemy() {
    bool x_true = getActionOnEnemyX(hero_x, hero_y, enemy_x, enemy_y);
    bool y_true = getActionOnEnemyY(hero_x, hero_y, enemy_x, enemy_y);
    if (enemy_moves == true && fight_for_enemy == true && enemy_life == true) {
        if (x_true || y_true) {
            HP = HP - enemy_entity_DMG;
            Life_all();
            hero_moves = true;
            Go_hero();
        }
    }
}

// отображения инвентаря
void Render_Invert() {
    cout << " # Inventory:";
    for (int i = 0; i < size(hero_invent); i++) {
        cout << (hero_invent[i]);
    }
    cout << "     #";
    cout << endl;

}

// что видит игрок
int main() {
    setlocale(LC_ALL, "ru");
    if (life == false) { return 0; }
    Map[map_number][hero_y][hero_x] = hero;
    Map[map_number][li_y][li_x] = loot_item;
    Map[map_number][enemy_y][enemy_x] = enemy_entity;
    while (true) {
        system("cls");
        Render_map();
        Render_Invert();
        UI_Map();
        cout << "Введите команду" << endl;
        char f;
        cin >> f;
        if (f == '0') { break; }
        else { Move(f); }
    }
}
