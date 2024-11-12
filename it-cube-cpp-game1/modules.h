#pragma once

using namespace std;

// ������ ��������� ���������� � ����� ����������
class Game {
public:
    const string version = "0.0.8";
    const string name = "@it_cube_cpp_game1";
    const string author = "MasterCont";
    const string git = "https://github.com/MasterCont/it-cube-cpp-game1.git";
    bool debug = false; // ���� �������, �� ���������� ���������
};

// ������ ������
class Player {
public:
    string name; // ������ ����������, � ������� ������� ��� ������
    string className = "@player_class_name"; // ������ ����������, � ������� ���������� "�����" ������
    string player_invent[6] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
    int pos_x = 2, pos_y = 2; // ����������� ����� ������ �� ����������� �� x � y
    int hp = 10; // ������ �� ������
    int dmg = 2;
    int inv_i = 0;
    bool moves = false; // ������ �� ����� ������ ���������� �� ���
    bool life = true; // ��� �� �����
};

// ������ ���������� (����) ������ 
class Enemy {
public:
    string designation = " A "; // ������ ��������� ����
    int hp = 20; // �������� ����
    int dmg = 2; // ���� ����
    int pos_x = 4, pos_y = 3; // ������� ������ ����
    bool fight = false; // ����������� ��� ��� ����
    bool moves = true; // ����� �� ��� �������������
    bool life = true; // ��� �� ���
};

// ������ ���������� ������ ��� ������� �������
class Spawn {
public:
    int li_pos_y = 4, li_pos_x = 4; // ����������� ����� �������� �� ����������� �� x � y
};

class Designations {
public:
    const string loot_item = " * "; // ������ ����������� ��������
    const string border = " # "; // ������ ����������� ������
    const string player = " P "; // ������ ����������� ������
    const string space = " . "; // ������ ����������� ������������
    const string enemy = " A "; // ������ ����������� ���������� (����)
};

extern bool pick_loot_item = false; // ������ �� ������� �������

// ��������� ���� ��� ������
extern bool fight = false; // ��� ��� ��� ������ ��� ���
extern bool can_go = true; // ����� �� ������������� �����

extern int map_number = 0; // ���������, ��� �� ��������� ����������� ������ (������� �� ���������) �����
extern const int maps_size = 6; // ������ ������ �������

Player player; // ������ ���������� ������ ��� �������������� � �������
Enemy enemy; // ������ �������� ����
Spawn spawn; // ������ ���������� ��� �������������� �� �������� ��������
Designations designations;
Game game;

extern string border = designations.border;
extern string space = designations.space;
extern string Maps[][maps_size][maps_size]{


    { // Map 0 - ������ ����� 1
        {border, border, border, border, border, border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, border, border, border, border, border}
    },

    { // Map 1 - ������ ����� 2
        {border, border, border, "   ", "   ", border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {"   ", space , space , space , space , border},
        {border, space , space , space , space , "   "},
        {border, border, border, border, "   ", "   "}
    },

    { // Map 2 - ������ ����� 3
        {border, border, border, "   ", "   ", border},
        {"   ", space , space , space , space , border},
        {"   ", space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space, border},
        {border, border, border, border, "   ", border}
    }

};

// ������� ��� ��������� ���������� ��������, ��������� � �����
bool getActionOnEnemyX(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y);
bool getActionOnEnemyY(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y);

// ������� ��� ��������� ��������� ��������� Windows
void setWindowsConsoleTitle(string title);

// ������� ��� ������ ���� ������� ���������
void UI_Hello(string title, string version, string author, string git);