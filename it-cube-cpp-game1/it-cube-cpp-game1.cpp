#include <iostream>
#include <string>

using namespace std;

// Создаём некоторую информацию о нашем приложении
string version = "0.0.3";
string name = "@it_cube_cpp_game1";

// Создаём игрока
string player = " P "; // Создаём интерфейс игрока
int player_x = 2, player_y = 2; // Прописываем спавн игрока на координатах по x и y
int player_hp = 10; // Создаём хп игроку
int player_dmg = 2;
string player_name; // Создаём переменную, в котором запишем имя игрока
string player_class = "@player_class_name"; // Создаём переменную, в котором записываем "класс" игрока


string loot_item = " * "; // Создаём интерфейс действия
int li_y = 4, li_x = 4; // Прописываем спавн действия на координатах по x и y

string player_invent[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
int player_inv_i = 0;

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
        // player_invent[player_inv_i] = loot_item;
        // ++player_inv_i;
        if (map_number == 0) { map_number = 1; } // Переключение на следующую локацию
        else if (map_number == 1) { map_number = 2; }
        else if (map_number == 2) { map_number = 0; } // Переключение на первую локацию, потому что тут последняя локация
    }

    if (m == 'w' && (Maps[map_number][player_y - 1][player_x] != " # ")) {
        Maps[map_number][player_y][player_x] = " . "; Maps[map_number][--player_y][player_x] = player;
    }
    if (m == 's' && (Maps[map_number][player_y + 1][player_x] != " # ")) {
        Maps[map_number][player_y][player_x] = " . "; Maps[map_number][++player_y][player_x] = player;
    }
    if (m == 'a' && (Maps[map_number][player_y][player_x - 1] != " # ")) {
        Maps[map_number][player_y][player_x] = " . "; Maps[map_number][player_y][--player_x] = player;
    }
    if (m == 'd' && (Maps[map_number][player_y][player_x + 1] != " # ")) {
        Maps[map_number][player_y][player_x] = " . "; Maps[map_number][player_y][++player_x] = player;
    }
}

string interface[][4] = {
     {" |#", " # ", " # ", " #  #  # #"},
     {" | Имя: "+ player_name +"    ", " # "},
     {" | Класс: "+ player_class +"  ", " # "},
     {" | HP: "+ to_string(player_hp) +"        ", " # "},
     {" | DMG: "+ to_string(player_dmg) +"        ", " # "},
     {" |#", " # ", " # ", " #  #  # #"}
};



void static UI_Map() { // Функция, которая выводит интерфейс управления игрой
    if (li_x == player_x && li_y == player_y) {
        cout << " # e - Go       # " << endl;

    }
    else { Maps[map_number][li_y][li_x] = loot_item; }
    cout << " # w - ↑ || s - ↓ || a - ← || d - → # " << endl;
    cout << " # 0 - exit                         # " << endl;
    cout << " #  #  #  #  #  #  #  #  #  #  #  # #" << endl;
}

void static Render_map() { // Функция, которая обновляет интерфейс карты при изменении действий в игре
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
    setlocale(LC_ALL, "ru"); // Устанавливаем русский язык в консоли

    cout << "Введите имя вашего персонажа: ";
    cin >> interface[1][1];
    interface[1][1] += "  #";

    map_number = 0; // При запуске игры устанавливаем первую (нулевую в программе) карту
    Maps[map_number][player_y][player_x] = player; // Указываем, что в этой координате спанится игрок и выводим его
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