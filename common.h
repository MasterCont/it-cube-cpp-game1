#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

//  ласс common с настройками игры
class common{

    struct Debug {

        struct Pages {
            int page = 0;
            int max;
        };

        int fontSize = 14;
        bool active = false;
        Pages pages;
    };

    struct Over {
        bool status = false;
        std::string reason = "";
    };

    // ¬нешний класс дл€ глобальных параметров окна
    class Window {
    public:
        const int width = 976;
        const int height = 480;
        const std::string widthString = std::to_string(width);
        const std::string heightString = std::to_string(height);
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

    // ќбъ€влени€ локальных переменных настроек игры
    Window window;
    MapDefaultSize mapDefaultSize;
};

// ќбъ€влени€ глобальных переменных
extern common game;