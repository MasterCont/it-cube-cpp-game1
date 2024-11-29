#pragma once
#include "objects.h";

int map_number = 0; // Указываем, что по умолчанию загружается первая (нулевая по программе) карта
const int maps_size = 6; // Создаём размер барьера

object border = objects.border;
object space = objects.space;
object Maps[][maps_size][maps_size]{


    { // Map 0 - Создаём карту 1
        {border, border, border, border, border, border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, border, border, border, border, border}
    },

    { // Map 1 - Создаём карту 2
        {border, border, border, space, space, border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {space, space , space , space , space , border},
        {border, space , space , space , space , space},
        {border, border, border, border, space, space}
    },

    { // Map 2 - Создаём карту 3
        {border, border, border, space, space, border},
        {space, space , space , space , space , border},
        {space, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space, border},
        {border, border, border, border, space, border}
    }

};