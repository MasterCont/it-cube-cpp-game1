#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// —оздаЄм некоторые "ответы" программы
class Responses {
public:
    const string undefined = "Undefined";
};

Responses res;


// ‘ункци¤ дл¤ установки заголовка терминала Windows
void setWindowsConsoleTitle(string title) {
    wstring wstr(title.begin(), title.end());
    const wchar_t* wstrPtr = wstr.c_str();
    SetConsoleTitle(wstrPtr);
}

void outputToCenter(const std::vector<std::string>& messages, int consoleWidth = 0, int consoleHeight = 0) {
    // �������� ���������� �������
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // �������� ������� �������
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

    if (consoleWidth == 0) consoleWidth = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
    if (consoleHeight == 0) consoleHeight = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;

    // ������� ������� ����� ������� ����� ���������
    system("cls");

    // ������� ��� ��������� �� �����
    for (size_t i = 0; i < messages.size(); ++i) {
        const std::string& text = messages[i];

        // ��������� ������� ��� ������������� ������
        int textLength = text.length();
        int x = (consoleWidth / 2) - (textLength / 2);
        int y = consoleHeight / 4 + i; // �������� y, ����� ����� �� ������������

        // ������������� ������ � ������ ���������
        COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(hConsole, coord);

        // ������� �����
        std::cout << text;
    }
}


// ‘ункци¤ дл¤ вывода окна запуска программы
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

// ‘ункци¤ дл¤ вывода окна завершени¤ программы
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

// ‘ункци¤ дл¤ получени¤ рандомного числа в диапазоне от min до max
int random(int min, int max) {
    return rand() % max + min;
}

struct userData {
    string name;
};

// Функция для записи данных в программу
userData getUserData() {

    // Добавляем персонажу имя/название
    int count = 16;
    string name;

    cout << "# Введите имя вашего персонажа: ";
    cin >> name;

    if (name.size() <= count && name.size() > 0) return { name };
    else {
        cout << endl;
        cout << "Допустимое имя персонажа стостоит из " + to_string(count) + " символов!" << endl;
        getUserData();
    }
}

void clearScreen() {
    // �������� ����� ��� ������������ ������
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // �������� ������� �������
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // ���������� ������ ����������� ������
    DWORD cells = csbi.srWindow.Right * csbi.srWindow.Bottom;
    DWORD written;
    COORD coord = { 0, 0 };

    // ��������� ���� ����� ���������
    FillConsoleOutputCharacter(hConsole, ' ', cells, coord, &written);
    // ������������� ���� ������, ���� ���������
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cells, coord, &written);

    // ���������� ������ � ������� ����� ����
    SetConsoleCursorPosition(hConsole, coord);
}

LPCSTR stringToLPCSTR(string value) {
    LPCSTR lpcstr = value.c_str();
    return lpcstr;
}