#pragma once
#include <iostream>
#include "maps.h";

// Создаём противника (моба) игрока 
class Enemy {
public:
    std::string designation = " A "; // Создаём интерфейс моба
    int hp = 10; // Здоровья моба
    int dmg = 2; // Урон моба
    int pos_x = 3, pos_y = 3; // Позиция спавна моба
    bool fight = false; // Определение боя для моба
    bool moves = true; // Может ли моб передвигаться
    bool life = false; // Жив ли моб

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

Enemy enemy; // Создаём свойства моба