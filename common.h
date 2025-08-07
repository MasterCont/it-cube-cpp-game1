#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

// Класс common с настройками игры
class common{

    struct Debug {

        struct Pages {
            int page = 0;
            static constexpr int max = 5;
            bool looging = true;
        };

        int fontSize = 14;
        bool active = false;
        Pages pages;

        // Запущено ли приложение в режиме отладки
        #if defined(DEBUG) || defined(_DEBUG) 
                static const bool release = 0;
        #else
                static const bool release = 1;
        #endif
    };

    struct Over {
        bool status = false;
        std::string reason = "";
    };

    // Внешний класс для глобальных параметров окна
    class Window {
    public:
        const int width = 976;
        const int height = 480;
        const std::string widthString = std::to_string(width);
        const std::string heightString = std::to_string(height);
        bool focus = true;
    };

public:
    const std::string version = "0.2.0";
    const std::string name = "@it_cube_cpp_game1";
    const std::string author = "MasterCont";
    const std::string git = "https://github.com/MasterCont/it-cube-cpp-game1.git";
    int map_number = 0; 
    Debug debug; 
    Over over; 
    bool ui_update_permission = true;
    bool data_collection;
    bool hello_ui = true;
    bool finished = false;

    class MapDefaultSize {
    public:
        const int width = 1024;
        const int height = 512;
    };

    // Объявления локальных переменных настроек игры
    Window window;
    MapDefaultSize mapDefaultSize;
};

// Объявления глобальных переменных
extern common game;