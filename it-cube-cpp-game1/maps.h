#pragma once
#include "objects.h";

const int maps_size = 12; // ������ ������ �������

object border = objects.border;
object space = objects.space;
object Maps[][maps_size][maps_size]{


    { // Map 0 - ������ ����� 1
        {border, border, border, border, border, border, border, border, border, border, border, border},
        {border, space , space , space , space , space , space , space , space , space , space , border},
        {border, space , space , space , space , space , space , space , space , space , space , border},
        {border, space , space , space , space , space , space , space , space , space , space , border},
        {border, space , space , space , space , space , space , space , space , space , space , border},
        {border, space , space , space , space , space , space , space , space , space , space , border},
        {border, space , space , space , space , space , space , space , space , space , space , border},
        {border, space , space , space , space , space , space , space , space , space , space , border},
        {border, space , space , space , space , space , space , space , space , space , space , border},
        {border, space , space , space , space , space , space , space , space , space , space , border},
        {border, space , space , space , space , space , space , space , space , space , space , border},
        {border, border, border, border, border, border, border, border, border, border, border, border}
    },

    { // Map 1 - ������ ����� 2
        {border, border, border, space, space, border},
        {border, space , space , space , space , border},
        {border, space , space , space , space , border},
        {space, space , space , space , space , border},
        {border, space , space , space , space , space},
        {border, border, border, border, space, space}
    },

    { // Map 2 - ������ ����� 3
        {border, border, border, space, space, border},
        {space, space , space , space , space , border},
        {space, space , space , space , space , border},
        {border, space , space , space , space , border},
        {border, space , space , space , space, border},
        {border, border, border, border, space, border}
    }

};