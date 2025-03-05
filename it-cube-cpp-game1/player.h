#pragma once
#include <iostream>

// ������ ������
class Player {
public:
    std::string name; // ������ ����������, � ������� ������� ��� ������
    std::string className = "@player_class_name"; // ������ ����������, � ������� ���������� "�����" ������
    std::string player_invent[6] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
    int pos_x = 2, pos_y = 2; // ����������� ����� ������ �� ����������� �� x � y
    int hp = 20; // ������ �� ������
    int dmg = 2;
    int inv_i = 0;
    bool moves = false; // ������ �� ����� ������ ���������� �� ���
    bool life = true; // ��� �� �����

    bool hpHas() {
        bool notHave = hp <= 0;
        if (notHave) life = false;
        return notHave ? false : true;
    }
};

Player player; // ������ ���������� ������ ��� �������������� � �������