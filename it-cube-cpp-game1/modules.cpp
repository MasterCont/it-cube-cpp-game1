#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <unordered_map>
#include <string>
using namespace std;

// вЂ”РѕР·РґР°Р„Рј РЅРµРєРѕС‚РѕСЂС‹Рµ "РѕС‚РІРµС‚С‹" РїСЂРѕРіСЂР°РјРјС‹
class Responses {
public:
    const string undefined = "Undefined";
};

Responses res;


// вЂСѓРЅРєС†РёВ¤ РґР»В¤ СѓСЃС‚Р°РЅРѕРІРєРё Р·Р°РіРѕР»РѕРІРєР° С‚РµСЂРјРёРЅР°Р»Р° Windows
void setWindowsConsoleTitle(string title) {
    wstring wstr(title.begin(), title.end());
    const wchar_t* wstrPtr = wstr.c_str();
    SetConsoleTitle(wstrPtr);
}

// вЂСѓРЅРєС†РёВ¤ РґР»В¤ РІС‹РІРѕРґР° РѕРєРЅР° Р·Р°РїСѓСЃРєР° РїСЂРѕРіСЂР°РјРјС‹
void UI_Hello(string title = res.undefined, string version = res.undefined, string author = res.undefined, string git = res.undefined) {
    cout << "# # # # # # # # # # #" << endl;
    cout << "# Title: " << title << endl;
    cout << "# Version: " << version << endl;
    cout << "# Author: " << author << endl;
    cout << "# Git: " << git << endl;
    cout << "# # # # # # # # # # #" << endl;
    cout << endl;
    cout << "# # # # # # # # # # #" << endl;
    cout << "# Control buttons: " << endl;
    cout << "# DEBUG: I | K/L" << endl;
    cout << "# # # # # # # # # # #" << endl;
    cout << endl;
}

// вЂСѓРЅРєС†РёВ¤ РґР»В¤ РІС‹РІРѕРґР° РѕРєРЅР° Р·Р°РІРµСЂС€РµРЅРёВ¤ РїСЂРѕРіСЂР°РјРјС‹
void UI_Bye() {
    system("cls");
    cout << "# # # # # # # # # # #" << endl;
    cout << "#     Game over!    #" << endl;
    cout << "# # # # # # # # # # #" << endl;
    cout << endl;
    system("pause");
}

// вЂСѓРЅРєС†РёВ¤ РґР»В¤ РїРѕР»СѓС‡РµРЅРёВ¤ СЂР°РЅРґРѕРјРЅРѕРіРѕ С‡РёСЃР»Р° РІ РґРёР°РїР°Р·РѕРЅРµ РѕС‚ min РґРѕ max
int random(int min, int max) {
    return rand() % max + min;
}

struct userData {
    string name;
};

// Р¤СѓРЅРєС†РёСЏ РґР»СЏ Р·Р°РїРёСЃРё РґР°РЅРЅС‹С… РІ РїСЂРѕРіСЂР°РјРјСѓ
userData getUserData() {

    // Р”РѕР±Р°РІР»СЏРµРј РїРµСЂСЃРѕРЅР°Р¶Сѓ РёРјСЏ/РЅР°Р·РІР°РЅРёРµ
    int count = 16;
    string name;

    cout << "# Р’РІРµРґРёС‚Рµ РёРјСЏ РІР°С€РµРіРѕ РїРµСЂСЃРѕРЅР°Р¶Р°: ";
    cin >> name;

    if (name.size() <= count && name.size() > 0) return { name };
    else {
        cout << endl;
        cout << "Р”РѕРїСѓСЃС‚РёРјРѕРµ РёРјСЏ РїРµСЂСЃРѕРЅР°Р¶Р° СЃС‚РѕСЃС‚РѕРёС‚ РёР· " + to_string(count) + " СЃРёРјРІРѕР»РѕРІ!" << endl;
        getUserData();
    }
}

void clearScreen() {
    // Получаем хендл для стандартного вывода
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Получаем размеры консоли
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Определяем размер консольного буфера
    DWORD cells = csbi.srWindow.Right * csbi.srWindow.Bottom;
    DWORD written;
    COORD coord = { 0, 0 };

    // Заполняем весь экран пробелами
    FillConsoleOutputCharacter(hConsole, ' ', cells, coord, &written);
    // Устанавливаем цвет текста, если требуется
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cells, coord, &written);

    // Перемещаем курсор в верхний левый угол
    SetConsoleCursorPosition(hConsole, coord);
}