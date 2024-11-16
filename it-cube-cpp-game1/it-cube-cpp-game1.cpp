#include <iostream>
#include <string>
using namespace std;

//массивы и переменные
char name[11];
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
            {"","", "", ""},
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

string Cyrllius = " C ";
int Cyrllius_DMG = 2;
int Cyrllius_x = 2, Cyrllius_y = 1;

bool fight = false;
bool hero_moves = false;
bool can_go = true;

// получение имени
void get_name() {
    cout << "Имя не должно превышать 10 символов" << endl;
    cout << "Введите ваше имя:" << endl;
    cin >> name;
    int j = 0;
    while (true) {
        j++;
        if (name[j] == '\0') { break; }
    }
    for (int i = j; i < 10; i++) {
        name[i] = ' ';
    }
}

// проверка на ходьбу игрока
void Go_hero() {
    if (fight == false) { can_go = true; }
    else if (fight == true && hero_moves == true) { can_go = true; }
    else if (fight == true && hero_moves == false) { can_go = false; }
}

//Жизнь
void Life_all() {
    if (HP < 10) { Interface[3][2] = "         "; }
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
            if (i == 1 && J == 1) { cout << " | Имя:" << " " << name << "#"; }
            else { cout << Interface[i][J]; }
        }
        cout << endl;
    }
}

//Тут проверка на близость врага
bool getActionOnEnemyX(int hero_x, int hero_y, int enemy_x, int enemy_y) {
    return (map_number == 0 && (enemy_y == hero_y && (enemy_x - 1 == hero_x || enemy_x + 1 == hero_x)));
}

bool getActionOnEnemyY(int hero_x, int hero_y, int enemy_x, int enemy_y) {
    return (map_number == 0 && (enemy_x == hero_x && (enemy_y - 1 == hero_y || enemy_y + 1 == hero_y)));
}

bool debug = false; // debug меню

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
        cout << "enemy_x: " << enemy_x;
        cout << " enemy_y: " << enemy_y << endl;
        cout << "hero_x: " << hero_x;
        cout << " hero_y: " << hero_y << endl;
    }
}

//враг
void Move_enemy() {
    bool x_true = getActionOnEnemyX(hero_x, hero_y, enemy_x, enemy_y);
    bool y_true = getActionOnEnemyY(hero_x, hero_y, enemy_x, enemy_y);
    if (enemy_moves == true && fight_for_enemy == true && enemy_life == true) {
        if (x_true || y_true) {
            HP = HP - enemy_entity_DMG;
            Interface[3][1] = to_string(HP);
            Life_all();// функция проверка на жизнь всех и игрока
            enemy_moves = false;//переменная хода для моба
            hero_moves = true;
            Go_hero();// функция проверка на ходьбу игрока
        }
        else {
            if (Map[map_number][hero_y][hero_x - 1] != " # ") {
                if (Map[map_number][enemy_y][enemy_x] != Map[map_number][li_y][li_x]) {
                    Map[map_number][enemy_y][enemy_x] = " . ";
                }
                else { Map[map_number][enemy_y][enemy_x] = loot_item; }
                enemy_x = hero_x - 1;
                enemy_y = hero_y;
                Map[map_number][enemy_y][enemy_x] = enemy_entity;
            }
            else if (Map[map_number][hero_y][hero_x + 1] != " # ") {
                if (Map[map_number][enemy_y][enemy_x] != Map[map_number][li_y][li_x]) {
                    Map[map_number][enemy_y][enemy_x] = " . ";
                }
                else { Map[map_number][enemy_y][enemy_x] = loot_item; }
                enemy_x = hero_x + 1;
                enemy_y = hero_y;
                Map[map_number][enemy_y][enemy_x] = enemy_entity;
            }
            else if (Map[map_number][hero_y - 1][hero_x] != " # ") {
                if (Map[map_number][enemy_y][enemy_x] != Map[map_number][li_y][li_x]) {
                    Map[map_number][enemy_y][enemy_x] = " . ";
                }
                else { Map[map_number][enemy_y][enemy_x] = loot_item; }
                enemy_y = hero_y - 1;
                enemy_x = hero_x;
                Map[map_number][enemy_y][enemy_x] = enemy_entity;
            }
            else if (Map[map_number][hero_y + 1][hero_x] != " # ") {
                if (Map[map_number][enemy_y][enemy_x] != Map[map_number][li_y][li_x]) {
                    Map[map_number][enemy_y][enemy_x] = " . ";
                }
                else { Map[map_number][enemy_y][enemy_x] = loot_item; }
                enemy_y = hero_y + 1;
                enemy_x = hero_x;
                Map[map_number][enemy_y][enemy_x] = enemy_entity;
            }
            !enemy_moves;//переменная хода для моба
            hero_moves;
            Go_hero();// функция проверка на ходьбу игрока
        }
    }
}

