#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

// ¬нешний класс дл€ глобальных параметров окна
class GlobalWindow {
public:
    const int width = 976;
    const int height = 480;
};

//  ласс common с настройками игры
class common{

    struct Debug {

        struct Pages {
            int page;
            int max;
        };

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

    // ќбъ€влени€ локальных переменных настроек игры
    Window window;
};

// ќбъ€влени€ глобальных переменных
extern common game;