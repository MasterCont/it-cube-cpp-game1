#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

struct object {
    int id;
    std::string name;
    std::string designation;
};

// ������ ������ ���� �������� �� ����� ����
class Objects {
public:
    const object _void = { 0, "void", " X " }; // ������ ����������� ������� �������
    const object space = { 1, "space", " . " }; // ������ ����������� ������������
    const object border = { 2, "border", " # " }; // ������ ����������� ������
    const object action = {     3, "action", " * " }; // ������ ����������� ��������
    const object player = { 4, "player", " P " }; // ������ ����������� ������
    const object enemy = { 5, "enemy", " A " }; // ������ ����������� ���������� (����)
};

Objects objects;

struct sEnemyObject { // ���������� �� structEnemyObject
    int id;
    int hp;
    int dmg;
    int pos_x, pos_y;
    bool life = false; // ��� �� ���

    bool hpHas(int id, vector<sEnemyObject> list, int map_number) {
        sEnemyObject enemy = list[id];
        bool notHave = (enemy.hp <= 0);
        if (notHave) {
            enemy.life = false;
           // Maps[map_number][enemy.pos_y][enemy.pos_x] = objects.space;
        }
        return notHave ? false : true;
    }
};

struct sGetActionOnEnemies {
    bool nearby;
    sEnemyObject enemy;
};