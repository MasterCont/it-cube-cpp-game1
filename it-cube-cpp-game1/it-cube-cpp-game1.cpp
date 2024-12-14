#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
using namespace std;

//массивы и переменные
bool brutality_c = false;

bool brutal_mode = false;

char name[11];
string hero = " P ";
bool life = true;
int DMG = 2;
int HP = 10;
string class_hero = "Алкаш";
int hero_x = 2, hero_y = 2;

string loot_item = " * ";
int li_y = 4, li_x = 4;

string hero_invent[6] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
string hero_invent_th[6] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
string mystical_stone = "mystical stone";
int hero_inv_i = 0;
int map_number = 0;
bool pick_loot_item = false;

class Enemy {
public:
    string enemy_entity = " A ";
    int enemy_entity_HP = 666;
    int enemy_entity_DMG = 2;
    int enemy_x = 4, enemy_y = 3;
    bool fight_for_enemy = false;
    bool enemy_moves = true;
    bool enemy_life = true;
    char name_enemy[10] = { 'У','б','и','й','ц','а',' ',' ' ,' ',' ' };//да,я глиномес
};
Enemy enemy;

string Cyrllius = " C ";
bool Cyrllius_life = true;
int Cyrllius_DMG = 2;
int Cyrllius_x = 2, Cyrllius_y = 1;

bool fight = false;
bool hero_moves = false;
bool can_go = true;
bool can_d = true;
bool can_a = true;
bool can_w = true;
bool can_s = true;

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
{ // Map 2 - Создаём карту 2
    {" # ", " # ", " # ", " # ", " # ", " # "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" # ", " . ", " . ", " . ", " . ", " # "},
    {" + ", " + ", " + ", " + ", " + ", " + "}
},

};

class PitCl {
public:
    string pit_one = " О ";
    int pit_number = 0;
    bool pit_pit = false;
    int pit_x = 1, pit_y = 1;
};
PitCl pitone;


string Pit1[2][6][3]{
    { // Pit1 0
    {" # ", "   "," # "},
    {" [ ", " | "," ] "},
    {" # ", "   "," # "},
    {" [ ", "   "," ] "},
    {" # ", "   "," # "},
    {" [ ", "   "," ] "}
},
 { // Pit1 1
    {" [ ", "   "," ] "},
    {" # ", "| |"," # "},
    {" [ ", "   "," ] "},
    {" # ", "   "," # "},
    {" [ ", "   "," ] "},
    {" # ", "   "," # "}
},
};

string Interface[6][4] = {
            {" |#", " # ", " # ", " #  #  #"},
            {"","", "", ""},
            {" | Класс: ", class_hero, "  ", " "},
            {" | HP: ", to_string(HP), "        ", " "},
            {" | DMG: ", to_string(DMG), "        ", " "},
            {" |#", " # ", " # ", " #  #  #"}
};
string Interface_enemy[6][4] = {
            {" #", " # ", " # ", " #  #  # # #"},
            {"","", "", ""},
            {" | Отношение: ", "враг", "", "# "},
            {" | HP: ", to_string(enemy.enemy_entity_HP), "        ", " # "},
            {" | DMG: ", to_string(enemy.enemy_entity_DMG), "        ", " # "},
            {" #", " # ", " # ", " #  #  # # #"}
};


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

bool brutal_mode_type_i = true;

void BrutalMode() {
    if (brutal_mode == true && brutal_mode_type_i == true) {
            DMG = 500;
            HP = HP + 10;
            hero = "*P ";
            brutal_mode_type_i = false;
            Interface[3][1] = to_string(HP);
            Interface[4][1] = to_string(DMG);
    }
    if (brutal_mode == false) {
        brutal_mode_type_i = true;
    }
}

//Жизнь и показатели
void Life_all() {
    // регуляция отображения ХП
    if (HP < 10) { Interface[3][2] = "         "; }
    else if(HP > 9 && HP < 100) { Interface[3][2] = "        "; }
    else if (HP > 99 && HP < 1000) { Interface[3][2] = "       "; }
    if (HP < 1) { life = false; }
    // смерть игрока
    else { life = true; }
    // смерть врага
    if (enemy.enemy_entity_HP < 1) { enemy.enemy_life = false;enemy.fight_for_enemy = false;fight = false;Map[0][enemy.enemy_y][enemy.enemy_x] = " . "; }
    // регуляция отображения ХП врага
    else { enemy.enemy_life = true; }
    if (enemy.enemy_entity_HP > 99) { Interface_enemy[3][2] = "       "; }
    else if (enemy.enemy_entity_HP > 9) { Interface_enemy[3][2] = "        "; }
    // регуляция отображения ДМГ
    if (DMG < 10) { Interface[4][2] = "        "; }
    else if (DMG > 9 && DMG < 100) { Interface[4][2] = "       "; }
    else if (DMG > 99 && DMG < 1000) { Interface[4][2] = "      "; }
}

