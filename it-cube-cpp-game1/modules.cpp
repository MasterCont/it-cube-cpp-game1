#include <iostream>
#include <tchar.h>
#include <Windows.h>

using namespace std;

// ������ ��������� "������" ���������
class Responses {
public:
    const string undefined = "Undefined";
};

Responses res;

// ������� ��� ��������� ���������� ��������, ��������� � �����
bool getActionOnEnemyX(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y) {
    return (enemy_pos_y == player_pos_y && (enemy_pos_x - 1 == player_pos_x || enemy_pos_x + 1 == player_pos_x));
}

bool getActionOnEnemyY(int player_pos_x, int player_pos_y, int enemy_pos_x, int enemy_pos_y) {
    return (enemy_pos_x == player_pos_x && (enemy_pos_y - 1 == player_pos_y || enemy_pos_y + 1 == player_pos_y));
}

// ������� ��� ��������� ��������� ��������� Windows
void setWindowsConsoleTitle(string title) {
    wstring wstr(title.begin(), title.end());
    const wchar_t* wstrPtr = wstr.c_str();
    SetConsoleTitle(wstrPtr);
}

// ������� ��� ������ ���� ������� ���������
void UI_Hello(string title = res.undefined, string version = res.undefined, string author = res.undefined, string git = res.undefined) {
    cout << "# # # # # # # # # # #" << endl;
    cout << "# Title: " << title << endl;
    cout << "# Version: " << version << endl;
    cout << "# Author: " << author << endl;
    cout << "# Git: " << git << endl;
    cout << "# # # # # # # # # # #" << endl;
    cout << endl;
}