#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <unordered_map>
#include <string>
#include <vector>

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

void outputToCenter(const std::vector<std::string>& messages, int consoleWidth = 0, int consoleHeight = 0) {
    // Получаем дескриптор консоли
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Получаем размеры консоли
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

    if (consoleWidth == 0) consoleWidth = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
    if (consoleHeight == 0) consoleHeight = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;

    // Очищаем консоль перед выводом новых сообщений
    system("cls");

    // Выводим все сообщения на экран
    for (size_t i = 0; i < messages.size(); ++i) {
        const std::string& text = messages[i];

        // Вычисляем отступы для центрирования текста
        int textLength = text.length();
        int x = (consoleWidth / 2) - (textLength / 2);
        int y = consoleHeight / 4 + i; // Изменяем y, чтобы текст не накладывался

        // Устанавливаем курсор в нужное положение
        COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(hConsole, coord);

        // Выводим текст
        std::cout << text;
    }
}


// вЂСѓРЅРєС†РёВ¤ РґР»В¤ РІС‹РІРѕРґР° РѕРєРЅР° Р·Р°РїСѓСЃРєР° РїСЂРѕРіСЂР°РјРјС‹
bool UI_Hello(string title = res.undefined, string version = res.undefined, string author = res.undefined, string git = res.undefined) {

    std::vector<std::string> messages = {
        "# # # # # # # # # # #\n",
        "# Title: " + title + "\n",
        "# Version: " + version + "\n",
        "# Author: " + author + "\n",
        "# Git: " + git + "\n",
        "# # # # # # # # # # #\n",
        "\n",
        "# # # # # # # # # # #\n",
        "# Control buttons : \n",
        "# DEBUG: I | K/L\n",
        "# # # # # # # # # # #\n",
        "\n\n\n",
        "# # # # # # # # # # #\n",
        "Press ENTER to start.\n",
        "# # # # # # # # # # #\n"
    };

    outputToCenter(messages);
    system("set /p dummy=");
    
    return true;
}

// вЂСѓРЅРєС†РёВ¤ РґР»В¤ РІС‹РІРѕРґР° РѕРєРЅР° Р·Р°РІРµСЂС€РµРЅРёВ¤ РїСЂРѕРіСЂР°РјРјС‹
void UI_Bye(bool successfully = false, string reason = "") {
    system("cls");

    std::vector<std::string> messages = {
        "# # # # # # # # # # #\n",
        successfully ? "#     The game has been successfully completed!    #\n" : "     Game over!    \n",
        reason.length() > 0 ? reason + "\n" : "",
        "# # # # # # # # # # #\n",
        "\n\n\n",
        "# # # # # # # # # # #\n",
        "Press ENTER to exit.\n",
        "# # # # # # # # # # #\n"
    };

    outputToCenter(messages);

    system("set /p dummy=");
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

LPCSTR stringToLPCSTR(string value) {
    LPCSTR lpcstr = value.c_str();
    return lpcstr;
}