// карта
void Render_map() {
    if (pitone.pit_pit == false) {
        for (int i = 0; i < size(Map[map_number]); i++) {
            for (int j = 0; j < size(Map[map_number][i]); j++) { // Вывод карты игрока
                cout << Map[map_number][i][j];
            }
            for (int J = 0; J < size(Interface[i]); J++) { // Вывод информации игрока
                if (i == 1 && J == 1) { cout << " | Имя:" << " " << name; }
                else { cout << Interface[i][J]; }
            }
            if (fight == true && enemy.fight_for_enemy == true) {
                for (int g = 0; g < size(Interface_enemy[i]); g++) { // Вывод информации врага
                    if (i == 1 && g == 1) { cout << " | Имя:" << " " << enemy.name_enemy << "#"; }
                    else { cout << Interface_enemy[i][g]; }
                }
            }
            if (fight == false && enemy.fight_for_enemy == false && (i != 0 && i != 5)) { cout << "#"; } //глиномесю
            if (fight == false && enemy.fight_for_enemy == false && (i == 0 || i == 5)) { cout << " #"; } //глиномесю
            cout << endl;
        }
    }
    if (pitone.pit_pit == true) {
        for (int i = 0; i < size(Pit1[pitone.pit_number]); i++) {
            for (int j = 0; j < size(Pit1[pitone.pit_number][i]); j++) { // Вывод карты игрока
                cout << Pit1[pitone.pit_number][i][j];
            }
            for (int J = 0; J < size(Interface[i]); J++) { // Вывод информации игрока
                if (i == 1 && J == 1) { cout << " | Имя:" << " " << name; }
                else { cout << Interface[i][J]; }
            }
            if (fight == true && enemy.fight_for_enemy == true) {
                for (int g = 0; g < size(Interface_enemy[i]); g++) { // Вывод информации врага
                    if (i == 1 && g == 1) { cout << " | Имя:" << " " << enemy.name_enemy << "#"; }
                    else { cout << Interface_enemy[i][g]; }
                }
            }
            if (fight == false && enemy.fight_for_enemy == false && (i != 0 && i != 5)) { cout << "#"; } //глиномесю
            if (fight == false && enemy.fight_for_enemy == false && (i == 0 || i == 5)) { cout << " #"; } //глиномесю
            cout << endl;
        }
    }
}

void RenderPit() {
    if (pitone.pit_pit == true) {
        can_go == false;
        hero_x = 1, hero_y = 2;
        for (int m = 30;m > 0;m--) {
            pitone.pit_number = 0;
            system("cls");
            Pit1[pitone.pit_number][hero_y][hero_x] = hero;
            Render_map();
            Sleep(100);
            pitone.pit_number = 1;
            system("cls");
            Pit1[pitone.pit_number][hero_y][hero_x] = hero;
            Render_map();
        }
        if (brutal_mode == false) {
            HP = HP - 2;
            Interface[3][1] = to_string(HP);
        }
        pitone.pit_pit = false;
        map_number = 0;
        hero_x = 1, hero_y = 1;
        system("cls");
        Map[map_number][hero_y][hero_x] = hero;
        Render_map();
        can_go == true;
        system("cls");
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
    bool x_true = getActionOnEnemyX(hero_x, hero_y, enemy.enemy_x, enemy.enemy_y);
    bool y_true = getActionOnEnemyY(hero_x, hero_y, enemy.enemy_x, enemy.enemy_y);
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
        cout << " enemy_entity_HP: " << enemy.enemy_entity_HP << endl;
        cout << "fight_for_enemy: " << enemy.fight_for_enemy;
        cout << " fight: " << fight << endl;
        cout << "enemy_life: " << enemy.enemy_life;
        cout << " enemy_moves: " << enemy.enemy_moves << endl;
        cout << "life: " << life;
        cout << " f_string: " << f_string << endl;
        cout << "x_true: " << x_true;
        cout << " y_true: " << y_true << endl;
        cout << "enemy_x: " << enemy.enemy_x;
        cout << " enemy_y: " << enemy.enemy_y << endl;
        cout << "hero_x: " << hero_x;
        cout << " hero_y: " << hero_y << endl;
        cout << "brutal_mode: " << brutal_mode;
        cout << " pit_pit: " << pitone.pit_pit << endl;
    }
}

