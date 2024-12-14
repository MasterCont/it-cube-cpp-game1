#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

struct object {
    int id;
    std::string name;
    std::string designation;
};

// Создаём список всех объектов на карте игры
class Objects {
public:
    const object _void = { 0, "void", " X " }; // Создаём обозначение пустого объекта
    const object space = { 1, "space", " . " }; // Создаём обозначение пространства
    const object border = { 2, "border", " # " }; // Создаём обозначение границ
    const object action = { 3, "action", " * " }; // Создаём обозначение действия
    object player = { 4, "player", " P " }; // Создаём обозначение игрока
    const object enemy = { 5, "enemy", " A " }; // Создаём обозначение противника (моба)
};

Objects objects;

struct sEnemyObject { // Сокращённо от structEnemyObject
    int id;
    int hp;
    int dmg;
    int pos_x, pos_y;
    int map_number;
    bool life = false; // Жив ли моб

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

struct actionsOnEneies {
    bool x_true;
    bool y_true;
    sGetActionOnEnemies x_true_left;
    sGetActionOnEnemies x_true_right;
    sGetActionOnEnemies y_true_up;
    sGetActionOnEnemies y_true_down;
};

struct sEnemyObjectGet {
    sEnemyObject enemy;
    int index;
    bool passed = false;
};