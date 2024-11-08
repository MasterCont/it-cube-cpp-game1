#include <iostream>

using namespace std;


// Создаём некоторую информацию о нашем приложении
string version = "0.0.2";
string name = "@it_cube_cpp_game1";

// Создаём игрока
string hero = " P "; // Создаём интерфейс игрока
int hero_x = 2, hero_y = 2; // Прописываем спавн игрока на координатах по x и y
int hero_hp = 10; // Создаём хп игроку
string hero_name; // Создаём переменную, в котором запишем имя игрока

string loot_item = " * "; // Создаём интерфейс действия
int li_y = 4, li_x = 4; // Прописываем спавн действия на координатах по x и y

string hero_invent[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
int hero_inv_i = 0;

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

void static Move(char m) { // Создаём функцию, отвечающую за передвижение игрока
    if (m == 'e') {
        // hero_invent[hero_inv_i] = loot_item;
        // ++hero_inv_i;
        if (map_number == 0) { map_number = 1; } // Переключение на следующую локацию
        else if (map_number == 1) { map_number = 2; }
        else if (map_number == 2) { map_number = 0; } // Переключение на первую локацию, потому что тут последняя локация
    }

    if (m == 'w' && (Maps[map_number][hero_y - 1][hero_x] != " # ")) {
        Maps[map_number][hero_y][hero_x] = " . "; Maps[map_number][--hero_y][hero_x] = hero;
    }
    if (m == 's' && (Maps[map_number][hero_y + 1][hero_x] != " # ")) {
        Maps[map_number][hero_y][hero_x] = " . "; Maps[map_number][++hero_y][hero_x] = hero;
    }
    if (m == 'a' && (Maps[map_number][hero_y][hero_x - 1] != " # ")) {
        Maps[map_number][hero_y][hero_x] = " . "; Maps[map_number][hero_y][--hero_x] = hero;
    }
    if (m == 'd' && (Maps[map_number][hero_y][hero_x + 1] != " # ")) {
        Maps[map_number][hero_y][hero_x] = " . "; Maps[map_number][hero_y][++hero_x] = hero;
    }
}



void static UI_Map() { // Функция, которая выводит интерфейс управления игрой
    if (li_x == hero_x && li_y == hero_y) {
        cout << " # e - Go       # " << endl;
    }
    else { Maps[map_number][li_y][li_x] = loot_item; }
    cout << " # w - ↑ || s - ↓ || a - ← || d - → # " << endl;
    cout << " # 0 - exit                         # " << endl;
    cout << " #  #  #  #  #  #  #  #  #  #  #  # #" << endl;
}

void static Render_map() { // Функция, которая обновляет интерфейс карты при изменении действий в игре
    for (auto& i : Maps[map_number]) {
        for (int j = 0; j < size(i); j++) {
             cout << i[j];
        }
        cout << endl;
    }
}

// void Render_Invert() {
//     for (int i = 0; i < size(hero_invent); i++) {
//         cout <<hero_invent[i];
//     }
//     cout << endl;
// }

int main() { // Главная функция

    setlocale(LC_ALL, "ru");

    cout << "Введите имя вашего персонажа: ";
    cin >> hero_name;
    map_number = 0; // При запуске игры устанавливаем первую (нулевую в программе) карту
    Maps[map_number][hero_y][hero_x] = hero; // Указываем, что в этой координате спанится игрок и выводим его
    Maps[map_number][li_y][li_x] = loot_item; // Указываем, что в этой координате спанится действие и выводим его
    while (true) { // Запускаем бесконечный цикл, чтобы программа не останавливалась, если произведётся действие
        system("cls"); // Обновляем интрфейс терминала, (если оно вообще у вас будет работать) чтобы не было большого вывода символов
        Render_map(); // Обновляем интрефейс карты
        // Render_Invert();
        UI_Map(); // Обновляем интрефейс управления
        char ch; 
        cin >> ch; // Ввод действия игрока
        if (ch == '0') { break; } // Остановка программы, если указан прописанный символ в ковычках
        Move(ch); // Совершаем некоторое действие, указанное от игрока
    }
}