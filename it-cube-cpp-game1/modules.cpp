//#include <iostream>
//#include "modules.h"
//
//using namespace std;
//
//string hero_invent[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
//int hero_inv_i = 0;
//
//int map_number = 0; // Указываем, что по умолчанию загружается первая (нулевая по программе) карта
//
//string hero = " P "; // Создаём интерфейс игрока
//int hero_x = 2, hero_y = 2; // Прописываем спавн игрока на координатах по x и y
//
//string loot_item = " * "; // Создаём интерфейс действия
//int li_y = 4, li_x = 4; // Прописываем спавн действия на координатах по x и y
//
//string Map[6][6] = { // Создаём карту 1
//        {" # ", " # ", " # ", " # ", " # ", " # "},
//        {" # ", " . ", " . ", " . ", " . ", " # "},
//        {" # ", " . ", " . ", " . ", " . ", " # "},
//        {" # ", " . ", " . ", " . ", " . ", " # "},
//        {" # ", " . ", " . ", " . ", " . ", " # "},
//        {" # ", " # ", " # ", " # ", " # ", " # "}
//};
//string Map_2[6][6] = { // Создаём карту 2
//        {" # ", " # ", " # ", "   ", "   ", " # "},
//        {" # ", " . ", " . ", " . ", " . ", " # "},
//        {" # ", " . ", " . ", " . ", " . ", " # "},
//        {"   ", " . ", " . ", " . ", " . ", " # "},
//        {" # ", " . ", " . ", " . ", " . ", "   "},
//        {" # ", " # ", " # ", " # ", "   ", "   "}
//};
//
//string Map_3[6][6] = { // Создаём карту 3
//        {" # ", " # ", " # ", "   ", "   ", " # "},
//        {"   ", " . ", " . ", " . ", " . ", " # "},
//        {"   ", " . ", " . ", " . ", " . ", " # "},
//        {" # ", " . ", " . ", " . ", " . ", " # "},
//        {" # ", " . ", " . ", " . ", " . ", " # "},
//        {" # ", " # ", " # ", " # ", "   ", " # "}
//};
//
//void static Move(char m) { // Создаём функцию, отвечающую за передвижение игрока
//    if (m == 'e') {
//        // hero_invent[hero_inv_i] = loot_item;
//        // ++hero_inv_i;
//        if (map_number == 0) { map_number = 1; } // Переключение на следующую локацию
//        else if (map_number == 1) { map_number = 2; }
//        else if (map_number == 2) { map_number = 0; } // Переключение на первую локацию, потому что тут последняя локация
//    }
//    if (map_number == 0) { // Передвижение персонажа при нулевой карте
//        if (m == 'w' && (Map[hero_y - 1][hero_x] != " # ")) {
//            Map[hero_y][hero_x] = " . "; Map[--hero_y][hero_x] = hero;
//        }
//        if (m == 's' && (Map[hero_y + 1][hero_x] != " # ")) {
//            Map[hero_y][hero_x] = " . "; Map[++hero_y][hero_x] = hero;
//        }
//        if (m == 'a' && (Map[hero_y][hero_x - 1] != " # ")) {
//            Map[hero_y][hero_x] = " . "; Map[hero_y][--hero_x] = hero;
//        }
//        if (m == 'd' && (Map[hero_y][hero_x + 1] != " # ")) {
//            Map[hero_y][hero_x] = " . "; Map[hero_y][++hero_x] = hero;
//        }
//    }
//    if (map_number == 1) { // Передвижение персонажа при первой карте
//        if (m == 'w' && (Map_2[hero_y - 1][hero_x] != " # ")) {
//            Map_2[hero_y][hero_x] = " . "; Map_2[--hero_y][hero_x] = hero;
//        }
//        if (m == 's' && (Map_2[hero_y + 1][hero_x] != " # ")) {
//            Map_2[hero_y][hero_x] = " . "; Map_2[++hero_y][hero_x] = hero;
//        }
//        if (m == 'a' && (Map_2[hero_y][hero_x - 1] != " # ")) {
//            Map_2[hero_y][hero_x] = " . "; Map_2[hero_y][--hero_x] = hero;
//        }
//        if (m == 'd' && (Map_2[hero_y][hero_x + 1] != " # ")) {
//            Map_2[hero_y][hero_x] = " . "; Map_2[hero_y][++hero_x] = hero;
//        }
//    }
//    if (map_number == 2) { // Передвижение персонажа при второй карте
//        if (m == 'w' && (Map_2[hero_y - 1][hero_x] != " # ")) {
//            Map_2[hero_y][hero_x] = " . "; Map_2[--hero_y][hero_x] = hero;
//        }
//        if (m == 's' && (Map_2[hero_y + 1][hero_x] != " # ")) {
//            Map_2[hero_y][hero_x] = " . "; Map_2[++hero_y][hero_x] = hero;
//        }
//        if (m == 'a' && (Map_2[hero_y][hero_x - 1] != " # ")) {
//            Map_2[hero_y][hero_x] = " . "; Map_2[hero_y][--hero_x] = hero;
//        }
//        if (m == 'd' && (Map_2[hero_y][hero_x + 1] != " # ")) {
//            Map_2[hero_y][hero_x] = " . "; Map_2[hero_y][++hero_x] = hero;
//        }
//    }
//}
//
//
//
//void static UI_Map() { // Функция, которая выводит интерфейс управления игрой
//    if (li_x == hero_x && li_y == hero_y) {
//        cout << " # e - Go       # " << endl;
//    }
//    else { Map[li_y][li_x] = loot_item; }
//    cout << " # w - up       # " << endl;
//    cout << " # s - down     # " << endl;
//    cout << " # a - left     # " << endl;
//    cout << " # d - right    # " << endl;
//    cout << " # 0 - exit     # " << endl;
//    cout << " #  #  #  #  #  # " << endl;
//}
//
//void static Render_map() { // Функция, которая обновляет интерфейс карты при изменении действий в игре
//    if (map_number == 0) {
//        for (auto& i : Map) {
//            for (int j = 0; j < size(i); j++) {
//                cout << i[j];
//            }
//            cout << endl;
//        }
//    }
//    if (map_number == 1) {
//        for (auto& i : Map_2) {
//            for (int j = 0; j < size(i); j++) {
//                cout << i[j];
//            }
//            cout << endl;
//        }
//    }
//    if (map_number == 2) {
//        for (auto& i : Map_3) {
//            for (int j = 0; j < size(i); j++) {
//                cout << i[j];
//            }
//            cout << endl;
//        }
//    }
//}
//
// void Render_Invert() {
//     for (int i = 0; i < size(hero_invent); i++) {
//         cout <<hero_invent[i];
//     }
//     cout << endl;
// }