//враг
void Move_enemy() {
    bool x_true = getActionOnEnemyX(hero_x, hero_y, enemy.enemy_x, enemy.enemy_y);
    bool y_true = getActionOnEnemyY(hero_x, hero_y, enemy.enemy_x, enemy.enemy_y);
    if (enemy.enemy_moves == true && enemy.fight_for_enemy == true && enemy.enemy_life == true) {
        if (x_true || y_true) {
            HP = HP - enemy.enemy_entity_DMG;
            Interface[3][1] = to_string(HP);
        }
        else if (!x_true && !y_true) {
            if (Map[map_number][hero_y][hero_x - 1] != " # ") {
                if (Map[0][enemy.enemy_y][enemy.enemy_x] != Map[map_number][li_y][li_x]) {
                    Map[0][enemy.enemy_y][enemy.enemy_x] = " . ";
                }
                else { Map[0][enemy.enemy_y][enemy.enemy_x] = loot_item; }
                enemy.enemy_x = hero_x - 1;
                enemy.enemy_y = hero_y;
                Map[0][enemy.enemy_y][enemy.enemy_x] = enemy.enemy_entity;
            }
            else if (Map[map_number][hero_y][hero_x + 1] != " # ") {
                if (Map[0][enemy.enemy_y][enemy.enemy_x] != Map[map_number][li_y][li_x]) {
                    Map[0][enemy.enemy_y][enemy.enemy_x] = " . ";
                }
                else { Map[0][enemy.enemy_y][enemy.enemy_x] = loot_item; }
                enemy.enemy_x = hero_x + 1;
                enemy.enemy_y = hero_y;
                Map[0][enemy.enemy_y][enemy.enemy_x] = enemy.enemy_entity;
            }
            else if (Map[map_number][hero_y - 1][hero_x] != " # ") {
                if (Map[0][enemy.enemy_y][enemy.enemy_x] != Map[map_number][li_y][li_x]) {
                    Map[0][enemy.enemy_y][enemy.enemy_x] = " . ";
                }
                else { Map[0][enemy.enemy_y][enemy.enemy_x] = loot_item; }
                enemy.enemy_y = hero_y - 1;
                enemy.enemy_x = hero_x;
                Map[0][enemy.enemy_y][enemy.enemy_x] = enemy.enemy_entity;
            }
            else if (Map[map_number][hero_y + 1][hero_x] != " # ") {
                if (Map[0][enemy.enemy_y][enemy.enemy_x] != Map[map_number][li_y][li_x]) {
                    Map[0][enemy.enemy_y][enemy.enemy_x] = " . ";
                }
                else { Map[0][enemy.enemy_y][enemy.enemy_x] = loot_item; }
                enemy.enemy_y = hero_y + 1;
                enemy.enemy_x = hero_x;
                Map[0][enemy.enemy_y][enemy.enemy_x] = enemy.enemy_entity;
            }
        }

        enemy.enemy_moves = false;//переменная хода для моба

    }
    hero_moves = true;
    Go_hero();// функция проверка на ходьбу игрока
}

