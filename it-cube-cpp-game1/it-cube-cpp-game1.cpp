#include <iostream>

using namespace std;

string hero = " P ";
int hero_x = 2, hero_y = 2;

string loot_item = " * ";
int li_y = 4, li_x = 4;

string hero_invent[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
int hero_inv_i = 0;

int map_number = 0;

string Map[6][6] = {
        {" # ", " # ", " # ", " # ", " # ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " # ", " # ", " # ", " # ", " # "}
};
string Map_2[6][6] = {
        {" # ", " # ", " # ", "   ", "   ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {"   ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", "   "},
        {" # ", " # ", " # ", " # ", "   ", "   "}
};

string Map_3[6][6] = {
        {" # ", " # ", " # ", "   ", "   ", " # "},
        {"   ", " . ", " . ", " . ", " . ", " # "},
        {"   ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " . ", " . ", " . ", " . ", " # "},
        {" # ", " # ", " # ", " # ", "   ", " # "}
};
void Move(char m) {
    if (m == 'e') {
        // hero_invent[hero_inv_i] = loot_item;
        // ++hero_inv_i;
        if (map_number == 0) { map_number = 1; }
        else if (map_number == 1) { map_number = 2; }
        else if (map_number == 2) { map_number = 0; }
    }
    if (map_number == 0) {
        if (m == 'w' && (Map[hero_y - 1][hero_x] != " # ")) {
            Map[hero_y][hero_x] = " . "; Map[--hero_y][hero_x] = hero;
        }
        if (m == 's' && (Map[hero_y + 1][hero_x] != " # ")) {
            Map[hero_y][hero_x] = " . "; Map[++hero_y][hero_x] = hero;
        }
        if (m == 'a' && (Map[hero_y][hero_x - 1] != " # ")) {
            Map[hero_y][hero_x] = " . "; Map[hero_y][--hero_x] = hero;
        }
        if (m == 'd' && (Map[hero_y][hero_x + 1] != " # ")) {
            Map[hero_y][hero_x] = " . "; Map[hero_y][++hero_x] = hero;
        }
    }
    if (map_number == 1) {
        if (m == 'w' && (Map_2[hero_y - 1][hero_x] != " # ")) {
            Map_2[hero_y][hero_x] = " . "; Map_2[--hero_y][hero_x] = hero;
        }
        if (m == 's' && (Map_2[hero_y + 1][hero_x] != " # ")) {
            Map_2[hero_y][hero_x] = " . "; Map_2[++hero_y][hero_x] = hero;
        }
        if (m == 'a' && (Map_2[hero_y][hero_x - 1] != " # ")) {
            Map_2[hero_y][hero_x] = " . "; Map_2[hero_y][--hero_x] = hero;
        }
        if (m == 'd' && (Map_2[hero_y][hero_x + 1] != " # ")) {
            Map_2[hero_y][hero_x] = " . "; Map_2[hero_y][++hero_x] = hero;
        }
    }
    if (map_number == 2) {
        if (m == 'w' && (Map_2[hero_y - 1][hero_x] != " # ")) {
            Map_2[hero_y][hero_x] = " . "; Map_2[--hero_y][hero_x] = hero;
        }
        if (m == 's' && (Map_2[hero_y + 1][hero_x] != " # ")) {
            Map_2[hero_y][hero_x] = " . "; Map_2[++hero_y][hero_x] = hero;
        }
        if (m == 'a' && (Map_2[hero_y][hero_x - 1] != " # ")) {
            Map_2[hero_y][hero_x] = " . "; Map_2[hero_y][--hero_x] = hero;
        }
        if (m == 'd' && (Map_2[hero_y][hero_x + 1] != " # ")) {
            Map_2[hero_y][hero_x] = " . "; Map_2[hero_y][++hero_x] = hero;
        }
    }
}



void UI_Map() {
    if (li_x == hero_x && li_y == hero_y) {
        cout << " # e - Go       # " << endl;
    }
    else { Map[li_y][li_x] = loot_item; }
    cout << " # w - up       # " << endl;
    cout << " # s - down     # " << endl;
    cout << " # a - left     # " << endl;
    cout << " # d - right    # " << endl;
    cout << " # 0 - exit     # " << endl;
    cout << " #  #  #  #  #  # " << endl;
}

void Render_map() {
    if (map_number == 0) {
        for (auto& i : Map) {
            for (int j = 0; j < size(i); j++) {
                cout << i[j];
            }
            cout << endl;
        }
    }
    if (map_number == 1) {
        for (auto& i : Map_2) {
            for (int j = 0; j < size(i); j++) {
                cout << i[j];
            }
            cout << endl;
        }
    }
    if (map_number == 2) {
        for (auto& i : Map_3) {
            for (int j = 0; j < size(i); j++) {
                cout << i[j];
            }
            cout << endl;
        }
    }
}

// void Render_Invert() {
//     for (int i = 0; i < size(hero_invent); i++) {
//         cout <<hero_invent[i];
//     }
//     cout << endl;
// }

int main() {
    map_number = 0;
    Map[hero_y][hero_x] = hero;
    Map[li_y][li_x] = loot_item;
    while (true) {
        system("cls");
        Render_map();
        // Render_Invert();
        UI_Map();
        char ch;
        cin >> ch;
        if (ch == '0') { break; }
        Move(ch);
    }
}