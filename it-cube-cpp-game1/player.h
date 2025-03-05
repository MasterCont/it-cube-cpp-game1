#pragma once
#include <iostream>

// Создаём игрока
class Player {
public:
    std::string name; // Создаём переменную, в котором запишем имя игрока
    std::string className = "@player_class_name"; // Создаём переменную, в котором записываем "класс" игрока
    std::string player_invent[6] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 " };
    int pos_x = 2, pos_y = 2; // Прописываем спавн игрока на координатах по x и y
    int hp = 20; // Создаём хп игроку
    int dmg = 2;
    int inv_i = 0;
    bool moves = false; // Можешь ли игрок ходить независимо от боя
    bool life = true; // Жив ли игрок

    bool hpHas() {
        bool notHave = hp <= 0;
        if (notHave) life = false;
        return notHave ? false : true;
    }
};

Player player; // Создаём переменную игрока для взаимодействия с игроком