// управление
void Move(char m) {
    Go_hero();
    Move_enemy();
    bool x_true = getActionOnEnemyX(hero_x, hero_y, enemy.enemy_x, enemy.enemy_y);
    bool y_true = getActionOnEnemyY(hero_x, hero_y, enemy.enemy_x, enemy.enemy_y);
   
    //Ход игрока проверяется
    if (can_go == true) {
        // взять
        if (m == 'e') {
            if (li_x == hero_x && li_y == hero_y && pick_loot_item == false) {
                hero_invent[hero_inv_i] = loot_item;
                hero_invent_th[hero_inv_i] = mystical_stone;
                pick_loot_item = true;               

                if (map_number == 0) { map_number = 1;Map[map_number][hero_y][hero_x] = hero;Map[map_number][hero_y][hero_x] = hero;Map[0][hero_y][hero_x] = " . "; }
                else if (map_number == 1) { map_number = 0;Map[map_number][hero_y][hero_x] = hero;Map[0][hero_y][hero_x] = " 1 ";}
                enemy.fight_for_enemy = false;
                fight = false;
                ++hero_inv_i;
            }
        }
        // активация предмета 1
        if (m == '1') {
            if (hero_invent_th[0] == mystical_stone) {
                brutal_mode = true;
                BrutalMode();
                hero_invent[0] = " 1 ";
                hero_invent_th[hero_inv_i] = " 1 ";
            }
        }
        //рядом враг и начать бой
        if (m == 'q' && (x_true || y_true)) {
            if (fight == false) {
                fight = true;
                Go_hero();
                enemy.enemy_entity_HP = enemy.enemy_entity_HP - DMG;
                Interface_enemy[3][1] = to_string(enemy.enemy_entity_HP);
                Life_all();
                enemy.fight_for_enemy = true;
                enemy.enemy_moves = true;
                Move_enemy();
            }
            else if (fight == true) {
                enemy.enemy_entity_HP = enemy.enemy_entity_HP - DMG;
                Interface_enemy[3][1] = to_string(enemy.enemy_entity_HP);
                Life_all();
                hero_moves = false;
                Go_hero();
                enemy.enemy_moves = true;
                Move_enemy();
            }
        }

        //рядом C (секрет)
        if (m == 'c' && brutality_c == false && Cyrllius_life == true) {
            Map[map_number][hero_y][hero_x] = " . ";
            hero_y = Cyrllius_y + 1;
            hero_x = Cyrllius_x;
            Map[map_number][hero_y][hero_x] = hero;
            brutality_c = true;
        }

        //Ходьба
        if (m == 'w' && Map[map_number][hero_y - 1][hero_x] != " # " && (Map[map_number][hero_y - 1][hero_x] != Map[0][enemy.enemy_y][enemy.enemy_x] || enemy.enemy_life == false)) { //вверх
            if (pick_loot_item == true || Map[map_number][hero_y][hero_x] != Map[map_number][li_y][li_x]) { Map[map_number][hero_y][hero_x] = " . "; }
            else { Map[map_number][hero_y][hero_x] = loot_item; }
            Map[map_number][--hero_y][hero_x] = hero;
            if (fight && hero_moves) {
                enemy.enemy_moves = true;//переменная хода для моба
                Move_enemy();//помогает мобу ходить
                hero_moves = false;
                Go_hero();// функция проверка на ходьбу игрока
            }
        }
        if (m == 's' && Map[map_number][hero_y + 1][hero_x] != " # " && (Map[map_number][hero_y + 1][hero_x] != Map[0][enemy.enemy_y][enemy.enemy_x] || enemy.enemy_life == false)) { //вниз
            if (pick_loot_item == true || Map[map_number][hero_y][hero_x] != Map[map_number][li_y][li_x]) { Map[map_number][hero_y][hero_x] = " . "; }
            else { Map[map_number][hero_y][hero_x] = loot_item; }
            Map[map_number][++hero_y][hero_x] = hero;
            if (fight && hero_moves) {
                enemy.enemy_moves = true;//переменная хода для моба
                Move_enemy();//помогает мобу ходить
                hero_moves = false;
                Go_hero();// функция проверка на ходьбу игрока
            }
        }
        if (m == 'a' && Map[map_number][hero_y][hero_x - 1] != " # " && (Map[map_number][hero_y][hero_x - 1] != Map[0][enemy.enemy_y][enemy.enemy_x] || enemy.enemy_life == false)) { //влево
            if (pick_loot_item == true || Map[map_number][hero_y][hero_x] != Map[map_number][li_y][li_x]) { Map[map_number][hero_y][hero_x] = " . "; }
            else { Map[map_number][hero_y][hero_x] = loot_item; }
            Map[map_number][hero_y][--hero_x] = hero;
            if (fight && hero_moves) {
                enemy.enemy_moves = true;//переменная хода для моба
                Move_enemy();//помогает мобу ходить
                hero_moves = false;
                Go_hero();// функция проверка на ходьбу игрока
            }
        }
        if (m == 'd' && Map[map_number][hero_y][hero_x + 1] != " # " && (Map[map_number][hero_y][hero_x + 1] != Map[0][enemy.enemy_y][enemy.enemy_x] || enemy.enemy_life == false)) { //вправо
            if (pick_loot_item == true || Map[map_number][hero_y][hero_x] != Map[map_number][li_y][li_x]) { Map[map_number][hero_y][hero_x] = " . "; }
            else { Map[map_number][hero_y][hero_x] = loot_item; }
            Map[map_number][hero_y][++hero_x] = hero;
            if (fight && hero_moves) {
                enemy.enemy_moves = true;//переменная хода для моба
                Move_enemy();//помогает мобу ходить
                hero_moves = false;
                Go_hero();// функция проверка на ходьбу игрока
            }
        }
    }

    //кнопка для доп.инф.
    if (m == 'k') {
        if (debug == false) { debug = true; }
        else { debug = false; }
    }

    if (map_number == 1 && hero_y <= 0) { Map[map_number][0][hero_x] = " + "; map_number = 2;hero_y = 4; }
    else if (map_number == 2 && hero_y >= 5) { Map[map_number][5][hero_x] = " + "; map_number = 1;hero_y = 1; }
    if (pitone.pit_y == hero_y && pitone.pit_x == hero_x && map_number == 2) { pitone.pit_pit = true; }
    Map[2][pitone.pit_y][pitone.pit_x] = pitone.pit_one;
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

// облегчает жизнь
void anime() {
    system("cls");
    Render_map();
    Render_Invert();
    UI_Map();
}

// что видит игрок
int main() {
    setlocale(LC_ALL, "ru");
    system("chcp 1251 > nul");
    get_name();
    Map[map_number][li_y][li_x] = loot_item;
    Map[map_number][enemy.enemy_y][enemy.enemy_x] = enemy.enemy_entity;
    Map[2][pitone.pit_y][pitone.pit_x] = pitone.pit_one;
    while (true) {
        Life_all();
        BrutalMode();
        if (pick_loot_item == true) { loot_item = " . "; }
        if (enemy.enemy_life == false) { enemy.enemy_entity = " . "; }
        system("cls");
        if (Cyrllius_life == true) {
            Map[map_number][Cyrllius_y][Cyrllius_x] = Cyrllius;
        }
        else { Map[0][Cyrllius_y][Cyrllius_x] = Cyrllius;Map[1][Cyrllius_y][Cyrllius_x] = " . "; }
        if (life == false) { Map[map_number][hero_y][hero_x] = "₽";  return 0; }
        //анимация
        if (brutality_c == true) {
            Map[map_number][hero_y][hero_x] = " . ";
            Sleep(500);
            anime();
            Map[map_number][hero_y][hero_x] = hero;
            Sleep(1000);
            anime();
            Map[map_number][hero_y][hero_x] = " . ";
            hero_x = Cyrllius_x + 1;
            hero_y = Cyrllius_y;
            Map[map_number][hero_y][hero_x] = hero;
            Sleep(20);
            anime();;
            Map[map_number][hero_y][hero_x] = " . ";
            hero_x = hero_x + 1;Map[map_number][hero_y][hero_x] = hero;
            Sleep(50);
            anime();;
            Map[map_number][hero_y][hero_x - 1] = "<--";
            Sleep(100);
            anime();
            Map[map_number][hero_y][hero_x] = " . ";
            hero_x = hero_x - 1;
            Map[map_number][hero_y][hero_x] = hero;
            Map[map_number][Cyrllius_y][Cyrllius_x] = "<С-";
            Cyrllius = "<С-";
            Cyrllius_life = false;
            system("cls");
            brutality_c = false;
        }//конец анимации
        RenderPit();
        if (Map[map_number][hero_y][hero_x] == Map[map_number][Cyrllius_y][Cyrllius_x] && Cyrllius_life == true) { for (int i = 10; i > 0; i--) { if (Map[map_number][hero_y + 1][hero_x] != " # ") { Sleep(1);anime(); if (Map[map_number][hero_y][hero_x] != Map[map_number][Cyrllius_y][Cyrllius_x]) { Map[map_number][hero_y][hero_x] = " . "; }++hero_y;Map[map_number][hero_y][hero_x] = hero;system("cls"); } } }// толчок
        Map[map_number][hero_y][hero_x] = hero;
        Render_map();
        Render_Invert();
        UI_Map();
        cout << "Введите команду" << endl;
        char f[3];
        cin >> f;
        if (f[0] == '0') { break; }
        else { if (f[0] != 'i' && f[0] != '1') { Move(f[0]); } else if(f[0] == 'i') { Move(f[1]); }}
        Move_enemy();
    }
}
