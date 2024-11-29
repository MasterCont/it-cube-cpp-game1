#pragma once
#include <iostream>
#include <unordered_map>

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
    const object action = { 3, "action", " * " }; // ������ ����������� ��������
    const object player = { 4, "player", " P " }; // ������ ����������� ������
    const object enemy = { 5, "enemy", " A " }; // ������ ����������� ���������� (����)
};

Objects objects;