// управление
void Move(char m) {
    Go_hero();
    Move_enemy();
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
            fight_for_enemy = false;

        }
        //рядом враг и начать бой
        if (m == 'q' && (x_true || y_true)) {
            if (fight == false) {
                fight = true;
                Go_hero();
                enemy_entity_HP = enemy_entity_HP - DMG;
                Life_all();
                fight_for_enemy = true;
                enemy_moves = true;
                Move_enemy();
            }
            else if (fight == true) {
                enemy_entity_HP = enemy_entity_HP - DMG;
                Life_all();
                hero_moves = false;
                Go_hero();
                enemy_moves = true;
                Move_enemy();
            }
        }

        //Ходьба
        if (m == 'w' && Map[map_number][hero_y - 1][hero_x] != " # " && Map[map_number][hero_y - 1][hero_x] != Map[map_number][enemy_y][enemy_x]) { //вверх
            if (pick_loot_item == true || Map[map_number][hero_y][hero_x] != Map[map_number][li_y][li_x]) { Map[map_number][hero_y][hero_x] = " . "; }
            else { Map[map_number][hero_y][hero_x] = loot_item; }
            Map[map_number][--hero_y][hero_x] = hero;
            if (fight && hero_moves) {
                enemy_moves = true;//переменная хода для моба
                Move_enemy();//помогает мобу ходить
                hero_moves = false;
                Go_hero();// функция проверка на ходьбу игрока
            }
        }
        if (m == 's' && Map[map_number][hero_y + 1][hero_x] != " # " && Map[map_number][hero_y + 1][hero_x] != Map[map_number][enemy_y][enemy_x]) { //вниз
            if (pick_loot_item == true || Map[map_number][hero_y][hero_x] != Map[map_number][li_y][li_x]) { Map[map_number][hero_y][hero_x] = " . "; }
            else { Map[map_number][hero_y][hero_x] = loot_item; }
            Map[map_number][++hero_y][hero_x] = hero;
            if (fight && hero_moves) {
                enemy_moves = true;//переменная хода для моба
                Move_enemy();//помогает мобу ходить
                hero_moves = false;
                Go_hero();// функция проверка на ходьбу игрока
            }
        }
        if (m == 'a' && Map[map_number][hero_y][hero_x - 1] != " # " && Map[map_number][hero_y][hero_x - 1] != Map[map_number][enemy_y][enemy_x]) { //влево
            if (pick_loot_item == true || Map[map_number][hero_y][hero_x] != Map[map_number][li_y][li_x]) { Map[map_number][hero_y][hero_x] = " . "; }
            else { Map[map_number][hero_y][hero_x] = loot_item; }
            Map[map_number][hero_y][--hero_x] = hero;
            if (fight && hero_moves) {
                enemy_moves = true;//переменная хода для моба
                Move_enemy();//помогает мобу ходить
                hero_moves = false;
                Go_hero();// функция проверка на ходьбу игрока
            }
        }
        if (m == 'd' && Map[map_number][hero_y][hero_x + 1] != " # " && Map[map_number][hero_y][hero_x + 1] != Map[map_number][enemy_y][enemy_x]) { //вправо
            if (pick_loot_item == true || Map[map_number][hero_y][hero_x] != Map[map_number][li_y][li_x]) { Map[map_number][hero_y][hero_x] = " . "; }
            else { Map[map_number][hero_y][hero_x] = loot_item; }
            Map[map_number][hero_y][++hero_x] = hero;
            if (fight && hero_moves) {
                enemy_moves = true;//переменная хода для моба
                Move_enemy();//помогает мобу ходить
                hero_moves = false;
                Go_hero();// функция проверка на ходьбу игрока
            }
        }
    }

    //кнопка для доп.инф.
    if (m == 'i') {
        if (debug == false) { debug = true; }
        else { debug = false; }
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
    get_name();
    Map[map_number][li_y][li_x] = loot_item;
    Map[map_number][enemy_y][enemy_x] = enemy_entity;
    while (true) {
        system("cls");
        Map[map_number][Cyrllius_y][Cyrllius_x] = Cyrllius;
        if (life == false) { Map[map_number][hero_y][hero_x] = "₽";  return 0; }
        if (Map[map_number][hero_y][hero_x] == Map[map_number][Cyrllius_y][Cyrllius_x]) { for (int i = 10; i > 0; i--) { if (Map[map_number][hero_y + 1][hero_x] != " # ") { ++hero_y; } } }// толчок
        Map[map_number][hero_y][hero_x] = hero;
        Render_map();
        Render_Invert();
        UI_Map();
        cout << "Введите команду" << endl;
        char f;
        cin >> f;
        if (f == '0') { break; }
        else { Move(f); }
        Move_enemy();
    }
}