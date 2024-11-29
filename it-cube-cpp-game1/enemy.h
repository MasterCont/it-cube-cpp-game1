#pragma once
#include <iostream>
#include "maps.h";

// ������ ���������� (����) ������ 
class Enemy {
public:
    std::string designation = " A "; // ������ ��������� ����
    int hp = 10; // �������� ����
    int dmg = 2; // ���� ����
    int pos_x = 3, pos_y = 3; // ������� ������ ����
    bool fight = false; // ����������� ��� ��� ����
    bool moves = true; // ����� �� ��� �������������
    bool life = false; // ��� �� ���

    bool hpHas(int map_number) {
        bool notHave = (hp <= 0);
        if (notHave) {
            life = false;
            Maps[map_number][pos_y][pos_x] = objects.space;
            //pos_x = -1;
            //pos_y = -1;
        }
        return notHave ? false : true;
    }

    bool initialization() {
        life = true;
        Maps[0][pos_y][pos_x] = objects.enemy;
        return life ? true : false;
    }
};

Enemy enemy; // ������ �������� ����