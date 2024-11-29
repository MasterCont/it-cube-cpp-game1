#pragma once
#include <iostream>
#include <unordered_map>

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
    const object player = { 4, "player", " P " }; // Создаём обозначение игрока
    const object enemy = { 5, "enemy", " A " }; // Создаём обозначение противника (моба)
};

Objects objects;